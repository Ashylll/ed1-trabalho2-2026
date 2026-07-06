#include "svg.h"
#include "arvore.h"
#include "circulo.h"
#include "forma.h"
#include "linha.h"
#include "retangulo.h"
#include "texto.h"
#include <stdio.h>
#include <string.h>

void svg_begin(FILE *fp) {
  if (!fp)
    return;

  fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
  fprintf(fp, "<svg xmlns:svg=\"http://www.w3.org/2000/svg\" "
              "xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
}

void svg_end(FILE *fp) {
  if (!fp)
    return;

  fprintf(fp, "</svg>\n");
}

void gera_svg_inicial(const char *path_geo_svg, Arvore formas) {
  FILE *fp_svg = fopen(path_geo_svg, "w");

  svg_begin(fp_svg);
  escreve_arvore_svg(fp_svg, formas);
  svg_end(fp_svg);

  fclose(fp_svg);
}

void gera_svg_final(const char *path_comb_svg, Arvore formas,
                    Arvore formas_marcadores) {
  FILE *fp_svg = fopen(path_comb_svg, "w");

  svg_begin(fp_svg);
  escreve_arvore_svg(fp_svg, formas);
  escreve_arvore_svg(fp_svg, formas_marcadores);
  svg_end(fp_svg);

  fclose(fp_svg);
}

void escreve_forma_deslocada_svg(FILE *fp_svg, Forma f, double x, double y) {
  if (!fp_svg || !f)
    return;

  char tipo = get_tipo_forma(f);
  void *handle = get_handle_forma(f);

  switch (tipo) {
  case 'c': {
    double r = get_raio_circulo(handle);
    const char *corb = get_corb_circulo(handle);
    const char *corp = get_corp_circulo(handle);

    double opacidade = 0.6;

    fprintf(fp_svg,
            "<circle "
            "style=\"fill:%s;fill-opacity:%.1f;stroke:%s;stroke-width:1.0\" "
            "r=\"%.2f\" cy=\"%.2f\" cx=\"%.2f\" />\n",
            corp, opacidade, corb, r, y, x);

    break;
  }

  case 'r': {
    double w = get_w_retangulo(handle);
    double h = get_h_retangulo(handle);
    const char *corb = get_corb_retangulo(handle);
    const char *corp = get_corp_retangulo(handle);

    double opacidade = 0.6;

    if (get_id_retangulo(handle) == -1) {
      fprintf(fp_svg,
              "<rect "
              "style=\"fill:%s;fill-opacity:%.1f;stroke:%s;stroke-dasharray:5;"
              "stroke-width:1.0\" x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" "
              "height=\"%.2f\" />\n",
              corp, opacidade, corb, x, y, w, h);
    } else {
      fprintf(fp_svg,
              "<rect "
              "style=\"fill:%s;fill-opacity:%.1f;stroke:%s;stroke-width:1.0\" "
              "x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" />\n",
              corp, opacidade, corb, x, y, w, h);
    }

    break;
  }

  case 'l': {
    Linha l = get_handle_forma(f);
    double y1 = get_y1_linha(l);
    double y2 = get_y2_linha(l);

    double dy = y + y2 - y1;

    double dx = x + get_largura_x_forma(f);

    const char *cor = get_cor_linha(handle);

    double opacidade = 0.8;

    fprintf(fp_svg,
            "<line style=\"stroke:%s;stroke-width:2.0;stroke-opacity:%.1f\" "
            "x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" />\n",
            cor, opacidade, x, y, dx, dy);

    break;
  }

  case 't': {
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
    double size = get_size_texto(handle);

    double opacidade = 1.0;

    fprintf(fp_svg,
            "<text "
            "style=\"text-anchor:%s;alignment-baseline:hanging;fill:%s;fill-"
            "opacity:%.1f;stroke:%s;stroke-width:0.7;"
            "font-family:%s;font-weight:%s;font-size:%lfpx;line-height:0%%\" "
            "x=\"%.2f\" y=\"%.2f\">%s</text>\n",
            ancora, corp, opacidade, corb, family, weight, size, x, y, txto);

    break;
  }

  default:
    fprintf(stderr, "[escreve_forma_svg] tipo desconhecido: %c\n", tipo);
    break;
  }
}

static void remove_extensao(const char *path, char *dest) {
  strcpy(dest, path);

  char *barra = strrchr(dest, '/');
  char *ponto = strrchr(dest, '.');

  if (ponto && (!barra || ponto > barra)) {
    *ponto = '\0';
  }
}

static FILE *cria_file_frame(int numeracao_frame, const char *comb_out) {
  char nome_svg[280];
  char base_comb_svg[256];

  remove_extensao(comb_out, base_comb_svg);
  snprintf(nome_svg, sizeof(nome_svg), "%s%06d.svg", base_comb_svg,
           numeracao_frame);

  FILE *fp = fopen(nome_svg, "w");
  return fp;
}

void escreve_frame(const char *comb_out, int numeracao, double x, double y,
                   double dw, Forma vet_selecionadas[], double n_selecionadas) {
  double dx = 0;
  double cx, cy;
  FILE *fp_svg = cria_file_frame(numeracao, comb_out);

  svg_begin(fp_svg);

  for (int i = 0; i < n_selecionadas; i++) {
    Forma f = vet_selecionadas[i];
    double l = get_largura_x_forma(f);

    get_correcao_ancora(f, &cx, &cy);

    escreve_forma_deslocada_svg(fp_svg, f, x + dx + cx, y + cy);

    dx += l + dw;
  }

  svg_end(fp_svg);
  fclose(fp_svg);
}
