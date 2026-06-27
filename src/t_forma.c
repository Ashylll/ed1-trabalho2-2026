#include "circulo.h"
#include "forma.h"
#include "linha.h"
#include "retangulo.h"
#include "texto.h"
#include "unity.h"
#include <stdio.h>
#include <string.h>

Forma f1, f2, f3, f4;
char *path_svg_teste = "teste.svg";
char *path_txt_teste = "teste.txt";
FILE *fp_svg;
FILE *fp_txt;

void setUp(void) {
  fp_svg = fopen(path_svg_teste, "w");
  fp_txt = fopen(path_txt_teste, "w");
  f1 = cria_forma('t', cria_texto(3, 4.2, 4.4, "pink", "yellow", 'm', "rosa"));
  f2 = cria_forma('r', cria_retangulo(1, 2.2, 4.4, 2.2, 2.2, "purple", "pink"));
  f3 = cria_forma('l', cria_linha(2, 2.0, 2.0, 4.0, 4.0, "pink"));
  f4 = cria_forma('c', cria_circulo(0, 2.2, 4.4, 2, "pink", "pink"));
}
void tearDown(void) {
  libera_forma(&f1);
  libera_forma(&f2);
  libera_forma(&f3);
  libera_forma(&f4);

  fclose(fp_svg);
  fclose(fp_txt);
  remove(path_svg_teste);
  remove(path_txt_teste);
}

void teste_cria_libera_forma(void) {
  Circulo c = cria_circulo(0, 2.2, 4.4, 2, "pink", "pink");
  Forma f = cria_forma('a', c);
  TEST_ASSERT_NULL(f);
  libera_forma(&f);

  f = cria_forma('c', c);
  TEST_ASSERT_NOT_NULL(f);
  TEST_ASSERT_EQUAL_CHAR('c', get_tipo_forma(f));
  TEST_ASSERT_EQUAL_PTR(c, get_handle_forma(f));
  libera_forma(&f);

  Retangulo r = cria_retangulo(1, 2.2, 4.4, 2.2, 2.2, "pink", "pink");
  f = cria_forma('r', r);
  TEST_ASSERT_NOT_NULL(f);
  TEST_ASSERT_EQUAL_CHAR('r', get_tipo_forma(f));
  TEST_ASSERT_EQUAL_PTR(r, get_handle_forma(f));
  libera_forma(&f);

  Linha l = cria_linha(2, 2.0, 2.0, 4.0, 4.0, "pink");
  f = cria_forma('l', l);
  TEST_ASSERT_NOT_NULL(f);
  TEST_ASSERT_EQUAL_CHAR('l', get_tipo_forma(f));
  TEST_ASSERT_EQUAL_PTR(l, get_handle_forma(f));
  libera_forma(&f);

  Texto t = cria_texto(3, 4.2, 4.4, "pink", "pink", 'm', "rosa");
  f = cria_forma('t', t);
  TEST_ASSERT_NOT_NULL(f);
  TEST_ASSERT_EQUAL_CHAR('t', get_tipo_forma(f));
  TEST_ASSERT_EQUAL_PTR(t, get_handle_forma(f));

  libera_forma(&f);
  TEST_ASSERT_NULL(f);
}

void teste_escreve_forma_svg(void) {
  escreve_forma_svg(fp_svg, f1);
  escreve_forma_svg(fp_svg, f2);
  escreve_forma_svg(fp_svg, f3);
  escreve_forma_svg(fp_svg, f4);

  fclose(fp_svg);

  FILE *checa = fopen(path_svg_teste, "r");
  TEST_ASSERT_NOT_NULL(checa);

  char linha[256];
  bool tem_circulo = false;
  bool tem_retangulo = false;
  bool tem_texto = false;
  bool tem_linha = false;
  while (fgets(linha, sizeof(linha), checa)) {
    if (strstr(linha, "<circle"))
      tem_circulo = true;
    if (strstr(linha, "<rect"))
      tem_retangulo = true;
    if (strstr(linha, "<text"))
      tem_texto = true;
    if (strstr(linha, "<line"))
      tem_linha = true;
  }

  TEST_ASSERT_TRUE(tem_circulo);
  TEST_ASSERT_TRUE(tem_retangulo);
  TEST_ASSERT_TRUE(tem_texto);
  TEST_ASSERT_TRUE(tem_linha);

  fclose(checa);
  remove(path_svg_teste);
  libera_forma(&f1);
  libera_forma(&f2);
  libera_forma(&f3);
  libera_forma(&f4);
}

