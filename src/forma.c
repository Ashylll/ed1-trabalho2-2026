#include "forma.h"
#include "circulo.h"
#include "linha.h"
#include "retangulo.h"
#include "texto.h"
#include <stdlib.h>
#include <string.h>

typedef struct StForma {
  char tipo;
  void *handle;
} StForma;

Forma cria_forma(char tipo, void *handle) {
  if (!handle || (tipo != 'c' && tipo != 'r' && tipo != 't' && tipo != 'l'))
    return NULL;

  StForma *forma = malloc(sizeof(StForma));
  if (!forma)
    return NULL;

  forma->tipo = tipo;
  forma->handle = handle;

  return forma;
}

void libera_forma(Forma *f) {
  if (!f || !*f)
    return;
  StForma *forma = (StForma *)*f;

  void *h = forma->handle;
  if (!h)
    return;
  switch (forma->tipo) {
  case 'c':
    libera_circulo((Circulo *)&h);
    break;
  case 'r':
    libera_retangulo((Retangulo *)&h);
    break;
  case 't':
    libera_texto((Texto *)&h);
    break;
  case 'l':
    libera_linha((Linha *)&h);
    break;
  }

  free(forma);
  *f = NULL;
}

void escreve_forma_svg(FILE *fp, Forma f) {
  if (!fp || !f)
    return;

  char tipo = get_tipo_forma(f);
  void *handle = get_handle_forma(f);

  switch (tipo) {
  case 'c': {
    double x = get_x_circulo(handle);
    double y = get_y_circulo(handle);
    double r = get_raio_circulo(handle);
    const char *corb = get_corb_circulo(handle);
    const char *corp = get_corp_circulo(handle);

    double opacidade = 0.6;

    fprintf(fp,
            "<circle "
            "style=\"fill:%s;fill-opacity:%.1f;stroke:%s;stroke-width:1.0\" "
            "r=\"%.2f\" cy=\"%.2f\" cx=\"%.2f\" />\n",
            corp, opacidade, corb, r, y, x);

    break;
  }

  case 'r': {
    double x = get_x_retangulo(handle);
    double y = get_y_retangulo(handle);
    double w = get_w_retangulo(handle);
    double h = get_h_retangulo(handle);
    const char *corb = get_corb_retangulo(handle);
    const char *corp = get_corp_retangulo(handle);

    double opacidade = 0.6;

    switch (get_id_retangulo(handle)) {
    case ID_RETANGULO_SEL: {

      fprintf(fp,
              "<rect "
              "style=\"fill:%s;fill-opacity:%.1f;stroke:%s;stroke-dasharray:5;"
              "stroke-width:1.0\" x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" "
              "height=\"%.2f\" />\n",
              corp, opacidade, corb, x, y, w, h);
      break;
    }
    case ID_QUADRADO_MARCA: {

      double y_centro = y - h / 2;
      double x_centro = x - w / 2;

      fprintf(fp,
              "<rect "
              "style=\"fill:%s;fill-opacity:%.1f;stroke:%s;stroke-width:1.0\" "
              "x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" />\n",
              corp, opacidade, corb, x_centro, y_centro, w, h);
      break;
    }
    default: {

      fprintf(fp,
              "<rect "
              "style=\"fill:%s;fill-opacity:%.1f;stroke:%s;stroke-width:1.0\" "
              "x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" />\n",
              corp, opacidade, corb, x, y, w, h);
    }
    }

    break;
  }

  case 'l': {
    double x1 = get_x1_linha(handle);
    double y1 = get_y1_linha(handle);
    double x2 = get_x2_linha(handle);
    double y2 = get_y2_linha(handle);
    const char *cor = get_cor_linha(handle);

    double opacidade = 0.8;

    fprintf(fp,
            "<line style=\"stroke:%s;stroke-width:2.0;stroke-opacity:%.1f\" "
            "x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" />\n",
            cor, opacidade, x1, y1, x2, y2);

    break;
  }

  case 't': {
    double x = get_x_texto(handle);
    double y = get_y_texto(handle);
    const char *corb = get_corb_texto(handle);
    const char *corp = get_corp_texto(handle);
    const char *txto = get_palavra_texto(handle);
    const char *family = get_family_texto(handle);
    const char *weight = get_weight_texto(handle);
    const char a = get_posicao_ancora_texto(handle);
    const char *ancora;
    switch (a) {
    case 'i':
      ancora = "start";
      break;
    case 'm':
      ancora = "middle";
      break;
    case 'f':
      ancora = "end";
      break;
    }
    int size = get_size_texto(handle);

    double opacidade = 1.0;

    fprintf(fp,
            "<text "
            "style=\"text-anchor:%s;alignment-baseline:central;fill:%s;fill-"
            "opacity:%.1f;stroke:%s;stroke-width:0.7;"
            "font-family:%s;font-weight:%s;font-size:%dpx;line-height:0%%\" "
            "x=\"%.2f\" y=\"%.2f\">%s</text>\n",
            ancora, corp, opacidade, corb, family, weight, size, x, y, txto);

    break;
  }

  default:
    fprintf(stderr, "[escreve_forma_svg] tipo desconhecido: %c\n", tipo);
    break;
  }
}

