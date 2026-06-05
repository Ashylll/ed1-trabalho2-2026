#include "circulo.h"
#include "unity.h"
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

// Parâmetros gerais do círculo para teste:
    int id = 1;
    double x = 10.4;
    double y = 8.26;
    double r = 0.8;
    char* corb = "pink";
    char* corp = "yellow";

void teste_cria_circulo(void){

    CIRCULO c = cria_circulo(id, x, y, r, corb, corp);
    TEST_ASSERT_NOT_NULL(c);
    libera_circulo(&c);

    c = cria_circulo(id, x, y, 0, corb, corp);
    TEST_ASSERT_NULL(c);
    libera_circulo(&c);

    c = cria_circulo(id, x, y, r, NULL, corp);
    TEST_ASSERT_NULL(c);
    libera_circulo(&c);

    c = cria_circulo(id, x, y, r, corb, NULL);
    TEST_ASSERT_NULL(c);
    libera_circulo(&c);
}

void teste_getArea_circulo(void){
    CIRCULO c = cria_circulo(id, x, y, r, corb, corp);

    double area = PI * r * r; 
    double area_retornada = getArea_circulo(c);

    TEST_ASSERT_EQUAL_DOUBLE(area, area_retornada);

    libera_circulo(&c);
}

void teste_getId_circulo(void){
    CIRCULO c = cria_circulo(id, x, y, r, corb, corp);

    int id_teste = getId_circulo(c);

    TEST_ASSERT_EQUAL_INT(id, id_teste);
    libera_circulo(&c);

    c = cria_circulo(-18, x, y, r, corb, corp);
    id_teste = getId_circulo(c);

    TEST_ASSERT_EQUAL_INT(-18, id_teste);
    libera_circulo(&c);
}

void teste_getX_circulo(void){
    CIRCULO c = cria_circulo(id, x, y, r, corb, corp);

    double x_teste = getX_circulo(c);

    TEST_ASSERT_EQUAL_DOUBLE(x, x_teste);
    libera_circulo(&c);

    c = cria_circulo(id, -8, y, r, corb, corp);
    x_teste = getX_circulo(c);

    TEST_ASSERT_EQUAL_DOUBLE(-8, x_teste);
    libera_circulo(&c);
}

void teste_getY_circulo(void){
    CIRCULO c = cria_circulo(id, x, y, r, corb, corp);

    double y_teste = getY_circulo(c);

    TEST_ASSERT_EQUAL_DOUBLE(y, y_teste);
    libera_circulo(&c);

    c = cria_circulo(id, x, -6, r, corb, corp);
    y_teste = getY_circulo(c);

    TEST_ASSERT_EQUAL_DOUBLE(-6, y_teste);
    libera_circulo(&c);
}

void teste_getR_circulo(void){
    CIRCULO c = cria_circulo(id, x, y, r, corb, corp);
    double r_teste = getR_circulo(c);
    TEST_ASSERT_EQUAL_DOUBLE(r, r_teste);
    libera_circulo(&c);

    c = cria_circulo(id, x, y, 16.4, corb, corp);
    r_teste = getR_circulo(c);
    TEST_ASSERT_EQUAL_DOUBLE(16.4, r_teste);
    libera_circulo(&c);
}

void teste_getCORB_circulo(void){
    CIRCULO c = cria_circulo(id, x, y, r, corb, corp);
    char* corb_teste = getCORB_circulo(c);
    TEST_ASSERT_EQUAL_STRING(corb, corb_teste);
    libera_circulo(&c);

    c = cria_circulo(id, x, y, r, "purple", corp);
    corb_teste = getCORB_circulo(c);
    TEST_ASSERT_EQUAL_STRING("purple", corb_teste);
    libera_circulo(&c);
}

void teste_getCORP_circulo(void){
    CIRCULO c = cria_circulo(id, x, y, r, corb, corp);
    char* corp_teste = getCORP_circulo(c);
    TEST_ASSERT_EQUAL_STRING(corp, corp_teste);
    libera_circulo(&c);

    c = cria_circulo(id, x, y, r, corb, "black");
    corp_teste = getCORP_circulo(c);
    TEST_ASSERT_EQUAL_STRING("black", corp_teste);
    libera_circulo(&c);
}

void teste_setId_circulo(void){
    CIRCULO c = cria_circulo(id, x, y, r, corb, corp);

    TEST_ASSERT_FALSE(setId_circulo(NULL, 2));
    TEST_ASSERT_EQUAL_INT(id, getId_circulo(c));

    TEST_ASSERT_TRUE(setId_circulo(c, 4));
    TEST_ASSERT_EQUAL_INT(4, getId_circulo(c));

    TEST_ASSERT_TRUE(setId_circulo(c, -2));
    TEST_ASSERT_EQUAL_INT(-2, getId_circulo(c));

    TEST_ASSERT_TRUE(setId_circulo(c, 0));
    TEST_ASSERT_EQUAL_INT(0, getId_circulo(c));

    libera_circulo(&c);
}