void teste_clona_forma(void) {
  Forma f1_clone = clona_forma(f1);
  Forma f2_clone = clona_forma(f2);

  int id = get_id_forma(f1_clone);
  double x = get_x_forma(f1_clone);
  double y = get_y_forma(f1_clone);
  char *corb = get_corb_forma(f1_clone);
  char *corp = get_corp_forma(f1_clone);
  TEST_ASSERT_EQUAL_INT(-10, id);
  TEST_ASSERT_EQUAL_DOUBLE(get_x_forma(f1), x);
  TEST_ASSERT_EQUAL_DOUBLE(get_y_forma(f1), y);
  TEST_ASSERT_EQUAL_STRING(get_corb_forma(f1), corb);
  TEST_ASSERT_EQUAL_STRING(get_corp_forma(f1), corp);

  id = get_id_forma(f2_clone);
  x = get_x_forma(f2_clone);
  y = get_y_forma(f2_clone);
  corb = get_corb_forma(f2_clone);
  corp = get_corp_forma(f2_clone);
  TEST_ASSERT_EQUAL_INT(-10, id);
  TEST_ASSERT_EQUAL_DOUBLE(get_x_forma(f2), x);
  TEST_ASSERT_EQUAL_DOUBLE(get_y_forma(f2), y);
  TEST_ASSERT_EQUAL_STRING(get_corb_forma(f2), corb);
  TEST_ASSERT_EQUAL_STRING(get_corp_forma(f2), corp);

  libera_forma(&f1_clone);
  libera_forma(&f2_clone);
}

void teste_troca_cores_forma(void) {
  troca_cores_forma(f1);
  troca_cores_forma(f2);

  TEST_ASSERT_EQUAL_STRING("yellow", get_corb_forma(f1));
  TEST_ASSERT_EQUAL_STRING("pink", get_corp_forma(f1));

  TEST_ASSERT_EQUAL_STRING("pink", get_corb_forma(f2));
  TEST_ASSERT_EQUAL_STRING("purple", get_corp_forma(f2));
}

void teste_traduz_tipo_forma(void) {
  TEST_ASSERT_EQUAL_STRING("Texto", traduz_tipo_forma('t', true));
  TEST_ASSERT_EQUAL_STRING("texto", traduz_tipo_forma('t', false));
  TEST_ASSERT_EQUAL_STRING("Retângulo", traduz_tipo_forma('r', true));
  TEST_ASSERT_EQUAL_STRING("retângulo", traduz_tipo_forma('r', false));
  TEST_ASSERT_EQUAL_STRING("Linha", traduz_tipo_forma('l', true));
  TEST_ASSERT_EQUAL_STRING("linha", traduz_tipo_forma('l', false));
  TEST_ASSERT_EQUAL_STRING("Círculo", traduz_tipo_forma('c', true));
  TEST_ASSERT_EQUAL_STRING("círculo", traduz_tipo_forma('c', false));
}

void teste_reporta_forma(void) {
  reporta_forma(fp_txt, f1, 'd');
  reporta_forma(fp_txt, f2, 'a');
  reporta_forma(fp_txt, f3, 'c');
  reporta_forma(fp_txt, f4, 'h');

  fclose(fp_txt);

  FILE *checa = fopen(path_txt_teste, "r");
  TEST_ASSERT_NOT_NULL(checa);

  char linha[256];
  bool tem_texto = false;
  bool tem_retangulo = false;
  bool tem_linha = false;
  bool tem_circulo = false;
  while (fgets(linha, sizeof(linha), checa)) {
    if (strstr(linha, "== Texto =="))
      tem_texto = true;
    if (strstr(linha, "== Retângulo =="))
      tem_retangulo = true;
    if (strstr(linha, "== Linha =="))
      tem_linha = true;
    if (strstr(linha, "== Círculo =="))
      tem_circulo = true;
  }

  TEST_ASSERT_TRUE(tem_texto);
  TEST_ASSERT_TRUE(tem_retangulo);
  TEST_ASSERT_TRUE(tem_linha);
  TEST_ASSERT_TRUE(tem_circulo);
}

void teste_get_correcao_ancora(void) {
  double dx, dy;
  get_correcao_ancora(f1, &dx, &dy);
  TEST_ASSERT_EQUAL_DOUBLE(get_largura_forma(f1) / 2, dx);
  TEST_ASSERT_EQUAL_DOUBLE(0.0, dy);

  get_correcao_ancora(f2, &dx, &dy);
  TEST_ASSERT_EQUAL_DOUBLE(0.0, dx);
  TEST_ASSERT_EQUAL_DOUBLE(0.0, dy);

  get_correcao_ancora(f3, &dx, &dy);
  TEST_ASSERT_EQUAL_DOUBLE(0.0, dx);
  TEST_ASSERT_EQUAL_DOUBLE(0.0, dy);

  Forma fl = cria_forma('l', cria_linha(2, 2.0, 6.0, 4.0, 4.0, "pink"));
  get_correcao_ancora(fl, &dx, &dy);
  TEST_ASSERT_EQUAL_DOUBLE(2.0, dy);
  libera_forma(&fl);

  get_correcao_ancora(f4, &dx, &dy);
  TEST_ASSERT_EQUAL_DOUBLE(2.0, dx);
  TEST_ASSERT_EQUAL_DOUBLE(2.0, dy);
}

