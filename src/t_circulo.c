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

void teste_cria_libera_circulo(void){

    Circulo c = cria_circulo(id, x, y, r, corb, corp);
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

void teste_getters_circulo(void){
    // area
    Circulo c = cria_circulo(id, x, y, r, corb, corp);

    double area = PI * r * r; 
    double area_retornada = get_area_circulo(c);

    TEST_ASSERT_EQUAL_DOUBLE(area, area_retornada);

    // id
    int id_teste = get_id_circulo(c);

    TEST_ASSERT_EQUAL_INT(id, id_teste);
    libera_circulo(&c);

    c = cria_circulo(-18, x, y, r, corb, corp);
    id_teste = get_id_circulo(c);

    TEST_ASSERT_EQUAL_INT(-18, id_teste);

    // x
    double x_teste = get_x_circulo(c);

    TEST_ASSERT_EQUAL_DOUBLE(x, x_teste);
    libera_circulo(&c);

    c = cria_circulo(id, -8, y, r, corb, corp);
    x_teste = get_x_circulo(c);

    TEST_ASSERT_EQUAL_DOUBLE(-8, x_teste);

    // y
    double y_teste = get_y_circulo(c);

    TEST_ASSERT_EQUAL_DOUBLE(y, y_teste);
    libera_circulo(&c);

    c = cria_circulo(id, x, -6, r, corb, corp);
    y_teste = get_y_circulo(c);

    TEST_ASSERT_EQUAL_DOUBLE(-6, y_teste);

    // raio
    double r_teste = get_raio_circulo(c);
    TEST_ASSERT_EQUAL_DOUBLE(r, r_teste);
    libera_circulo(&c);

    c = cria_circulo(id, x, y, 16.4, corb, corp);
    r_teste = get_raio_circulo(c);
    TEST_ASSERT_EQUAL_DOUBLE(16.4, r_teste);

    // corb
    char* corb_teste = get_corb_circulo(c);
    TEST_ASSERT_EQUAL_STRING(corb, corb_teste);
    libera_circulo(&c);

    c = cria_circulo(id, x, y, r, "purple", corp);
    corb_teste = get_corb_circulo(c);
    TEST_ASSERT_EQUAL_STRING("purple", corb_teste);

    // corp
    char* corp_teste = get_corp_circulo(c);
    TEST_ASSERT_EQUAL_STRING(corp, corp_teste);
    libera_circulo(&c);

    c = cria_circulo(id, x, y, r, corb, "black");
    corp_teste = get_corp_circulo(c);
    TEST_ASSERT_EQUAL_STRING("black", corp_teste);
    libera_circulo(&c);
}

void teste_setters_circulo(void){
    // id
    Circulo c = cria_circulo(id, x, y, r, corb, corp);

    TEST_ASSERT_FALSE(set_id_circulo(NULL, 2));
    TEST_ASSERT_EQUAL_INT(id, get_id_circulo(c));

    TEST_ASSERT_TRUE(set_id_circulo(c, 4));
    TEST_ASSERT_EQUAL_INT(4, get_id_circulo(c));

    TEST_ASSERT_TRUE(set_id_circulo(c, -2));
    TEST_ASSERT_EQUAL_INT(-2, get_id_circulo(c));

    TEST_ASSERT_TRUE(set_id_circulo(c, 0));
    TEST_ASSERT_EQUAL_INT(0, get_id_circulo(c));

    // x
    TEST_ASSERT_FALSE(set_x_circulo(NULL, -10));
    TEST_ASSERT_EQUAL_DOUBLE(x, get_x_circulo(c));

    TEST_ASSERT_TRUE(set_x_circulo(c, 4.2));
    TEST_ASSERT_EQUAL_DOUBLE(4.2, get_x_circulo(c));

    TEST_ASSERT_TRUE(set_x_circulo(c, -2.8));
    TEST_ASSERT_EQUAL_DOUBLE(-2.8, get_x_circulo(c));

    TEST_ASSERT_TRUE(set_x_circulo(c, 0));
    TEST_ASSERT_EQUAL_DOUBLE(0, get_x_circulo(c));

    // y    
    TEST_ASSERT_FALSE(set_y_circulo(NULL, -10));
    TEST_ASSERT_EQUAL_DOUBLE(y, get_y_circulo(c));

    TEST_ASSERT_TRUE(set_y_circulo(c, 4.2));
    TEST_ASSERT_EQUAL_DOUBLE(4.2, get_y_circulo(c));

    TEST_ASSERT_TRUE(set_y_circulo(c, -2.8));
    TEST_ASSERT_EQUAL_DOUBLE(-2.8, get_y_circulo(c));

    TEST_ASSERT_TRUE(set_y_circulo(c, 0));
    TEST_ASSERT_EQUAL_DOUBLE(0, get_y_circulo(c));


    // raio
    TEST_ASSERT_FALSE(set_raio_circulo(NULL, 2));
    TEST_ASSERT_EQUAL_DOUBLE(r, get_raio_circulo(c));

    TEST_ASSERT_FALSE(set_raio_circulo(c, -2));
    TEST_ASSERT_EQUAL_DOUBLE(r, get_raio_circulo(c));

    TEST_ASSERT_FALSE(set_raio_circulo(c, 0));
    TEST_ASSERT_EQUAL_DOUBLE(r, get_raio_circulo(c));

    TEST_ASSERT_TRUE(set_raio_circulo(c, 4.2));
    TEST_ASSERT_EQUAL_DOUBLE(4.2, get_raio_circulo(c));

    // corb
    TEST_ASSERT_FALSE(set_corb_circulo(NULL, "blue"));
    TEST_ASSERT_EQUAL_STRING(corb, get_corb_circulo(c));

    TEST_ASSERT_FALSE(set_corb_circulo(c, NULL));
    TEST_ASSERT_EQUAL_STRING(corb, get_corb_circulo(c));

    TEST_ASSERT_TRUE(set_corb_circulo(c, "cyan"));
    TEST_ASSERT_EQUAL_STRING("cyan", get_corb_circulo(c));

    // corp
    TEST_ASSERT_FALSE(set_corp_circulo(NULL, "white"));
    TEST_ASSERT_EQUAL_STRING(corp, get_corp_circulo(c));

    TEST_ASSERT_FALSE(set_corp_circulo(c, NULL));
    TEST_ASSERT_EQUAL_STRING(corp, get_corp_circulo(c));

    TEST_ASSERT_TRUE(set_corp_circulo(c, "gray"));
    TEST_ASSERT_EQUAL_STRING("gray", get_corp_circulo(c));

    libera_circulo(&c);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(teste_cria_libera_circulo);
    RUN_TEST(teste_getters_circulo);
    RUN_TEST(teste_setters_circulo);
    return UNITY_END();
}
