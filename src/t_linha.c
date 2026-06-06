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
    char* cor = "pink";

void teste_cria_libera_linha(void){
    LINHA l = cria_linha(id, x1, y1, x2, y2, cor);
    TEST_ASSERT_NOT_NULL(l);
    libera_linha(&l);

    l = cria_linha(id, x1, y1, x2, y2, NULL);
    TEST_ASSERT_NULL(l);
    libera_linha(&l);
}

void teste_getters_linha(void){
    // comprimento
    LINHA l = cria_linha(id, x1, y1, x2, y2, cor);
    double deltaX = x2 - x1;
    double deltaY = y2 - y1;
    double comprimento = sqrt(deltaX*deltaX + deltaY*deltaY);

    double comprimento_teste = getComprimento_linha(l);
    TEST_ASSERT_EQUAL_DOUBLE(comprimento, comprimento_teste);

    // id
    int id_teste = getId_linha(l);
    
    TEST_ASSERT_EQUAL_INT(id, id_teste);
    libera_linha(&l);
    
    l = cria_linha(-18, x1, y1, x2, y2, cor);
    id_teste = getId_linha(l);
    
    TEST_ASSERT_EQUAL_INT(-18, id_teste);

    // x1
    double x1_teste = getX1_linha(l);
    
    TEST_ASSERT_EQUAL_DOUBLE(x1, x1_teste);
    libera_linha(&l);
    
    l = cria_linha(id, -8, y1, x2, y2, cor);
    x1_teste = getX1_linha(l);
    
    TEST_ASSERT_EQUAL_DOUBLE(-8, x1_teste);
    // y1
    double y1_teste = getY1_linha(l);
    TEST_ASSERT_EQUAL_DOUBLE(y1, y1_teste);
    libera_linha(&l);
    
    l = cria_linha(id, x1, -6, x2, y2, cor);
    y1_teste = getY1_linha(l);
    
    TEST_ASSERT_EQUAL_DOUBLE(-6, y1_teste);
    // x2
    double x2_teste = getX2_linha(l);
    
    TEST_ASSERT_EQUAL_DOUBLE(x2, x2_teste);
    libera_linha(&l);
    
    l = cria_linha(id, x1, y1, -4, y2, cor);
    x2_teste = getX2_linha(l);
    
    TEST_ASSERT_EQUAL_DOUBLE(-4, x2_teste);
    // y2
    double y2_teste = getY2_linha(l);
    
    TEST_ASSERT_EQUAL_DOUBLE(y2, y2_teste);
    libera_linha(&l);
    
    l = cria_linha(id, x1, y1, x2, 0, cor);
    y2_teste = getY2_linha(l);
    
    TEST_ASSERT_EQUAL_DOUBLE(0, y2_teste);

    // cor
    char* cor_teste = getCOR_linha(l);
    TEST_ASSERT_EQUAL_STRING(cor, cor_teste);
    libera_linha(&l);
    
    l = cria_linha(id, x1, y1, x2, y2, "black");
    cor_teste = getCOR_linha(l);
    TEST_ASSERT_EQUAL_STRING("black", cor_teste);

    // área
    double area = 1.5 * getComprimento_linha(l);
    double area_teste = getArea_linha(l);
    
    TEST_ASSERT_EQUAL_DOUBLE(area, area_teste);
    libera_linha(&l);    
}

