#include "arvore.h"
#include "circulo.h"
#include "forma.h"
#include "leitura_geo.h"
#include "linha.h"
#include "retangulo.h"
#include "sorting.h"
#include "svg.h"
#include "texto.h"
#include "unity.h"
#include <stdio.h>
#include <stdlib.h>

static bool esta_ordenado(Forma vetor[], int n, compara_formas_t cmp) {
    for (int i = 0; i < n - 1; i++) {
        if (cmp(vetor[i], vetor[i+1]) > 0) {
            return false;
        }
    }
    return true;
}

char *path_teste = "teste_leitura.geo";
Arvore arvore_teste;
Forma vet_sel;
void setUp(void) {
  arvore_teste = cria_arvore(compara_default);
  vet_sel = malloc(100 * sizeof(Forma));
  FILE *fp_geo = fopen(path_teste, "w");
  fprintf(fp_geo, "c 1 65.0 50.0 10.0 red blue\n");
  fprintf(fp_geo, "r 2 130.0 40.0 30.0 20.0 black yellow\n");
  fprintf(fp_geo, "l 3 100.0 40.0 120.0 100.0 green\n");
  fprintf(fp_geo, "t 4 10.0 100.0 red blue i maionese\n");
  fprintf(fp_geo, "c 1 30.0 50.0 10.0 red blue\n");

  fprintf(fp_geo, "r 2 90.0 40.0 30.0 20.0 black yellow\n");
  fprintf(fp_geo, "l 3 150.0 40.0 150.0 80.0 green\n");
  fprintf(fp_geo, "t 4 210.0 40.0 red blue i maionese\n");
  fprintf(fp_geo, "c 5 270.0 65.0 25.0 purple orange\n");
  fprintf(fp_geo, "r 6 330.0 40.0 40.0 50.0 white gray\n");
  fprintf(fp_geo, "l 7 390.0 40.0 410.0 90.0 pink\n");
  fprintf(fp_geo, "t 8 450.0 40.0 black white i ketchup\n");

  fclose(fp_geo);
  leitura_geo(path_teste, arvore_teste);
  gera_svg_inicial("t1-inicial.svg", arvore_teste);
}

void tearDown(void) {
  libera_arvore(&arvore_teste);
  free(vet_sel);

  system("rm *.svg");
}

void teste_compara_formas(void) {
  Retangulo r = cria_retangulo(1, 4.0, 0.0, 10.0, 10.0, "black", "white");
  Linha l = cria_linha(3, 6.0, 2.0, 6.0, 6.0, "green");
  Forma f1 = cria_forma('r', r);
  Forma f2 = cria_forma('l', l);

  TEST_ASSERT_EQUAL_INT(-1, compara_default(f1, f2));
  TEST_ASSERT_EQUAL_INT(1, compara_area(f1, f2));
  TEST_ASSERT_EQUAL_INT(1, compara_largura(f1, f2));
  TEST_ASSERT_EQUAL_INT(-1, compara_altura(f2, f1));
  TEST_ASSERT_EQUAL_INT(1, compara_cor_preenchimento(f1, f2));
  libera_forma(&f1);
  libera_forma(&f2);

  Circulo c = cria_circulo(1, 4.2, -4.8, 4.0, "#AA1244", "#884466");
  Texto t = cria_texto(1, 4.2, -4.8, "#AAAAAA", "#88CCAA", 'm', ":3");
  f1 = cria_forma('c', c);
  f2 = cria_forma('t', t);

  TEST_ASSERT_EQUAL_INT(1, compara_default(f1, f2));
  TEST_ASSERT_EQUAL_INT(-1, compara_area(f2, f1));
  TEST_ASSERT_EQUAL_INT(1, compara_largura(f1, f2));
  TEST_ASSERT_EQUAL_INT(1, compara_altura(f2, f1));
  TEST_ASSERT_EQUAL_INT(-1, compara_cor_preenchimento(f1, f2));

  libera_forma(&f1);
  libera_forma(&f2);
}

