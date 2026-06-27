#include "arvore.h"
#include "circulo.h"
#include "forma.h"
#include "leitura_geo.h"
#include "linha.h"
#include "retangulo.h"
#include "sorting.h"
#include "unity.h"
#include <string.h>

Arvore arvore_teste;
void setUp(void) { arvore_teste = cria_arvore(compara_default); }
void tearDown(void) { libera_arvore(&arvore_teste); }

void teste_cria_libera_arvore(void) {
  Arvore arvore = cria_arvore(NULL);
  TEST_ASSERT_NULL(arvore);
  arvore = cria_arvore(compara_default);
  TEST_ASSERT_NOT_NULL(arvore);

  Linha l1 = cria_linha(-2, 2.0, 8.0, 4.0, 6.0, "pink");
  Linha l2 = cria_linha(-4, 2.0, 9.0, 4.0, 6.0, "pink");
  Forma f1 = cria_forma('l', l1);
  Forma f2 = cria_forma('l', l2);
  insere_arvore(arvore, f1);
  insere_arvore(arvore, f2);

  libera_arvore(&arvore);
  TEST_ASSERT_NULL(arvore);
}

void teste_insere_remove_tamanho_arvore(void) {
  Linha l1 = cria_linha(-2, 2.0, 9.0, 4.0, 6.0, "pink");
  Linha l2 = cria_linha(-2, 2.0, 8.0, 4.0, 6.0, "pink");
  Linha l3 = cria_linha(-2, 2.0, 7.0, 4.0, 6.0, "pink");

  Forma f1 = cria_forma('l', l1);
  Forma f2 = cria_forma('l', l2);
  Forma f3 = cria_forma('l', l3);
  insere_arvore(arvore_teste, f1);
  insere_arvore(arvore_teste, f2);
  insere_arvore(arvore_teste, f3);
  TEST_ASSERT_EQUAL_INT(3, get_tamanho_arvore(arvore_teste));

  remove_arvore(arvore_teste, f2);
  TEST_ASSERT_EQUAL_INT(2, get_tamanho_arvore(arvore_teste));
  remove_arvore(arvore_teste, f1);
  TEST_ASSERT_EQUAL_INT(1, get_tamanho_arvore(arvore_teste));
  remove_arvore(arvore_teste, f3);
  TEST_ASSERT_EQUAL_INT(0, get_tamanho_arvore(arvore_teste));
}

void teste_escreve_arvore_svg(void) {
  char *path_in = "teste_leitura.geo";
  FILE *fp_geo = fopen(path_in, "w");
  fprintf(fp_geo, "c 10 50.0 50.0 20.0 blue red\n");
  fprintf(fp_geo, "r 20 10.0 10.0 100.0 200.0 green yellow\n");
  fprintf(fp_geo, "ts sans-serif bold 14.0\n");
  fprintf(fp_geo, "t 30 0.0 0.0 black black i Texto de Teste\n");
  fclose(fp_geo);
  leitura_geo(path_in, arvore_teste);

  char *path_out_teste = "teste_escrita.svg";
  FILE *fp_svg = fopen(path_out_teste, "w");
  escreve_arvore_svg(fp_svg, arvore_teste);
  fclose(fp_svg);

  FILE *checa = fopen(path_out_teste, "r");
  TEST_ASSERT_NOT_NULL(checa);

  char linha[256];
  bool tem_circulo = false;
  bool tem_retangulo = false;
  bool tem_texto = false;
  bool tem_txto = false;
  while (fgets(linha, sizeof(linha), checa)) {
    if (strstr(linha, "<circle"))
      tem_circulo = true;
    if (strstr(linha, "<rect"))
      tem_retangulo = true;
    if (strstr(linha, "<text"))
      tem_texto = true;
    if (strstr(linha, "Texto de Teste"))
      tem_txto = true;
  }

  TEST_ASSERT_TRUE(tem_circulo);
  TEST_ASSERT_TRUE(tem_retangulo);
  TEST_ASSERT_TRUE(tem_texto);
  TEST_ASSERT_TRUE(tem_txto);

  fclose(checa);
  remove(path_in);
  remove(path_out_teste);
}

void teste_formas_selecionadas_para_vetor(void) {
  Forma ret_sel = cria_forma(
      'r', cria_retangulo(-1, 0.0, 0.0, 100.0, 100.0, "red", "none"));
  Forma f_dentro1 = cria_forma(
      'r', cria_retangulo(1, 10.0, 10.0, 10.0, 10.0, "blue", "blue"));
  Forma f_dentro2 =
      cria_forma('c', cria_circulo(2, 20.0, 20.0, 5.0, "blue", "blue"));
  Forma f_fora = cria_forma(
      'r', cria_retangulo(3, 500.0, 500.0, 10.0, 10.0, "blue", "blue"));

  insere_arvore(arvore_teste, f_dentro1);
  insere_arvore(arvore_teste, f_dentro2);
  insere_arvore(arvore_teste, f_fora);

  Forma vetor[10];
  int n = 0;

  formas_selecionadas_para_vetor(arvore_teste, ret_sel, vetor, &n);

  TEST_ASSERT_EQUAL_INT(2, n);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(teste_cria_libera_arvore);
  RUN_TEST(teste_insere_remove_tamanho_arvore);
  RUN_TEST(teste_escreve_arvore_svg);
  RUN_TEST(teste_formas_selecionadas_para_vetor);
  return UNITY_END();
}
