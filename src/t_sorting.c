#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "forma.h"
#include "sorting.h"
#include "unity.h"
#include <stdlib.h>
#include <stdio.h>

void setUp(void) {}
void tearDown(void) {}

void teste_compara_formas(void){
    RETANGULO r = cria_retangulo(1, 4.0, 0.0, 10.0, 10.0, "black", "white");
    LINHA l = cria_linha(3, 6.0, 2.0, 6.0, 6.0, "green");
    FORMA f1 = cria_forma('r', r);
    FORMA f2 = cria_forma('l', l);

    TEST_ASSERT_EQUAL_INT(-1, compara_default(f1, f2));
    TEST_ASSERT_EQUAL_INT(1, compara_area(f1, f2));
    TEST_ASSERT_EQUAL_INT(1, compara_largura(f1, f2));
    TEST_ASSERT_EQUAL_INT(-1, compara_altura(f2, f1));
    //TEST_ASSERT_EQUAL_INT(-1, compara_cor_preenchimento(f1, f2));
    libera_forma(&f1); libera_forma(&f2);


    CIRCULO c = cria_circulo(1, 4.2, -4.8, 4.0, "#AA1244", "#884466");
    TEXTO t = cria_texto(1, 4.2, -4.8, "#AAAAAA", "#88CCAA", 'm', ":3");
    f1 = cria_forma('c', c);
    f2 = cria_forma('t', t);

    TEST_ASSERT_EQUAL_INT(1, compara_default(f1, f2));
    TEST_ASSERT_EQUAL_INT(-1, compara_area(f2, f1));
    TEST_ASSERT_EQUAL_INT(1, compara_largura(f1, f2));
    TEST_ASSERT_EQUAL_INT(1, compara_altura(f2, f1));
    //TEST_ASSERT_EQUAL_INT(-1, compara_cor_preenchimento(f1, f2));
    
    libera_forma(&f1); libera_forma(&f2);
}

void teste_dentro_selecao(void){

}

void teste_bubble_sort_animado(void){

}

int main(void){
    UNITY_BEGIN();
    RUN_TEST(teste_compara_formas);
    RUN_TEST(dentro_selecao);
    RUN_TEST(teste_bubble_sort_animado);
    return UNITY_END();
}