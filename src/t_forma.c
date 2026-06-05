#include "forma.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

#include "unity.h"
#include <stdlib.h>
#include <stdio.h>

void setUp(void) {}
void tearDown(void) {}

void teste_cria_forma(void){
    CIRCULO c = cria_circulo(0, 2.2, 4.4, 2, "pink", "pink");
    FORMA f = cria_forma('a', c);
    TEST_ASSERT_NULL(f);
    libera_forma(&f);

    f = cria_forma('c', c);
    TEST_ASSERT_NOT_NULL(f);
    TEST_ASSERT_EQUAL_CHAR('c', getTipo_forma(f));
    TEST_ASSERT_EQUAL_PTR(c, getHandle_forma(f));
    libera_forma(&f);

    RETANGULO r = cria_retangulo(1, 2.2, 4.4, 2.2, 2.2, "pink", "pink");
    f = cria_forma('r', r);
    TEST_ASSERT_NOT_NULL(f);
    TEST_ASSERT_EQUAL_CHAR('r', getTipo_forma(f));
    TEST_ASSERT_EQUAL_PTR(r, getHandle_forma(f));
    libera_forma(&f);

    LINHA l = cria_linha(2, 2.0, 2.0, 4.0, 4.0, "pink");
    if(!l) printf("dfa\n");
    f = cria_forma('l', l);
    TEST_ASSERT_NOT_NULL(f);
    TEST_ASSERT_EQUAL_CHAR('l', getTipo_forma(f));
    TEST_ASSERT_EQUAL_PTR(l, getHandle_forma(f));
    libera_forma(&f);

    TEXTO t = cria_texto(3, 4.2, 4.4, "pink", "pink", 'm', "rosa");
    f = cria_forma('t', t);
    TEST_ASSERT_NOT_NULL(f);
    TEST_ASSERT_EQUAL_CHAR('t', getTipo_forma(f));
    TEST_ASSERT_EQUAL_PTR(t, getHandle_forma(f));

    libera_forma(&f);
    TEST_ASSERT_NULL(f);

}

void teste_getId_forma(void){
    LINHA l = cria_linha(-2, 2.0, 2.0, 4.0, 4.0, "pink");
    FORMA f = cria_forma('l', l);

    TEST_ASSERT_EQUAL_INT(-2, getId_forma(f));

    libera_forma(&f);
}

void teste_getTipo_forma(void){
    LINHA l = cria_linha(-2, 2.0, 2.0, 4.0, 4.0, "pink");
    FORMA f = cria_forma('l', l);

    TEST_ASSERT_EQUAL_CHAR('l', getTipo_forma(f));

    libera_forma(&f);
}

void teste_getHandle_forma(void){
    LINHA l = cria_linha(-2, 2.0, 2.0, 4.0, 4.0, "pink");
    FORMA f = cria_forma('l', l);

    TEST_ASSERT_EQUAL_PTR(l, getHandle_forma(f));

    libera_forma(&f);
}
    
void teste_getAncora_forma(void){
    LINHA l = cria_linha(-2, 2.0, 8.0, 4.0, 6.0, "pink");
    FORMA f = cria_forma('l', l);

    double x, y;
    getAncora_forma(f, &x, &y);

    TEST_ASSERT_EQUAL_DOUBLE(2, x);
    TEST_ASSERT_EQUAL_DOUBLE(8, y);

    libera_forma(&f);
}

void teste_getArea_forma(void){
    LINHA l = cria_linha(-2, 2.0, 8.0, 4.0, 6.0, "pink");
    FORMA f = cria_forma('l', l);
    double area_linha = getArea_linha(l);

    double area_forma = getArea_forma(f);
    TEST_ASSERT_EQUAL_DOUBLE(area_linha, area_forma);
    libera_forma(&f);

    CIRCULO c = cria_circulo(1, 2.2, 4.4, 0.8, "pink", "pink");
    double area_circulo = getArea_circulo(c);
    f = cria_forma('c', c);
    area_forma = getArea_forma(f);
    TEST_ASSERT_EQUAL_DOUBLE(area_circulo, area_forma);


    libera_forma(&f);
}

void teste_setAncora_forma(void){
    LINHA l = cria_linha(-2, 2.0, 8.0, 4.0, 6.0, "pink");
    FORMA f = cria_forma('l', l);

    TEST_ASSERT_FALSE(setAncora_forma(NULL, 10.2, 10.4));
    TEST_ASSERT_TRUE(setAncora_forma(f, 10.2, 10.4));

    double x, y;
    getAncora_forma(f, &x, &y);

    TEST_ASSERT_EQUAL_DOUBLE(10.2, x);
    TEST_ASSERT_EQUAL_DOUBLE(10.4, y);
    TEST_ASSERT_EQUAL_DOUBLE(10.2 - 2 + 4, getX2_linha(l));
    TEST_ASSERT_EQUAL_DOUBLE(10.4 - 8 + 6, getY2_linha(l));
    
    libera_forma(&f);
}

void teste_setCORB_forma(void){
    CIRCULO c = cria_circulo(2, 2.2, 2.2, 2.2, "pink", "pink");
    FORMA f = cria_forma('c', c);

    setCORB_forma(f, "yellow");

    TEST_ASSERT_EQUAL_STRING("yellow", getCORB_circulo(c));
    libera_forma(&f);

    LINHA l = cria_linha(-2, 2.0, 8.0, 4.0, 6.0, "pink");
    f = cria_forma('l', l);

    setCORB_forma(f, "purple");

    TEST_ASSERT_EQUAL_STRING("purple", getCOR_linha(l));

    libera_forma(&f);
}

