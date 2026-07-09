#include "forma.h"
#include "circulo.h"
#include "arvore.h"
#include "leitura_geo.h"
#include "processa_qry.h"
#include "sorting.h"
#include "unity.h"
#include <stdio.h>

FILE *fp_qry;
FILE *fp_txt;
FILE *fp_comb;
char *path_geo = "teste.geo";
char *path_qry;
char *path_txt = "teste.txt";
char *path_svg = "geo-teste.svg";
Arvore formas, formas_marcadores;
void setUp(void) {
  formas = cria_arvore(compara_default);
  formas_marcadores = cria_arvore(compara_default);

  FILE *fp_geo = fopen(path_geo, "w");
  fprintf(fp_geo, "l 1 10.0 10.0 40.0 40.0 green\n");
  fprintf(fp_geo, "c 2 30.0 50.0 10.0 red blue\n");
  fprintf(fp_geo, "r 3 90.0 40.0 45.0 15.0 black yellow\n");
  fprintf(fp_geo, "c 4 150.0 60.0 20.0 green white\n");
  fprintf(fp_geo, "r 5 210.0 40.0 20.0 50.0 orange black\n");
  fprintf(fp_geo, "c 6 270.0 75.0 35.0 purple gray\n");
  fprintf(fp_geo, "r 7 330.0 40.0 30.0 30.0 blue pink\n");
  fprintf(fp_geo, "c 8 390.0 45.0 5.0 brown cyan\n");
  fprintf(fp_geo, "r 9 450.0 40.0 50.0 70.0 red yellow\n");
  fprintf(fp_geo, "t 10 10.0 100.0 red blue i maionese\n");
  fclose(fp_geo);

  leitura_geo(path_geo, formas);
}

void tearDown(void) {

  remove(path_txt);
  remove(path_svg);
  remove(path_geo);
  remove(path_qry);
  libera_arvore(&formas);
  libera_arvore(&formas_marcadores);

}

void teste_comando_sel(void) {
  path_qry = "teste-sel.qry";
  fp_qry = fopen(path_qry, "w");
  fprintf(fp_qry, "sel 0.0 0.0 500.0 500.0\n"); 
  fclose(fp_qry);

  bool sucesso = processa_qry(path_qry, path_txt, path_svg, formas, formas_marcadores);
  TEST_ASSERT_TRUE(sucesso);
  
  TEST_ASSERT_TRUE(get_tamanho_arvore(formas_marcadores) > 0);
}

void teste_comando_cm(void) {
  path_qry = "teste-cm.qry";
  int tam_antes = get_tamanho_arvore(formas);

  fp_qry = fopen(path_qry, "w");
  fprintf(fp_qry, "cm 10.0 10.0 200.0 200.0 300.0 300.0\n");
  fclose(fp_qry);

  bool sucesso = processa_qry(path_qry, path_txt, path_svg, formas, formas_marcadores);
  TEST_ASSERT_TRUE(sucesso);

  int tam_depois = get_tamanho_arvore(formas);
  TEST_ASSERT_TRUE(tam_depois > tam_antes);
}

void teste_comando_mc(void) {
  Arvore mc = cria_arvore(compara_default);
  Forma c = cria_forma('c', cria_circulo(2, 20.0, 20.0, 4.0, "yellow", "pink"));
  insere_arvore(mc, c);

  path_qry = "teste-mc.qry";
  fp_qry = fopen(path_qry, "w");
  fprintf(fp_qry, "sel 10.0 10.0 200.0 200.0\n");
  fprintf(fp_qry, "mc white white\n");
  fclose(fp_qry);

  bool sucesso = processa_qry(path_qry, path_txt, path_svg, mc, formas_marcadores);
  TEST_ASSERT_TRUE(sucesso);
  
  TEST_ASSERT_EQUAL_STRING("white", get_corb_forma(c));
  TEST_ASSERT_EQUAL_STRING("white", get_corp_forma(c));

  libera_arvore(&mc);
}


void teste_comandos_find_findrm(void) {
  path_qry = "teste-find-findrm.qry";
  fp_qry = fopen(path_qry, "w");
  
  fprintf(fp_qry, "sel 0.0 0.0 500.0 500.0\n");
  fprintf(fp_qry, "find 3 bs a 100.0 100.0 10.0\n");
  fprintf(fp_qry, "findrm 2 qs a 200.0 200.0 10.0\n");
  fclose(fp_qry);

  int tam_antes = get_tamanho_arvore(formas);
  
  bool sucesso = processa_qry(path_qry, path_txt, path_svg, formas, formas_marcadores);
  
  TEST_ASSERT_TRUE(sucesso);
  
  int tam_depois = get_tamanho_arvore(formas);
  TEST_ASSERT_TRUE(tam_depois < tam_antes);

  system("rm *.svg");
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(teste_comando_sel);
  RUN_TEST(teste_comando_cm);
  RUN_TEST(teste_comando_mc);
  RUN_TEST(teste_comandos_find_findrm);
  return UNITY_END();
}