double get_largura_x_forma(Forma f) {
  if (!f)
    return -1;
  void *handle = get_handle_forma(f);

  switch (get_tipo_forma(f)) {
  case 'c':
    return 2 * get_raio_circulo(handle);

  case 'r':
    return get_w_retangulo(handle);

  case 'l': {
    double x1 = get_x1_linha(handle);
    double x2 = get_x2_linha(handle);
    return x2 - x1;
  }

  case 't': {
    double palavra = strlen(get_palavra_texto(handle));
    double size = get_size_texto(handle);
    return palavra * size * 0.49;
  }

  default:
    return -1;
  }
}

Forma clona_forma(Forma f) {
  if (!f)
    return NULL;
  StForma *forma = (StForma *)f;

  void *handle = forma->handle;
  int id_clone = -10;

  switch (forma->tipo) {
  case 'c': {
    double x = get_x_circulo(handle);
    double y = get_y_circulo(handle);
    double r = get_raio_circulo(handle);
    const char *corb_original = get_corb_circulo(handle);
    const char *corp_original = get_corp_circulo(handle);

    char *corb = malloc(strlen(corb_original) + 1);
    strcpy(corb, corb_original);

    char *corp = malloc(strlen(corp_original) + 1);
    strcpy(corp, corp_original);

    return cria_forma('c', cria_circulo(id_clone, x, y, r, corb, corp));
  }

  case 'r': {
    double x = get_x_retangulo(handle);
    double y = get_y_retangulo(handle);
    double w = get_w_retangulo(handle);
    double h = get_h_retangulo(handle);
    const char *corb_original = get_corb_retangulo(handle);
    const char *corp_original = get_corp_retangulo(handle);

    char *corb = malloc(strlen(corb_original) + 1);
    strcpy(corb, corb_original);

    char *corp = malloc(strlen(corp_original) + 1);
    strcpy(corp, corp_original);

    return cria_forma('r', cria_retangulo(id_clone, x, y, w, h, corb, corp));
  }

  case 'l': {
    double x1 = get_x1_linha(handle);
    double y1 = get_y1_linha(handle);
    double x2 = get_x2_linha(handle);
    double y2 = get_y2_linha(handle);
    const char *cor_original = get_cor_linha(handle);

    char *cor = malloc(strlen(cor_original) + 1);
    strcpy(cor, cor_original);

    return cria_forma('l', cria_linha(id_clone, x1, y1, x2, y2, cor));
  }

  case 't': {
    double x = get_x_texto(handle);
    double y = get_y_texto(handle);
    const char *corb_original = get_corb_texto(handle);
    const char *corp_original = get_corp_texto(handle);
    char a = get_posicao_ancora_texto(handle);
    const char *txt = get_palavra_texto(handle);

    char *corb = malloc(strlen(corb_original) + 1);
    strcpy(corb, corb_original);

    char *corp = malloc(strlen(corp_original) + 1);
    strcpy(corp, corp_original);

    return cria_forma('t', cria_texto(id_clone, x, y, corb, corp, a, txt));
  }

  default:
    return NULL;
  }
}

void troca_cores_forma(Forma f) {
  if (!f)
    return;
  char *corb = get_corb_forma(f);
  char *corp = get_corp_forma(f);

  set_corb_forma(f, corp);
  set_corp_forma(f, corb);
}

char *traduz_tipo_forma(const char tipo, bool maiusculo) {
  if (maiusculo) {
    switch (tipo) {
    case 'r':
      return "Retângulo";
    case 'c':
      return "Círculo";
    case 'l':
      return "Linha";
    case 't':
      return "Texto";
    default:
      return "Desconhecido";
    }
  } else {
    switch (tipo) {
    case 'r':
      return "retângulo";
    case 'c':
      return "círculo";
    case 'l':
      return "linha";
    case 't':
      return "texto";
    default:
      return "desconhecido";
    }
  }
}

