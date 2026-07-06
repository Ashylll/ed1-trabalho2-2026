#include "processa_qry.h"
#include "arvore.h"
#include "forma.h"
#include "retangulo.h"
#include "sorting.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static Forma *formas_selecionadas = NULL;
static int n_selecionadas = 0;

static void clona_move_forma(Arvore formas, double dx, double dy) {
  for (int i = 0; i < n_selecionadas; i++) {
    Forma clone = clona_forma(formas_selecionadas[i]);
    desloca_forma(clone, dx, dy);
    
    insere_arvore(formas, clone);
    formas_selecionadas[i] = clone;
  }
}

static void cm(double x, double y, double w, double h, double dx, double dy,
               Arvore formas, Arvore formas_marcadores) {
  Forma retangulo_sel = cria_forma(
      'r', cria_retangulo(ID_RETANGULO_SEL, x, y, w, h, "red", "none"));
  insere_arvore(formas_marcadores, retangulo_sel);

  n_selecionadas = 0;
  formas_selecionadas_para_vetor(formas, retangulo_sel, formas_selecionadas,
                                 &n_selecionadas);

  clona_move_forma(formas, dx, dy);

  for (int i = 0; i < n_selecionadas; i++) {
    insere_arvore(formas, formas_selecionadas[i]);
  }
}

static void comando_cm(const char *linha, FILE *fp_qry, FILE *fp_log,
                       Arvore formas, Arvore formas_marcadores) {
  double x, y, w, h, dx, dy;

  if (sscanf(linha, "%*s %lf %lf %lf %lf %lf %lf", &x, &y, &w, &h, &dx, &dy) !=
      6)
    return;
  fprintf(fp_log, "[*] cm %lf %lf %lf %lf %lf %lf\n", x, y, w, h, dx, dy);

  cm(x, y, w, h, dx, dy, formas, formas_marcadores);
}

static void sel(double x, double y, double w, double h, Arvore formas,
                Arvore formas_marcadores) {
  Forma retangulo_sel =
      cria_forma('r', cria_retangulo(ID_RETANGULO_SEL, x, y, w, h,
                                     CORB_RETANGULO_SEL, CORP_RETANGULO_SEL));
  insere_arvore(formas_marcadores, retangulo_sel);

  n_selecionadas = 0;
  formas_selecionadas_para_vetor(formas, retangulo_sel, formas_selecionadas,
                                 &n_selecionadas);
}

static void comando_sel(const char *linha, FILE *fp_qry, FILE *fp_log,
                        Arvore formas, Arvore formas_marcadores) {
  double x, y, w, h;

  if (sscanf(linha, "%*s %lf %lf %lf %lf", &x, &y, &w, &h) != 4)
    return;
  fprintf(fp_log, "[*] sel %lf %lf %lf %lf\n", x, y, w, h);

  sel(x, y, w, h, formas, formas_marcadores);

  if (n_selecionadas > 0)
    fprintf(fp_log, "Formas selecionadas:\n\n");
  else
    fprintf(fp_log, "Nenhuma forma selecionada\n\n");

  for (int i = 0; i < n_selecionadas; i++) {
    int id = get_id_forma(formas_selecionadas[i]);
    char tipo = get_tipo_forma(formas_selecionadas[i]);

    fprintf(fp_log, "Id: %d\nTipo: %s\n\n", id, traduz_tipo_forma(tipo, false));
  }
}

static void cria_quadrados_marcadores(Arvore formas_marcadores, int k) {
  for (int i = 0; i < k; i++) {
    double x, y;

    get_ancora_forma(formas_selecionadas[i], &x, &y);
    Forma quadrado_ancora = cria_forma(
        'r', cria_retangulo(ID_QUADRADO_MARCA, x, y, LADO_QUADRADO_MARCA,
                            LADO_QUADRADO_MARCA, CORB_QUADRADO_MARCA,
                            CORP_QUADRADO_MARCA));

    insere_arvore(formas_marcadores, quadrado_ancora);
  }
}

static void remove_formas_maiores(Arvore formas, int k) {
  for (int i = k; i < n_selecionadas; i++) {
    remove_arvore(formas, formas_selecionadas[i]);
    libera_forma(formas_selecionadas[i]);
    formas_selecionadas[i] = NULL;
  }
}

static void atualiza_posicao_formas(Arvore formas, double x, double y,
                                    double dw) {
  double dx = 0;
  double cx, cy;

  for (int i = 0; i < n_selecionadas; i++) {
    Forma f = formas_selecionadas[i];
    double l = get_largura_x_forma(f);

    get_correcao_ancora(f, &cx, &cy);
    set_x_forma(formas_selecionadas[i], x + dx + cx);
    set_y_forma(formas_selecionadas[i], y + cy);

    dx += l + dw;
  }
}