void teste_setCORP_forma(void){
    CIRCULO c = cria_circulo(2, 2.2, 2.2, 2.2, "pink", "pink");
    FORMA f = cria_forma('c', c);
    
    setCORP_forma(f, "yellow");

    TEST_ASSERT_EQUAL_STRING("yellow", getCORP_circulo(c));
    libera_forma(&f);

    LINHA l = cria_linha(-2, 2.0, 8.0, 4.0, 6.0, "pink");
    f = cria_forma('l', l);

    setCORP_forma(f, "purple");

    TEST_ASSERT_EQUAL_STRING("pink", getCOR_linha(l));

    libera_forma(&f);
}

void teste_desloca_forma(void){
    LINHA l = cria_linha(-2, 2.0, 8.0, 4.0, 6.0, "pink");
    FORMA f = cria_forma('l', l);

    TEST_ASSERT_FALSE(desloca_forma(NULL, 2, -4));
    TEST_ASSERT_TRUE(desloca_forma(f, 2, -4));

    TEST_ASSERT_EQUAL_DOUBLE(2 + 2, getX1_linha(l));
    TEST_ASSERT_EQUAL_DOUBLE(8 - 4, getY1_linha(l));
    TEST_ASSERT_EQUAL_DOUBLE(4 + 2, getX2_linha(l));
    TEST_ASSERT_EQUAL_DOUBLE(6 - 4, getY2_linha(l));

    libera_forma(&f);
}

void teste_reporta_forma(void){
    CIRCULO c = cria_circulo(10, 5.0, 5.0, 2.0, "pink", "yellow");
    FORMA f = cria_forma('c', c);
    
    FILE *arq = fopen("teste_reporte.txt", "w+");
    TEST_ASSERT_NOT_NULL(arq);

    reporta_forma(f, arq);
    
    // Volta ao início do arquivo para ler e validar
    rewind(arq);
    char buffer[256];
    fgets(buffer, sizeof(buffer), arq);
    TEST_ASSERT_EQUAL_STRING("Circulo\n", buffer);
    
    fgets(buffer, sizeof(buffer), arq);
    TEST_ASSERT_EQUAL_STRING("Id: 10\n", buffer);

    fclose(arq);
    remove("teste_reporte.txt"); // Limpa o arquivo de teste
    libera_forma(&f);
}

void teste_sobrepoe_retangulo(void){
    RETANGULO r1 = cria_retangulo(1, 0.0, 0.0, 10.0, 10.0, "black", "white");
    RETANGULO r2 = cria_retangulo(2, 5.0, 5.0, 10.0, 10.0, "black", "white");
    FORMA f1 = cria_forma('r', r1);
    FORMA f2 = cria_forma('r', r2);
    
    TEST_ASSERT_TRUE(sobrepoe_retangulo(f1, f2));

    setX_retangulo(r2, 20.0); 
    TEST_ASSERT_FALSE(sobrepoe_retangulo(f1, f2));

    LINHA l = cria_linha(3, -5.0, 5.0, 5.0, 5.0, "green");
    FORMA fL = cria_forma('l', l);
    TEST_ASSERT_TRUE(sobrepoe_retangulo(f1, fL));

    TEXTO t = cria_texto(4, 5.0, 5.0, "black", "black", 'i', "Oi");
    FORMA fT = cria_forma('t', t);
    TEST_ASSERT_TRUE(sobrepoe_retangulo(f1, fT));

    libera_forma(&f1);
    libera_forma(&f2);
    libera_forma(&fL);
    libera_forma(&fT);
}

void  teste_compara_formas(void){
    RETANGULO r = cria_retangulo(1, 4.0, 0.0, 10.0, 10.0, "black", "white");
    LINHA l = cria_linha(3, 6.0, 2.0, 6.0, 6.0, "green");
    FORMA f1 = cria_forma('r', r);
    FORMA f2 = cria_forma('l', l);
    int result = compara_formas(f1, f2);

    TEST_ASSERT_EQUAL_INT(result, -1);
    setY_retangulo(r, 5.0);

    result = compara_formas(f1, f2);
    TEST_ASSERT_EQUAL_INT(result, 1);
    setY1_linha(l, 4.0);

    result = compara_formas(f1, f2);
    TEST_ASSERT_EQUAL_INT(result, 1);


    libera_forma(&f1); libera_forma(&f2);
}
int main(void){
    UNITY_BEGIN();
    RUN_TEST(teste_cria_forma);
    RUN_TEST(teste_getId_forma);
    RUN_TEST(teste_getTipo_forma);
    RUN_TEST(teste_getHandle_forma);
    RUN_TEST(teste_getAncora_forma);
    RUN_TEST(teste_getArea_forma);
    RUN_TEST(teste_setAncora_forma);
    RUN_TEST(teste_setCORB_forma);
    RUN_TEST(teste_setCORP_forma);
    RUN_TEST(teste_desloca_forma);
    RUN_TEST(teste_reporta_forma);
    RUN_TEST(teste_sobrepoe_retangulo);
    RUN_TEST(teste_compara_formas);
    return UNITY_END();
}