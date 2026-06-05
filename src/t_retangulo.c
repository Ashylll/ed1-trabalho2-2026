#include "retangulo.h"
#include "unity.h"
#include <stdlib.h>
#include <stdio.h>

void setUp(void) {}
void tearDown(void) {}

// Parâmetros gerais do retângulo para teste:
    int id = 1;
    double x = 10.4;
    double y = 8.26;
    double w = 2.2;
    double h = 4.8;
    char* corb = "pink";
    char* corp = "yellow";

void teste_cria_retangulo(void){
    RETANGULO r = cria_retangulo(id, x, y, w, h, corb, corp);
    TEST_ASSERT_NOT_NULL(r);
    libera_retangulo(&r);

    r = cria_retangulo(id, x, y, 0, h, corb, corp);
    TEST_ASSERT_NULL(r);
    libera_retangulo(&r);

    r = cria_retangulo(id, x, y, w, 0, corb, corp);
    TEST_ASSERT_NULL(r);
    libera_retangulo(&r);

    r = cria_retangulo(id, x, y, w, h, NULL, corp);
    TEST_ASSERT_NULL(r);
    libera_retangulo(&r);

    r = cria_retangulo(id, x, y, w, h, corb, NULL);
    TEST_ASSERT_NULL(r);
    libera_retangulo(&r);
}

void teste_getters_retangulo(void){
    // área
    RETANGULO r = cria_retangulo(id, x, y, w, h, corb, corp);

    double area = w * h;
    double area_retornada = getArea_retangulo(r);

    TEST_ASSERT_EQUAL_DOUBLE(area, area_retornada);

    // id
    int id_teste = getId_retangulo(r);

    TEST_ASSERT_EQUAL_INT(id, id_teste);
    libera_retangulo(&r);

    r = cria_retangulo(-18, x, y, w, h, corb, corp);
    id_teste = getId_retangulo(r);

    TEST_ASSERT_EQUAL_INT(-18, id_teste);

    // x
    double x_teste = getX_retangulo(r);

    TEST_ASSERT_EQUAL_DOUBLE(x, x_teste);
    libera_retangulo(&r);

    r = cria_retangulo(id, -8, y, w, h, corb, corp);
    x_teste = getX_retangulo(r);

    TEST_ASSERT_EQUAL_DOUBLE(-8, x_teste);

    // y
    double y_teste = getY_retangulo(r);

    TEST_ASSERT_EQUAL_DOUBLE(y, y_teste);
    libera_retangulo(&r);

    r = cria_retangulo(id, x, -6, w, h, corb, corp);
    y_teste = getY_retangulo(r);

    TEST_ASSERT_EQUAL_DOUBLE(-6, y_teste);

    // largura
    double w_teste = getW_retangulo(r);

    TEST_ASSERT_EQUAL_DOUBLE(w, w_teste);
    libera_retangulo(&r);

    r = cria_retangulo(id, x, y, 4, h, corb, corp);
    w_teste = getW_retangulo(r);

    TEST_ASSERT_EQUAL_DOUBLE(4, w_teste);

    // altura
    double h_teste = getH_retangulo(r);

    TEST_ASSERT_EQUAL_DOUBLE(h, h_teste);
    libera_retangulo(&r);

    r = cria_retangulo(id, x, y, w, 6, corb, corp);
    h_teste = getH_retangulo(r);

    TEST_ASSERT_EQUAL_DOUBLE(6, h_teste);

    // corb
    char* corb_teste = getCORB_retangulo(r);
    TEST_ASSERT_EQUAL_STRING(corb, corb_teste);
    libera_retangulo(&r);

    r = cria_retangulo(id, x, y, w, h, "purple", corp);
    corb_teste = getCORB_retangulo(r);
    TEST_ASSERT_EQUAL_STRING("purple", corb_teste);

    // corp
    char* corp_teste = getCORP_retangulo(r);
    TEST_ASSERT_EQUAL_STRING(corp, corp_teste);
    libera_retangulo(&r);

    r = cria_retangulo(id, x, y, w, h, corb, "black");
    corp_teste = getCORP_retangulo(r);
    TEST_ASSERT_EQUAL_STRING("black", corp_teste);
    libera_retangulo(&r);
}