static void find(FILE *fp_log, int k, char *alg, char crit, double x, double y,
                 double dw, const char *comb_out, Arvore formas,
                 Arvore formas_marcadores, bool rm) {
  compara_formas_t criterio_ordenacao;

  switch (crit) {
  case 'd':
    cria_quadrados_marcadores(formas_marcadores, k);
    if (rm)
      remove_formas_maiores(formas, k);
    fprintf(fp_log, "Critério \"default\". Formas já ordenadas\n");
    return;

  case 'a':
    criterio_ordenacao = compara_area;
    break;
  case 'w':
    criterio_ordenacao = compara_largura;
    break;
  case 'h':
    criterio_ordenacao = compara_altura;
    break;
  case 'c':
    criterio_ordenacao = compara_cor_preenchimento;
    break;
  default:
    criterio_ordenacao = NULL;
    break;
  }

  if (strcmp(alg, "bs") == 0)
    bubble_sort_animado(comb_out, formas_selecionadas, n_selecionadas, k,
                        criterio_ordenacao);
  /*
  else if (strcmp(alg, "ss") == 0) selection_sort_animado();
  else if (strcmp(alg, "is") == 0) insertion_sort_animado();
  else if (strcmp(alg, "shs") == 0) shell_sort_animado();
  else if (strcmp(alg, "qs") == 0) quick_sort_animado();
  else if (strcmp(alg, "ms") == 0) merge_sort_animado();
  */

  for (int i = 0; i < n_selecionadas; i++) {
    remove_arvore(formas, formas_selecionadas[i]);
  }

  atualiza_posicao_formas(formas, x, y, dw);

  for (int i = 0; i < n_selecionadas; i++) {
    insere_arvore(formas, formas_selecionadas[i]);
  }

  cria_quadrados_marcadores(formas_marcadores, k);

  if (rm)
    remove_formas_maiores(formas_selecionadas, k);
}

static void comando_find(const char *linha, const char *comb_out, FILE *fp_qry,
                         FILE *fp_log, Arvore formas, Arvore formas_marcadores,
                         bool rm) {
  int k;
  char alg[8];
  char crit;
  double x, y, dw;
  if (sscanf(linha, "%*s %d %s %c %lf %lf %lf", &k, alg, &crit, &x, &y, &dw) !=
      6)
    return;

  if (rm)
    fprintf(fp_log, "[*] findrm %d %s %c %lf %lf %lf\n", k, alg, crit, x, y,
            dw);
  else
    fprintf(fp_log, "[*] find %d %s %c %lf %lf %lf\n", k, alg, crit, x, y, dw);

  if (n_selecionadas <= 0) {
    fprintf(fp_log, "Nenhuma forma selecionada para ordenação\n\n");
    return;
  }

  find(fp_log, k, alg, crit, x, y, dw, comb_out, formas, formas_marcadores, rm);

  fprintf(fp_log, "Formas selecionadas segundo o critério:\n");
  for (int i = 0; i < n_selecionadas; i++) {
    reporta_forma(fp_log, formas_selecionadas[i], crit);
  }
}

static void comando_mc() {
  for (int i = 0; i < n_selecionadas; i++) {
    troca_cores_forma(formas_selecionadas[i]);
  }
}

bool processa_qry(const char *path_qry, const char *path_log,
                  const char *comb_out, Arvore formas,
                  Arvore formas_marcadores) {
  FILE *fp_qry = fopen(path_qry, "r");
  FILE *fp_log = fopen(path_log, "w");
  if (!fp_qry || !fp_log)
    return false;

  int tamanho_arvore = get_tamanho_arvore(formas);
  formas_selecionadas = malloc(tamanho_arvore * sizeof(Forma));

  char linha[1024], comando[8];

  while (fgets(linha, sizeof linha, fp_qry)) {
    if (sscanf(linha, "%7s", comando) != 1)
      continue;

    if (comando[0] == '#')
      continue;

    if (strcmp(comando, "sel") == 0) {
      comando_sel(linha, fp_qry, fp_log, formas, formas_marcadores);
    } else if (strcmp(comando, "find") == 0) {
      comando_find(linha, comb_out, fp_qry, fp_log, formas, formas_marcadores,
                   false);
    } else if (strcmp(comando, "cm") == 0) {
      comando_sel(linha, fp_qry, fp_log, formas, formas_marcadores);
    } else if (strcmp(comando, "findrm") == 0) {
      comando_find(linha, comb_out, fp_qry, fp_log, formas, formas_marcadores,
                   true);
    } else if (strcmp(comando, "mc") == 0) {
      comando_mc();
    } else {
      return false;
    }
  }

  free(formas_selecionadas);
  fclose(fp_qry);
  fclose(fp_log);
  return true;
}