void teste_setX_circulo(void){
    CIRCULO c = cria_circulo(id, x, y, r, corb, corp);
    
    TEST_ASSERT_FALSE(setX_circulo(NULL, -10));
    TEST_ASSERT_EQUAL_DOUBLE(x, getX_circulo(c));

    TEST_ASSERT_TRUE(setX_circulo(c, 4.2));
    TEST_ASSERT_EQUAL_DOUBLE(4.2, getX_circulo(c));

    TEST_ASSERT_TRUE(setX_circulo(c, -2.8));
    TEST_ASSERT_EQUAL_DOUBLE(-2.8, getX_circulo(c));

    TEST_ASSERT_TRUE(setX_circulo(c, 0));
    TEST_ASSERT_EQUAL_DOUBLE(0, getX_circulo(c));

    libera_circulo(&c);
}

void teste_setY_circulo(void){
    CIRCULO c = cria_circulo(id, x, y, r, corb, corp);
    
    TEST_ASSERT_FALSE(setY_circulo(NULL, -10));
    TEST_ASSERT_EQUAL_DOUBLE(y, getY_circulo(c));

    TEST_ASSERT_TRUE(setY_circulo(c, 4.2));
    TEST_ASSERT_EQUAL_DOUBLE(4.2, getY_circulo(c));

    TEST_ASSERT_TRUE(setY_circulo(c, -2.8));
    TEST_ASSERT_EQUAL_DOUBLE(-2.8, getY_circulo(c));

    TEST_ASSERT_TRUE(setY_circulo(c, 0));
    TEST_ASSERT_EQUAL_DOUBLE(0, getY_circulo(c));

    libera_circulo(&c);
}

void teste_setR_circulo(void){
    CIRCULO c = cria_circulo(id, x, y, r, corb, corp);
    
    TEST_ASSERT_FALSE(setR_circulo(NULL, 2));
    TEST_ASSERT_EQUAL_DOUBLE(r, getR_circulo(c));

    TEST_ASSERT_FALSE(setR_circulo(c, -2));
    TEST_ASSERT_EQUAL_DOUBLE(r, getR_circulo(c));

    TEST_ASSERT_FALSE(setR_circulo(c, 0));
    TEST_ASSERT_EQUAL_DOUBLE(r, getR_circulo(c));

    TEST_ASSERT_TRUE(setR_circulo(c, 4.2));
    TEST_ASSERT_EQUAL_DOUBLE(4.2, getR_circulo(c));

    libera_circulo(&c);
}

void teste_setCORB_circulo(void){
    CIRCULO c = cria_circulo(id, x, y, r, corb, corp);

    TEST_ASSERT_FALSE(setCORB_circulo(NULL, "blue"));
    TEST_ASSERT_EQUAL_STRING(corb, getCORB_circulo(c));

    TEST_ASSERT_FALSE(setCORB_circulo(c, NULL));
    TEST_ASSERT_EQUAL_STRING(corb, getCORB_circulo(c));

    TEST_ASSERT_TRUE(setCORB_circulo(c, "cyan"));
    TEST_ASSERT_EQUAL_STRING("cyan", getCORB_circulo(c));

    libera_circulo(&c);
}

void teste_setCORP_circulo(void){
    CIRCULO c = cria_circulo(id, x, y, r, corb, corp);

    TEST_ASSERT_FALSE(setCORP_circulo(NULL, "white"));
    TEST_ASSERT_EQUAL_STRING(corp, getCORP_circulo(c));

    TEST_ASSERT_FALSE(setCORP_circulo(c, NULL));
    TEST_ASSERT_EQUAL_STRING(corp, getCORP_circulo(c));

    TEST_ASSERT_TRUE(setCORP_circulo(c, "gray"));
    TEST_ASSERT_EQUAL_STRING("gray", getCORP_circulo(c));

    libera_circulo(&c);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(teste_cria_circulo);
    RUN_TEST(teste_getArea_circulo);
    RUN_TEST(teste_getId_circulo);
    RUN_TEST(teste_getX_circulo);
    RUN_TEST(teste_getY_circulo);
    RUN_TEST(teste_getR_circulo);
    RUN_TEST(teste_getCORB_circulo);
    RUN_TEST(teste_getCORP_circulo);
    RUN_TEST(teste_setId_circulo);
    RUN_TEST(teste_setX_circulo);
    RUN_TEST(teste_setY_circulo);
    RUN_TEST(teste_setR_circulo);
    RUN_TEST(teste_setCORB_circulo);
    RUN_TEST(teste_setCORP_circulo);
    return UNITY_END();
}