void teste_dentro_selecao(void) {
    Retangulo ret_selecao_raw = cria_retangulo(-1, 0.0, 0.0, 100.0, 100.0, "none", "none");
    Forma sel = cria_forma('r', ret_selecao_raw);

    Retangulo r_in = cria_retangulo(1, 10.0, 10.0, 20.0, 20.0, "red", "red");
    Forma f_r_in = cria_forma('r', r_in);
    TEST_ASSERT_TRUE(dentro_selecao(f_r_in, sel));

    Retangulo r_out = cria_retangulo(2, 200.0, 200.0, 20.0, 20.0, "blue", "blue");
    Forma f_r_out = cria_forma('r', r_out);
    TEST_ASSERT_FALSE(dentro_selecao(f_r_out, sel));

    Circulo c_in = cria_circulo(3, 50.0, 50.0, 10.0, "green", "green");
    Forma f_c_in = cria_forma('c', c_in);
    TEST_ASSERT_TRUE(dentro_selecao(f_c_in, sel));

    Linha l_out = cria_linha(4, 150.0, 150.0, 200.0, 200.0, "black");
    Forma f_l_out = cria_forma('l', l_out);
    TEST_ASSERT_FALSE(dentro_selecao(f_l_out, sel));

    libera_forma(&sel);
    libera_forma(&f_r_in);
    libera_forma(&f_r_out);
    libera_forma(&f_c_in);
    libera_forma(&f_l_out);
}

void teste_bubble_sort_animado(void) {
  char *path_svg = "t1-bubble.svg";
  Forma ret_sel = cria_forma('r', cria_retangulo(-1, 0.0, 0.0, 200.0, 200.0, "red", "none"));

  int n = 0;
  formas_selecionadas_para_vetor(arvore_teste, ret_sel, vet_sel, &n);
  
  bubble_sort_animado(path_svg, vet_sel, n, 100, compara_area);
  
  TEST_ASSERT_TRUE(esta_ordenado(vet_sel, n, compara_area));

  libera_forma(&ret_sel);
}

void teste_selection_sort_animado(void) {
  char *path_svg = "t1-selection.svg";
  Forma ret_sel = cria_forma('r', cria_retangulo(-1, 0.0, 0.0, 200.0, 200.0, "red", "none"));

  int n = 0;
  formas_selecionadas_para_vetor(arvore_teste, ret_sel, vet_sel, &n);
  
  selection_sort_animado(path_svg, vet_sel, n, 100, compara_area);
  
  TEST_ASSERT_TRUE(esta_ordenado(vet_sel, n, compara_area));

  libera_forma(&ret_sel);
}

void teste_insertion_sort_animado(void) {
  char *path_svg = "t1-insertion.svg";
  Forma ret_sel = cria_forma('r', cria_retangulo(-1, 0.0, 0.0, 200.0, 200.0, "red", "none"));

  int n = 0;
  formas_selecionadas_para_vetor(arvore_teste, ret_sel, vet_sel, &n);
  
  insertion_sort_animado(path_svg, vet_sel, n, 100, compara_area);
  
  TEST_ASSERT_TRUE(esta_ordenado(vet_sel, n, compara_area));

  libera_forma(&ret_sel);
}

void teste_shell_sort_animado(void) {
  char *path_svg = "t1-shell.svg";
  Forma ret_sel = cria_forma('r', cria_retangulo(-1, 0.0, 0.0, 200.0, 200.0, "red", "none"));

  int n = 0;
  formas_selecionadas_para_vetor(arvore_teste, ret_sel, vet_sel, &n);
  
  shell_sort_animado(path_svg, vet_sel, n, compara_area);
  
  TEST_ASSERT_TRUE(esta_ordenado(vet_sel, n, compara_area));

  libera_forma(&ret_sel);
}

void teste_quick_sort_animado(void) {
  char *path_svg = "t1-quick.svg";
  Forma ret_sel = cria_forma('r', cria_retangulo(-1, 0.0, 0.0, 200.0, 200.0, "red", "none"));

  int n = 0;
  formas_selecionadas_para_vetor(arvore_teste, ret_sel, vet_sel, &n);
  
  quick_sort_animado(path_svg, vet_sel, n, compara_area);
  
  TEST_ASSERT_TRUE(esta_ordenado(vet_sel, n, compara_area));

  libera_forma(&ret_sel);
}

void teste_merge_sort_animado(void) {
  char *path_svg = "t1-merge.svg";
  Forma ret_sel = cria_forma('r', cria_retangulo(-1, 0.0, 0.0, 200.0, 200.0, "red", "none"));

  int n = 0;
  formas_selecionadas_para_vetor(arvore_teste, ret_sel, vet_sel, &n);
  
  merge_sort_animado(path_svg, vet_sel, n, compara_area);
  
  TEST_ASSERT_TRUE(esta_ordenado(vet_sel, n, compara_area));

  libera_forma(&ret_sel);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(teste_compara_formas);
  RUN_TEST(teste_dentro_selecao);
  RUN_TEST(teste_bubble_sort_animado);
  RUN_TEST(teste_selection_sort_animado);
  RUN_TEST(teste_insertion_sort_animado);
  RUN_TEST(teste_shell_sort_animado);
  RUN_TEST(teste_quick_sort_animado);
  RUN_TEST(teste_merge_sort_animado);
  return UNITY_END();
}