void teste_setters_linha(void){
    // id
    LINHA l = cria_linha(id, x1, y1, x2, y2, cor);

    TEST_ASSERT_FALSE(setId_linha(NULL, 2));
    TEST_ASSERT_EQUAL_INT(id, getId_linha(l));

    TEST_ASSERT_TRUE(setId_linha(l, 4));
    TEST_ASSERT_EQUAL_INT(4, getId_linha(l));

    TEST_ASSERT_TRUE(setId_linha(l, -2));
    TEST_ASSERT_EQUAL_INT(-2, getId_linha(l));

    TEST_ASSERT_TRUE(setId_linha(l, 0));
    TEST_ASSERT_EQUAL_INT(0, getId_linha(l));

    // x1
    TEST_ASSERT_FALSE(setX1_linha(NULL, -10));
    TEST_ASSERT_EQUAL_DOUBLE(x1, getX1_linha(l));
    
    TEST_ASSERT_TRUE(setX1_linha(l, 4.2));
    TEST_ASSERT_EQUAL_DOUBLE(4.2, getX1_linha(l));
    
    TEST_ASSERT_TRUE(setX1_linha(l, -2.8));
    TEST_ASSERT_EQUAL_DOUBLE(-2.8, getX1_linha(l));
    
    TEST_ASSERT_TRUE(setX1_linha(l, 0));
    TEST_ASSERT_EQUAL_DOUBLE(0, getX1_linha(l));
    // y1
    TEST_ASSERT_FALSE(setY1_linha(NULL, -10));
    TEST_ASSERT_EQUAL_DOUBLE(y1, getY1_linha(l));
    
    TEST_ASSERT_TRUE(setY1_linha(l, 4.2));
    TEST_ASSERT_EQUAL_DOUBLE(4.2, getY1_linha(l));
    
    TEST_ASSERT_TRUE(setY1_linha(l, -2.8));
    TEST_ASSERT_EQUAL_DOUBLE(-2.8, getY1_linha(l));
    
    TEST_ASSERT_TRUE(setY1_linha(l, 0));
    TEST_ASSERT_EQUAL_DOUBLE(0, getY1_linha(l));
    // x2
    TEST_ASSERT_FALSE(setX2_linha(NULL, -10));
    TEST_ASSERT_EQUAL_DOUBLE(x2, getX2_linha(l));
    
    TEST_ASSERT_TRUE(setX2_linha(l, 4.2));
    TEST_ASSERT_EQUAL_DOUBLE(4.2, getX2_linha(l));
    
    TEST_ASSERT_TRUE(setX2_linha(l, -2.8));
    TEST_ASSERT_EQUAL_DOUBLE(-2.8, getX2_linha(l));
    
    TEST_ASSERT_TRUE(setX2_linha(l, 0));
    TEST_ASSERT_EQUAL_DOUBLE(0, getX2_linha(l));
    // y2
    TEST_ASSERT_FALSE(setY2_linha(NULL, -10));
    TEST_ASSERT_EQUAL_DOUBLE(y2, getY2_linha(l));
    
    TEST_ASSERT_TRUE(setY2_linha(l, 4.2));
    TEST_ASSERT_EQUAL_DOUBLE(4.2, getY2_linha(l));
    
    TEST_ASSERT_TRUE(setY2_linha(l, -2.8));
    TEST_ASSERT_EQUAL_DOUBLE(-2.8, getY2_linha(l));
    
    TEST_ASSERT_TRUE(setY2_linha(l, 0));
    TEST_ASSERT_EQUAL_DOUBLE(0, getY2_linha(l));
    libera_linha(&l);

    // âncora
    l = cria_linha(id, x1, y1, x2, y2, cor);
    TEST_ASSERT_FALSE(setAncora_linha(NULL, -10, -8));
    TEST_ASSERT_TRUE(setAncora_linha(l, 6.2, -12.2));
    TEST_ASSERT_EQUAL_DOUBLE(6.2, getX1_linha(l));
    TEST_ASSERT_EQUAL_DOUBLE(-12.2, getY1_linha(l));
    TEST_ASSERT_EQUAL_DOUBLE(x2 + (6.2 - x1), getX2_linha(l));
    TEST_ASSERT_EQUAL_DOUBLE(y2 + (-12.2 - y1), getY2_linha(l));
    
    // cor
    TEST_ASSERT_FALSE(setCOR_linha(NULL, "white"));
    TEST_ASSERT_EQUAL_STRING(cor, getCOR_linha(l));
    
    TEST_ASSERT_FALSE(setCOR_linha(l, NULL));
    TEST_ASSERT_EQUAL_STRING(cor, getCOR_linha(l));
    
    TEST_ASSERT_TRUE(setCOR_linha(l, "gray"));
    TEST_ASSERT_EQUAL_STRING("gray", getCOR_linha(l));
    
    libera_linha(&l);
}


int main(void) {
    UNITY_BEGIN();
    RUN_TEST(teste_cria_libera_linha);
    RUN_TEST(teste_getters_linha);
    RUN_TEST(teste_setters_linha);
    return UNITY_END();
}