void teste_setters_retangulo(void){
    // id
    RETANGULO r = cria_retangulo(id, x, y, w, h, corb, corp);

    TEST_ASSERT_FALSE(setId_retangulo(NULL, 2));
    TEST_ASSERT_EQUAL_INT(id, getId_retangulo(r));

    TEST_ASSERT_TRUE(setId_retangulo(r, 4));
    TEST_ASSERT_EQUAL_INT(4, getId_retangulo(r));

    TEST_ASSERT_TRUE(setId_retangulo(r, -2));
    TEST_ASSERT_EQUAL_INT(-2, getId_retangulo(r));

    TEST_ASSERT_TRUE(setId_retangulo(r, 0));
    TEST_ASSERT_EQUAL_INT(0, getId_retangulo(r));

    // x
    TEST_ASSERT_FALSE(setX_retangulo(NULL, -10));
    TEST_ASSERT_EQUAL_DOUBLE(x, getX_retangulo(r));

    TEST_ASSERT_TRUE(setX_retangulo(r, 4.2));
    TEST_ASSERT_EQUAL_DOUBLE(4.2, getX_retangulo(r));

    TEST_ASSERT_TRUE(setX_retangulo(r, -2.8));
    TEST_ASSERT_EQUAL_DOUBLE(-2.8, getX_retangulo(r));

    TEST_ASSERT_TRUE(setX_retangulo(r, 0));
    TEST_ASSERT_EQUAL_DOUBLE(0, getX_retangulo(r));

    // y
    TEST_ASSERT_FALSE(setY_retangulo(NULL, -10));
    TEST_ASSERT_EQUAL_DOUBLE(y, getY_retangulo(r));

    TEST_ASSERT_TRUE(setY_retangulo(r, 4.2));
    TEST_ASSERT_EQUAL_DOUBLE(4.2, getY_retangulo(r));

    TEST_ASSERT_TRUE(setY_retangulo(r, -2.8));
    TEST_ASSERT_EQUAL_DOUBLE(-2.8, getY_retangulo(r));

    TEST_ASSERT_TRUE(setY_retangulo(r, 0));
    TEST_ASSERT_EQUAL_DOUBLE(0, getY_retangulo(r));

    // largura
    TEST_ASSERT_FALSE(setW_retangulo(NULL, 2));
    TEST_ASSERT_EQUAL_DOUBLE(w, getW_retangulo(r));

    TEST_ASSERT_FALSE(setW_retangulo(r, -2));
    TEST_ASSERT_EQUAL_DOUBLE(w, getW_retangulo(r));

    TEST_ASSERT_FALSE(setW_retangulo(r, 0));
    TEST_ASSERT_EQUAL_DOUBLE(w, getW_retangulo(r));

    TEST_ASSERT_TRUE(setW_retangulo(r, 4.2));
    TEST_ASSERT_EQUAL_DOUBLE(4.2, getW_retangulo(r));

    // altura
    TEST_ASSERT_FALSE(setH_retangulo(NULL, 2));
    TEST_ASSERT_EQUAL_DOUBLE(h, getH_retangulo(r));

    TEST_ASSERT_FALSE(setH_retangulo(r, -2));
    TEST_ASSERT_EQUAL_DOUBLE(h, getH_retangulo(r));

    TEST_ASSERT_FALSE(setH_retangulo(r, 0));
    TEST_ASSERT_EQUAL_DOUBLE(h, getH_retangulo(r));

    TEST_ASSERT_TRUE(setH_retangulo(r, 4.2));
    TEST_ASSERT_EQUAL_DOUBLE(4.2, getH_retangulo(r));

    // corb
    TEST_ASSERT_FALSE(setCORB_retangulo(NULL, "blue"));
    TEST_ASSERT_EQUAL_STRING(corb, getCORB_retangulo(r));

    TEST_ASSERT_FALSE(setCORB_retangulo(r, NULL));
    TEST_ASSERT_EQUAL_STRING(corb, getCORB_retangulo(r));

    TEST_ASSERT_TRUE(setCORB_retangulo(r, "cyan"));
    TEST_ASSERT_EQUAL_STRING("cyan", getCORB_retangulo(r));

    // corp
    TEST_ASSERT_FALSE(setCORP_retangulo(NULL, "white"));
    TEST_ASSERT_EQUAL_STRING(corp, getCORP_retangulo(r));

    TEST_ASSERT_FALSE(setCORP_retangulo(r, NULL));
    TEST_ASSERT_EQUAL_STRING(corp, getCORP_retangulo(r));

    TEST_ASSERT_TRUE(setCORP_retangulo(r, "gray"));
    TEST_ASSERT_EQUAL_STRING("gray", getCORP_retangulo(r));

    libera_retangulo(&r);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(teste_cria_retangulo);
    RUN_TEST(teste_getters_retangulo);
    RUN_TEST(teste_setters_retangulo);
    return UNITY_END();
}