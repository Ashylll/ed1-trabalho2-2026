#include "linha.h"
#include "unity.h"

#include <math.h>
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

// Parâmetros gerais da linha para teste:
int id = 1;
double x1 = 4.8;
double y1 = 8.26;
double x2 = 10.4;
double y2 = 2.2;
char *cor = "pink";

void teste_cria_libera_linha(void) {
  Linha l = cria_linha(id, x1, y1, x2, y2, cor);
  TEST_ASSERT_NOT_NULL(l);
  libera_linha(&l);

  l = cria_linha(id, x1, y1, x2, y2, NULL);
  TEST_ASSERT_NULL(l);
  libera_linha(&l);
}

void teste_getters_linha(void) {
  // comprimento
  Linha l = cria_linha(id, x1, y1, x2, y2, cor);
  double deltaX = x2 - x1;
  double deltaY = y2 - y1;
  double comprimento = sqrt(deltaX * deltaX + deltaY * deltaY);

  double comprimento_teste = get_comprimento_linha(l);
  TEST_ASSERT_EQUAL_DOUBLE(comprimento, comprimento_teste);

  // id
  int id_teste = get_id_linha(l);

  TEST_ASSERT_EQUAL_INT(id, id_teste);
  libera_linha(&l);

  l = cria_linha(-18, x1, y1, x2, y2, cor);
  id_teste = get_id_linha(l);

  TEST_ASSERT_EQUAL_INT(-18, id_teste);

  // x1
  double x1_teste = get_x1_linha(l);

  TEST_ASSERT_EQUAL_DOUBLE(x1, x1_teste);
  libera_linha(&l);

  l = cria_linha(id, -8, y1, x2, y2, cor);
  x1_teste = get_x1_linha(l);

  TEST_ASSERT_EQUAL_DOUBLE(-8, x1_teste);
  // y1
  double y1_teste = get_y1_linha(l);
  TEST_ASSERT_EQUAL_DOUBLE(y1, y1_teste);
  libera_linha(&l);

  l = cria_linha(id, x1, -6, x2, y2, cor);
  y1_teste = get_y1_linha(l);

  TEST_ASSERT_EQUAL_DOUBLE(-6, y1_teste);
  // x2
  double x2_teste = get_x2_linha(l);

  TEST_ASSERT_EQUAL_DOUBLE(x2, x2_teste);
  libera_linha(&l);

  l = cria_linha(id, x1, y1, -4, y2, cor);
  x2_teste = get_x2_linha(l);

  TEST_ASSERT_EQUAL_DOUBLE(-4, x2_teste);
  // y2
  double y2_teste = get_y2_linha(l);

  TEST_ASSERT_EQUAL_DOUBLE(y2, y2_teste);
  libera_linha(&l);

  l = cria_linha(id, x1, y1, x2, 0, cor);
  y2_teste = get_y2_linha(l);

  TEST_ASSERT_EQUAL_DOUBLE(0, y2_teste);

  // cor
  char *cor_teste = get_cor_linha(l);
  TEST_ASSERT_EQUAL_STRING(cor, cor_teste);
  libera_linha(&l);

  l = cria_linha(id, x1, y1, x2, y2, "black");
  cor_teste = get_cor_linha(l);
  TEST_ASSERT_EQUAL_STRING("black", cor_teste);

  // área
  double area = 1.5 * get_comprimento_linha(l);
  double area_teste = get_area_linha(l);

  TEST_ASSERT_EQUAL_DOUBLE(area, area_teste);
  libera_linha(&l);
}