void reporta_forma(FILE *fp_txt, Forma f, const char criterio_ordenacao) {
  if (!f || !fp_txt)
    return;

  char t = get_tipo_forma(f);
  char *tipo = traduz_tipo_forma(t, true);

  switch (criterio_ordenacao) {
  case 'd':
    fprintf(fp_txt,
            "== %s ==\nId: %d\nÂncora: y = %.2lf || x = %.2lf\nÁrea: %.2lf\n",
            tipo, get_id_forma(f), get_y_forma(f), get_x_forma(f),
            get_area_forma(f));

    break;
  case 'a':
    fprintf(fp_txt, "== %s ==\nId: %d\nÁrea: %.2lf\n", tipo, get_id_forma(f),
            get_area_forma(f));

    break;
  case 'w':
    fprintf(fp_txt, "== %s ==\nId: %d\nLargura: %.2lf\n", tipo, get_id_forma(f),
            get_largura_forma(f));

    break;
  case 'h':
    fprintf(fp_txt, "== %s ==\nId: %d\nAltura: %.2lf\n", tipo, get_id_forma(f),
            get_altura_forma(f));

    break;
  case 'c':
    if (t == 'l') {
      fprintf(fp_txt, "== Linha ==\nId: %d\nCor: %s\n", get_id_forma(f),
              get_corp_forma(f));
    } else {
      fprintf(fp_txt, "== %s ==\nId: %d\nCor de preenchimento: %.s\n", tipo,
              get_id_forma(f), get_corp_forma(f));
    }

    break;
  default:
    fprintf(fp_txt, "Critério desconhecido\n");
  }
}

void get_correcao_ancora(Forma f, double *dx, double *dy) {
  *dx = 0.0;
  *dy = 0.0;

  switch (get_tipo_forma(f)) {
  case 'c': {
    Circulo c = get_handle_forma(f);
    double raio = get_raio_circulo(c);
    *dx = raio;
    *dy = raio;
    break;
  }
  case 't': {
    char ancora = get_posicao_ancora_texto(get_handle_forma(f));
    if (ancora == 'm')
      *dx = get_largura_x_forma(f) / 2.0;
    else if (ancora == 'f')
      *dx = get_largura_x_forma(f);
    break;
  }
  case 'l': {
    Linha l = get_handle_forma(f);
    double y1 = get_y1_linha(l);
    double y2 = get_y2_linha(l);
    double min_y = (y1 < y2) ? y1 : y2;
    *dy = y1 - min_y;
    break;
  }
  default:
    break;
  }
}

int get_id_forma(Forma f) {
  StForma *forma = (StForma *)f;

  switch (forma->tipo) {
  case 'c':
    return get_id_circulo(forma->handle);
  case 'r':
    return get_id_retangulo(forma->handle);
  case 't':
    return get_id_texto(forma->handle);
  case 'l':
    return get_id_linha(forma->handle);
  default:
    return -100;
  }
}

char get_tipo_forma(Forma f) {
  StForma *forma = (StForma *)f;

  return forma->tipo;
}

void *get_handle_forma(Forma f) {
  if (!f)
    return NULL;
  StForma *forma = (StForma *)f;

  return forma->handle;
}

bool get_ancora_forma(Forma f, double *x, double *y) {
  if (!f || !x || !y)
    return false;
  StForma *forma = (StForma *)f;

  switch (forma->tipo) {
  case 'c':
    *x = get_x_circulo(forma->handle);
    *y = get_y_circulo(forma->handle);
    break;
  case 'r':
    *x = get_x_retangulo(forma->handle);
    *y = get_y_retangulo(forma->handle);
    break;
  case 't':
    *x = get_x_texto(forma->handle);
    *y = get_y_texto(forma->handle);
    break;
  case 'l':
    *x = get_x1_linha(forma->handle);
    *y = get_y1_linha(forma->handle);
    break;
  default:
    return false;
  }

  return true;
}

double get_x_forma(Forma f) {
  if (!f)
    return -1;
  StForma *forma = (StForma *)f;

  switch (get_tipo_forma(f)) {
  case 'c':
    return get_x_circulo(forma->handle);
  case 'r':
    return get_x_retangulo(forma->handle);
  case 'l':
    return get_x1_linha(forma->handle);
  case 't':
    return get_x_texto(forma->handle);
  default:
    return -1;
  }
}

double get_y_forma(Forma f) {
  if (!f)
    return -1;
  StForma *forma = (StForma *)f;

  switch (get_tipo_forma(f)) {
  case 'c':
    return get_y_circulo(forma->handle);
  case 'r':
    return get_y_retangulo(forma->handle);
  case 'l':
    return get_y1_linha(forma->handle);
  case 't':
    return get_y_texto(forma->handle);
  default:
    return -1;
  }
}

double get_area_forma(Forma f) {
  if (!f)
    return -1;
  char tipo = get_tipo_forma(f);
  void *handle = get_handle_forma(f);

  switch (tipo) {
  case 'c':
    return get_area_circulo(handle);
  case 'r':
    return get_area_retangulo(handle);
  case 't':
    return get_area_texto(handle);
  case 'l':
    return get_area_linha(handle);
  default:
    return -2;
  }
}