void teste_getters_forma(void) {
  Linha l = cria_linha(-2, 2.0, 8.0, 4.0, 6.0, "pink");
  Forma f = cria_forma('l', l);

  TEST_ASSERT_EQUAL_INT(-2, get_id_forma(f));     // id
  TEST_ASSERT_EQUAL_CHAR('l', get_tipo_forma(f)); // tipo
  TEST_ASSERT_EQUAL_PTR(l, get_handle_forma(f));  // handle

  // âncora
  double x, y;
  get_ancora_forma(f, &x, &y);

  TEST_ASSERT_EQUAL_DOUBLE(2.0, x);
  TEST_ASSERT_EQUAL_DOUBLE(8.0, y);

  double x2, y2;
  x2 = get_x_forma(f);
  y2 = get_y_forma(f);
  TEST_ASSERT_EQUAL_DOUBLE(2.0, x);
  TEST_ASSERT_EQUAL_DOUBLE(8.0, y);

  // área
  double area_linha = get_area_linha(l);

  double area_forma = get_area_forma(f);
  TEST_ASSERT_EQUAL_DOUBLE(area_linha, area_forma);

  libera_forma(&f);
  Circulo c = cria_circulo(1, 2.2, 4.4, 0.8, "yellow", "pink");
  double area_circulo = get_area_circulo(c);
  f = cria_forma('c', c);
  area_forma = get_area_forma(f);
  TEST_ASSERT_EQUAL_DOUBLE(area_circulo, area_forma);

  // corb
  char *cor_teste = get_corb_forma(f);
  TEST_ASSERT_EQUAL_STRING("yellow", cor_teste);
  // corp
  cor_teste = get_corp_forma(f);
  TEST_ASSERT_EQUAL_STRING("pink", cor_teste);

  // altura
  double altura_teste = get_altura_forma(f);
  TEST_ASSERT_EQUAL_DOUBLE(1.6, altura_teste);
  // largura
  double largura_teste = get_largura_forma(f);
  TEST_ASSERT_EQUAL_DOUBLE(1.6, altura_teste);

  libera_forma(&f);
}

void teste_setters_forma(void) {
  // âncora
  Linha l = cria_linha(-2, 2.0, 8.0, 4.0, 6.0, "pink");
  Forma f = cria_forma('l', l);

  TEST_ASSERT_FALSE(set_ancora_forma(NULL, 10.2, 10.4));
  TEST_ASSERT_TRUE(set_ancora_forma(f, 10.2, 10.4));

  double x, y;
  get_ancora_forma(f, &x, &y);

  TEST_ASSERT_EQUAL_DOUBLE(10.2, x);
  TEST_ASSERT_EQUAL_DOUBLE(10.4, y);
  TEST_ASSERT_EQUAL_DOUBLE(10.2 - 2 + 4, get_x2_linha(l));
  TEST_ASSERT_EQUAL_DOUBLE(10.4 - 8 + 6, get_y2_linha(l));
  libera_forma(&f);

  // corb
  Circulo c = cria_circulo(2, 2.2, 2.2, 2.2, "pink", "pink");
  f = cria_forma('c', c);

  set_corb_forma(f, "yellow");

  TEST_ASSERT_EQUAL_STRING("yellow", get_corb_circulo(c));
  libera_forma(&f);

  l = cria_linha(-2, 2.0, 8.0, 4.0, 6.0, "pink");
  f = cria_forma('l', l);

  set_corb_forma(f, "purple");

  TEST_ASSERT_EQUAL_STRING("purple", get_cor_linha(l));
  libera_forma(&f);

  // corp
  c = cria_circulo(2, 2.2, 2.2, 2.2, "pink", "pink");
  f = cria_forma('c', c);

  set_corp_forma(f, "yellow");

  TEST_ASSERT_EQUAL_STRING("yellow", get_corp_circulo(c));
  libera_forma(&f);

  l = cria_linha(-2, 2.0, 8.0, 4.0, 6.0, "pink");
  f = cria_forma('l', l);

  set_corp_forma(f, "purple");

  TEST_ASSERT_EQUAL_STRING("pink", get_cor_linha(l));

  libera_forma(&f);
}

void teste_desloca_forma(void) {
  Linha l = cria_linha(-2, 2.0, 8.0, 4.0, 6.0, "pink");
  Forma f = cria_forma('l', l);

  TEST_ASSERT_FALSE(desloca_forma(NULL, 2, -4));
  TEST_ASSERT_TRUE(desloca_forma(f, 2, -4));

  TEST_ASSERT_EQUAL_DOUBLE(2 + 2, get_x1_linha(l));
  TEST_ASSERT_EQUAL_DOUBLE(8 - 4, get_y1_linha(l));
  TEST_ASSERT_EQUAL_DOUBLE(4 + 2, get_x2_linha(l));
  TEST_ASSERT_EQUAL_DOUBLE(6 - 4, get_y2_linha(l));

  libera_forma(&f);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(teste_cria_libera_forma);
  RUN_TEST(teste_escreve_forma_svg);
  RUN_TEST(teste_clona_forma);
  RUN_TEST(teste_troca_cores_forma);
  RUN_TEST(teste_traduz_tipo_forma);
  RUN_TEST(teste_reporta_forma);
  RUN_TEST(teste_get_correcao_ancora);
  RUN_TEST(teste_getters_forma);
  RUN_TEST(teste_setters_forma);
  RUN_TEST(teste_desloca_forma);
  return UNITY_END();
}