void teste_setters_linha(void) {
  // id
  Linha l = cria_linha(id, x1, y1, x2, y2, cor);

  TEST_ASSERT_FALSE(set_id_linha(NULL, 2));
  TEST_ASSERT_EQUAL_INT(id, get_id_linha(l));

  TEST_ASSERT_TRUE(set_id_linha(l, 4));
  TEST_ASSERT_EQUAL_INT(4, get_id_linha(l));

  TEST_ASSERT_TRUE(set_id_linha(l, -2));
  TEST_ASSERT_EQUAL_INT(-2, get_id_linha(l));

  TEST_ASSERT_TRUE(set_id_linha(l, 0));
  TEST_ASSERT_EQUAL_INT(0, get_id_linha(l));

  // x1
  TEST_ASSERT_FALSE(set_x1_linha(NULL, -10));
  TEST_ASSERT_EQUAL_DOUBLE(x1, get_x1_linha(l));

  TEST_ASSERT_TRUE(set_x1_linha(l, 4.2));
  TEST_ASSERT_EQUAL_DOUBLE(4.2, get_x1_linha(l));

  TEST_ASSERT_TRUE(set_x1_linha(l, -2.8));
  TEST_ASSERT_EQUAL_DOUBLE(-2.8, get_x1_linha(l));

  TEST_ASSERT_TRUE(set_x1_linha(l, 0));
  TEST_ASSERT_EQUAL_DOUBLE(0, get_x1_linha(l));
  // y1
  TEST_ASSERT_FALSE(set_y1_linha(NULL, -10));
  TEST_ASSERT_EQUAL_DOUBLE(y1, get_y1_linha(l));

  TEST_ASSERT_TRUE(set_y1_linha(l, 4.2));
  TEST_ASSERT_EQUAL_DOUBLE(4.2, get_y1_linha(l));

  TEST_ASSERT_TRUE(set_y1_linha(l, -2.8));
  TEST_ASSERT_EQUAL_DOUBLE(-2.8, get_y1_linha(l));

  TEST_ASSERT_TRUE(set_y1_linha(l, 0));
  TEST_ASSERT_EQUAL_DOUBLE(0, get_y1_linha(l));
  // x2
  TEST_ASSERT_FALSE(set_x2_linha(NULL, -10));
  TEST_ASSERT_EQUAL_DOUBLE(x2, get_x2_linha(l));

  TEST_ASSERT_TRUE(set_x2_linha(l, 4.2));
  TEST_ASSERT_EQUAL_DOUBLE(4.2, get_x2_linha(l));

  TEST_ASSERT_TRUE(set_x2_linha(l, -2.8));
  TEST_ASSERT_EQUAL_DOUBLE(-2.8, get_x2_linha(l));

  TEST_ASSERT_TRUE(set_x2_linha(l, 0));
  TEST_ASSERT_EQUAL_DOUBLE(0, get_x2_linha(l));
  // y2
  TEST_ASSERT_FALSE(set_y2_linha(NULL, -10));
  TEST_ASSERT_EQUAL_DOUBLE(y2, get_y2_linha(l));

  TEST_ASSERT_TRUE(set_y2_linha(l, 4.2));
  TEST_ASSERT_EQUAL_DOUBLE(4.2, get_y2_linha(l));

  TEST_ASSERT_TRUE(set_y2_linha(l, -2.8));
  TEST_ASSERT_EQUAL_DOUBLE(-2.8, get_y2_linha(l));

  TEST_ASSERT_TRUE(set_y2_linha(l, 0));
  TEST_ASSERT_EQUAL_DOUBLE(0, get_y2_linha(l));
  libera_linha(&l);

  // âncora
  l = cria_linha(id, x1, y1, x2, y2, cor);
  TEST_ASSERT_FALSE(set_ancora_linha(NULL, -10, -8));
  TEST_ASSERT_TRUE(set_ancora_linha(l, 6.2, -12.2));
  TEST_ASSERT_EQUAL_DOUBLE(6.2, get_x1_linha(l));
  TEST_ASSERT_EQUAL_DOUBLE(-12.2, get_y1_linha(l));
  TEST_ASSERT_EQUAL_DOUBLE(x2 + (6.2 - x1), get_x2_linha(l));
  TEST_ASSERT_EQUAL_DOUBLE(y2 + (-12.2 - y1), get_y2_linha(l));

  // cor
  TEST_ASSERT_FALSE(set_cor(NULL, "white"));
  TEST_ASSERT_EQUAL_STRING(cor, get_cor_linha(l));

  TEST_ASSERT_FALSE(set_cor(l, NULL));
  TEST_ASSERT_EQUAL_STRING(cor, get_cor_linha(l));

  TEST_ASSERT_TRUE(set_cor(l, "gray"));
  TEST_ASSERT_EQUAL_STRING("gray", get_cor_linha(l));

  libera_linha(&l);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(teste_cria_libera_linha);
  RUN_TEST(teste_getters_linha);
  RUN_TEST(teste_setters_linha);
  return UNITY_END();
}