double get_largura_forma(Forma f) {
  if (!f)
    return -1;
  char tipo = get_tipo_forma(f);
  void *handle = get_handle_forma(f);

  switch (tipo) {
  case 'c':
    return 2 * get_raio_circulo(handle);
  case 'r':
    return get_w_retangulo(handle);
  case 't':
    return strlen(get_palavra_texto(handle));
  case 'l':
    return get_comprimento_linha(handle);
  default:
    return -2;
  }
}

double get_altura_forma(Forma f) {
  if (!f)
    return -1;
  char tipo = get_tipo_forma(f);
  void *handle = get_handle_forma(f);

  switch (tipo) {
  case 'c':
    return 2 * get_raio_circulo(handle);
  case 'r':
    return get_h_retangulo(handle);
  case 't':
    return 10.0;
  case 'l':
    return 1.5;
  default:
    return -2;
  }
}

char *get_corb_forma(Forma f) {
  if (!f)
    return NULL;
  char tipo = get_tipo_forma(f);
  void *handle = get_handle_forma(f);

  switch (tipo) {
  case 'c':
    return get_corb_circulo(handle);
  case 'r':
    return get_corb_retangulo(handle);
  case 't':
    return get_corb_texto(handle);
  case 'l':
    return get_cor_linha(handle);
  default:
    return NULL;
  }
}

char *get_corp_forma(Forma f) {
  if (!f)
    return NULL;
  char tipo = get_tipo_forma(f);
  void *handle = get_handle_forma(f);

  switch (tipo) {
  case 'c':
    return get_corp_circulo(handle);
  case 'r':
    return get_corp_retangulo(handle);
  case 't':
    return get_corp_texto(handle);
  case 'l':
    return get_cor_linha(handle);
  default:
    return NULL;
  }
}

bool set_ancora_forma(Forma f, double x, double y) {
  if (!f)
    return false;

  StForma *forma = (StForma *)f;

  switch (forma->tipo) {
  case 'c':
    return set_x_circulo(forma->handle, x) && set_y_circulo(forma->handle, y);
  case 'r':
    return set_x_retangulo(forma->handle, x) &&
           set_y_retangulo(forma->handle, y);
  case 't':
    return set_x_texto(forma->handle, x) && set_y_texto(forma->handle, y);
  case 'l':
    return set_ancora_linha(forma->handle, x, y);

  default:
    return false;
  }
}

void set_x_forma(Forma f, double x) {
  if (!f)
    return;

  StForma *forma = (StForma *)f;
  void *handle = get_handle_forma(f);
  switch (forma->tipo) {
  case 'c':
    set_x_circulo(handle, x);
  case 'r':
    set_x_retangulo(handle, x);
  case 't':
    set_x_texto(handle, x);
  case 'l':
    set_ancora_linha(handle, x, get_y1_linha(handle));

  default:
    return;
  }
}

void set_y_forma(Forma f, double y) {
  if (!f)
    return;

  StForma *forma = (StForma *)f;
  void *handle = get_handle_forma(f);
  switch (forma->tipo) {
  case 'c':
    set_y_circulo(handle, y);
  case 'r':
    set_y_retangulo(handle, y);
  case 't':
    set_y_texto(handle, y);
  case 'l':
    set_ancora_linha(handle, get_x1_linha(handle), y);

  default:
    return;
  }
}

void set_corb_forma(Forma f, char *corb) {
  if (!f || !corb)
    return;

  Forma figura = get_handle_forma(f);
  switch (get_tipo_forma(f)) {
  case 'c': {
    set_corb_circulo(figura, corb);
    break;
  }
  case 'r': {
    set_corb_retangulo(figura, corb);
    break;
  }
  case 't': {
    set_corb_texto(figura, corb);
    break;
  }
  case 'l': {
    set_cor(figura, corb);
    break;
  }
  }
  return;
}

void set_corp_forma(Forma f, char *corp) {
  if (!f || !corp)
    return;

  Forma figura = get_handle_forma(f);
  switch (get_tipo_forma(f)) {
  case 'c': {
    set_corp_circulo(figura, corp);
    break;
  }
  case 'r': {
    set_corp_retangulo(figura, corp);
    break;
  }
  case 't': {
    set_corp_texto(figura, corp);
    break;
  }
  default:
    break;
  }
  return;
}

bool desloca_forma(Forma f, double dx, double dy) {
  if (!f)
    return false;

  double x, y;

  if (!get_ancora_forma(f, &x, &y))
    return false;

  return set_ancora_forma(f, x + dx, y + dy);
}
