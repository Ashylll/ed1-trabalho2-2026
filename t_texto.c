#include "texto.h"
#include "unity.h"
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

// Parâmetros gerais do texto para teste:
    int id = 1;
    double x = 10.4;
    double y = 8.26;
    char* corb = "pink";
    char* corp = "yellow";
    char a = 'm';
    char* txto = "Oii";

void teste_cria_texto(void){

    TEXTO t = cria_texto(id, x, y, corb, corp, a, txto);
    TEST_ASSERT_NOT_NULL(t);
    libera_texto(&t);

    t = cria_texto(id, x, y, NULL, corp, a, txto);
    TEST_ASSERT_NULL(t);
    libera_texto(&t);

    t = cria_texto(id, x, y, corb, NULL, a, txto);
    TEST_ASSERT_NULL(t);
    libera_texto(&t);

    t = cria_texto(id, x, y, corb, corp, 'e', txto);
    TEST_ASSERT_NULL(t);
    libera_texto(&t);

    t = cria_texto(id, x, y, corb, corp, a, NULL);
    TEST_ASSERT_NULL(t);
    libera_texto(&t);
}


void teste_getId_texto(void){
    TEXTO t = cria_texto(id, x, y, corb, corp, a, txto);

    int id_teste = getId_texto(t);

    TEST_ASSERT_EQUAL_INT(id, id_teste);
    libera_texto(&t);

    t = cria_texto(-18, x, y, corb, corp, a, txto);
    id_teste = getId_texto(t);

    TEST_ASSERT_EQUAL_INT(-18, id_teste);
    libera_texto(&t);
}

void teste_getX_texto(void){
    TEXTO t = cria_texto(id, x, y, corb, corp, a, txto);

    double x_teste = getX_texto(t);

    TEST_ASSERT_EQUAL_DOUBLE(x, x_teste);
    libera_texto(&t);

    t = cria_texto(id, -8, y, corb, corp, a, txto);
    x_teste = getX_texto(t);

    TEST_ASSERT_EQUAL_DOUBLE(-8, x_teste);
    libera_texto(&t);
}

void teste_getY_texto(void){
    TEXTO t = cria_texto(id, x, y, corb, corp, a, txto);

    double y_teste = getY_texto(t);

    TEST_ASSERT_EQUAL_DOUBLE(y, y_teste);
    libera_texto(&t);

    t = cria_texto(id, x, -6, corb, corp, a, txto);
    y_teste = getY_texto(t);

    TEST_ASSERT_EQUAL_DOUBLE(-6, y_teste);
    libera_texto(&t);
}


void teste_getCORB_texto(void){
    TEXTO t = cria_texto(id, x, y, corb, corp, a, txto);
    char* corb_teste = getCORB_texto(t);
    TEST_ASSERT_EQUAL_STRING(corb, corb_teste);
    libera_texto(&t);

    t = cria_texto(id, x, y, "purple", corp, a, txto);
    corb_teste = getCORB_texto(t);
    TEST_ASSERT_EQUAL_STRING("purple", corb_teste);
    libera_texto(&t);
}

void teste_getCORP_texto(void){
    TEXTO t = cria_texto(id, x, y, corb, corp, a, txto);
    char* corp_teste = getCORP_texto(t);
    TEST_ASSERT_EQUAL_STRING(corp, corp_teste);
    libera_texto(&t);

    t = cria_texto(id, x, y, corb, "black", a, txto);
    corp_teste = getCORP_texto(t);
    TEST_ASSERT_EQUAL_STRING("black", corp_teste);
    libera_texto(&t);
}

void teste_getA_texto(void){
    TEXTO t = cria_texto(id, x, y, corb, corp, a, txto);
    char a_teste = getA_texto(t);
    TEST_ASSERT_EQUAL_CHAR(a, a_teste);
    libera_texto(&t);

    t = cria_texto(id, x, y, corb, corp, 'i', txto);
    a_teste = getA_texto(t);
    TEST_ASSERT_EQUAL_CHAR('i', a_teste);
    libera_texto(&t);

    t = cria_texto(id, x, y, corb, corp, 'm', txto);
    a_teste = getA_texto(t);
    TEST_ASSERT_EQUAL_CHAR('m', a_teste);
    libera_texto(&t);

    t = cria_texto(id, x, y, corb, corp, 'f', txto);
    a_teste = getA_texto(t);
    TEST_ASSERT_EQUAL_CHAR('f', a_teste);
    libera_texto(&t);
}

void teste_getTXTO_texto(void){
    TEXTO t = cria_texto(id, x, y, corb, corp, a, txto);
    char* txto_teste = getTXTO_texto(t);
    TEST_ASSERT_EQUAL_STRING(txto, txto_teste);
    libera_texto(&t);

    t = cria_texto(id, x, y, corb, corp, a, "yupiii");
    txto_teste = getTXTO_texto(t);
    TEST_ASSERT_EQUAL_STRING("yupiii", txto_teste);
    libera_texto(&t);
}

void teste_setId_texto(void){
    TEXTO t = cria_texto(id, x, y, corb, corp, a, txto);

    TEST_ASSERT_FALSE(setId_texto(NULL, 2));
    TEST_ASSERT_EQUAL_INT(id, getId_texto(t));

    TEST_ASSERT_TRUE(setId_texto(t, 4));
    TEST_ASSERT_EQUAL_INT(4, getId_texto(t));

    TEST_ASSERT_TRUE(setId_texto(t, -2));
    TEST_ASSERT_EQUAL_INT(-2, getId_texto(t));

    TEST_ASSERT_TRUE(setId_texto(t, 0));
    TEST_ASSERT_EQUAL_INT(0, getId_texto(t));

    libera_texto(&t);
}

void teste_setX_texto(void){
    TEXTO t = cria_texto(id, x, y, corb, corp, a, txto);
    
    TEST_ASSERT_FALSE(setX_texto(NULL, -10));
    TEST_ASSERT_EQUAL_DOUBLE(x, getX_texto(t));

    TEST_ASSERT_TRUE(setX_texto(t, 4.2));
    TEST_ASSERT_EQUAL_DOUBLE(4.2, getX_texto(t));

    TEST_ASSERT_TRUE(setX_texto(t, -2.8));
    TEST_ASSERT_EQUAL_DOUBLE(-2.8, getX_texto(t));

    TEST_ASSERT_TRUE(setX_texto(t, 0));
    TEST_ASSERT_EQUAL_DOUBLE(0, getX_texto(t));

    libera_texto(&t);
}

void teste_setY_texto(void){
    TEXTO t = cria_texto(id, x, y, corb, corp, a, txto);
    
    TEST_ASSERT_FALSE(setY_texto(NULL, -10));
    TEST_ASSERT_EQUAL_DOUBLE(y, getY_texto(t));

    TEST_ASSERT_TRUE(setY_texto(t, 4.2));
    TEST_ASSERT_EQUAL_DOUBLE(4.2, getY_texto(t));

    TEST_ASSERT_TRUE(setY_texto(t, -2.8));
    TEST_ASSERT_EQUAL_DOUBLE(-2.8, getY_texto(t));

    TEST_ASSERT_TRUE(setY_texto(t, 0));
    TEST_ASSERT_EQUAL_DOUBLE(0, getY_texto(t));

    libera_texto(&t);
}


void teste_setCORB_texto(void){
    TEXTO t = cria_texto(id, x, y, corb, corp, a, txto);

    TEST_ASSERT_FALSE(setCORB_texto(NULL, "blue"));
    TEST_ASSERT_EQUAL_STRING(corb, getCORB_texto(t));

    TEST_ASSERT_FALSE(setCORB_texto(t, NULL));
    TEST_ASSERT_EQUAL_STRING(corb, getCORB_texto(t));

    TEST_ASSERT_TRUE(setCORB_texto(t, "cyan"));
    TEST_ASSERT_EQUAL_STRING("cyan", getCORB_texto(t));

    libera_texto(&t);
}

void teste_setCORP_texto(void){
    TEXTO t = cria_texto(id, x, y, corb, corp, a, txto);

    TEST_ASSERT_FALSE(setCORP_texto(NULL, "white"));
    TEST_ASSERT_EQUAL_STRING(corp, getCORP_texto(t));

    TEST_ASSERT_FALSE(setCORP_texto(t, NULL));
    TEST_ASSERT_EQUAL_STRING(corp, getCORP_texto(t));

    TEST_ASSERT_TRUE(setCORP_texto(t, "gray"));
    TEST_ASSERT_EQUAL_STRING("gray", getCORP_texto(t));

    libera_texto(&t);
}

void teste_setA_texto(void){
    TEXTO t = cria_texto(id, x, y, corb, corp, a, txto);

    TEST_ASSERT_FALSE(setA_texto(NULL, 'i'));
    TEST_ASSERT_EQUAL_CHAR(a, getA_texto(t));

    TEST_ASSERT_FALSE(setA_texto(t, 'h'));
    TEST_ASSERT_EQUAL_CHAR(a, getA_texto(t));

    TEST_ASSERT_TRUE(setA_texto(t, 'i'));
    TEST_ASSERT_EQUAL_CHAR('i', getA_texto(t));

    TEST_ASSERT_TRUE(setA_texto(t, 'm'));
    TEST_ASSERT_EQUAL_CHAR('m', getA_texto(t));

    TEST_ASSERT_TRUE(setA_texto(t, 'f'));
    TEST_ASSERT_EQUAL_CHAR('f', getA_texto(t));

    libera_texto(&t);
}

void teste_setTXTO_texto(void){
    TEXTO t = cria_texto(id, x, y, corb, corp, a, txto);

    TEST_ASSERT_FALSE(setTXTO_texto(NULL, "Tchau"));
    TEST_ASSERT_EQUAL_STRING(txto, getTXTO_texto(t));

    TEST_ASSERT_FALSE(setTXTO_texto(t, NULL));
    TEST_ASSERT_EQUAL_STRING(txto, getTXTO_texto(t));

    TEST_ASSERT_TRUE(setTXTO_texto(t, "Ahhh"));
    TEST_ASSERT_EQUAL_STRING("Ahhh", getTXTO_texto(t));

    libera_texto(&t);
}

void teste_getFFamily_texto(void){
    TEXTO t = cria_texto(id, x, y, corb, corp, a, txto);
    char* family = getFFamily_texto(t);
    TEST_ASSERT_EQUAL_STRING(FFAMILY_PADRAO, family);

    libera_texto(&t);
}

void teste_getFWeight_texto(void){
    TEXTO t = cria_texto(id, x, y, corb, corp, a, txto);
    char* weight = getFWeight_texto(t);
    TEST_ASSERT_EQUAL_STRING(FWEIGHT_PADRAO, weight);

    libera_texto(&t);
}

void teste_getFSize_texto(void){
    TEXTO t = cria_texto(id, x, y, corb, corp, a, txto);
    double size = getFSize_texto(t);
    TEST_ASSERT_EQUAL_DOUBLE(FSIZE_PADRAO, size);

    libera_texto(&t);
}
void teste_muda_estilo(void){
    TEXTO t = cria_texto(id, x, y, corb, corp, a, txto);

    TEST_ASSERT_FALSE(muda_estilo(NULL, "serif", "bold", 2));
    TEST_ASSERT_EQUAL_STRING(FFAMILY_PADRAO, getFFamily_texto(t));
    TEST_ASSERT_EQUAL_STRING(FWEIGHT_PADRAO, getFWeight_texto(t));
    TEST_ASSERT_EQUAL_DOUBLE(FSIZE_PADRAO, getFSize_texto(t));

    TEST_ASSERT_FALSE(muda_estilo(t, NULL, "normal", 8));
    TEST_ASSERT_EQUAL_STRING(FFAMILY_PADRAO, getFFamily_texto(t));
    TEST_ASSERT_EQUAL_STRING(FWEIGHT_PADRAO, getFWeight_texto(t));
    TEST_ASSERT_EQUAL_DOUBLE(FSIZE_PADRAO, getFSize_texto(t));

    TEST_ASSERT_FALSE(muda_estilo(t, "cursive", NULL, 12));
    TEST_ASSERT_EQUAL_STRING(FFAMILY_PADRAO, getFFamily_texto(t));
    TEST_ASSERT_EQUAL_STRING(FWEIGHT_PADRAO, getFWeight_texto(t));
    TEST_ASSERT_EQUAL_DOUBLE(FSIZE_PADRAO, getFSize_texto(t));

    TEST_ASSERT_FALSE(muda_estilo(t, "cursive", "bold", -4));
    TEST_ASSERT_EQUAL_STRING(FFAMILY_PADRAO, getFFamily_texto(t));
    TEST_ASSERT_EQUAL_STRING(FWEIGHT_PADRAO, getFWeight_texto(t));
    TEST_ASSERT_EQUAL_DOUBLE(FSIZE_PADRAO, getFSize_texto(t));

    TEST_ASSERT_TRUE(muda_estilo(t, "serif", "bold", 10));
    TEST_ASSERT_EQUAL_STRING("serif", getFFamily_texto(t));
    TEST_ASSERT_EQUAL_STRING("bold", getFWeight_texto(t));
    TEST_ASSERT_EQUAL_DOUBLE(10, getFSize_texto(t));

    TEST_ASSERT_TRUE(muda_estilo(t, "cursive", "bolder", 218.9481674));
    TEST_ASSERT_EQUAL_STRING("cursive", getFFamily_texto(t));
    TEST_ASSERT_EQUAL_STRING("bolder", getFWeight_texto(t));
    TEST_ASSERT_EQUAL_DOUBLE(218.9481674, getFSize_texto(t));

    TEST_ASSERT_TRUE(muda_estilo(t, "sans-serif", "lighter", 20));
    TEST_ASSERT_EQUAL_STRING("sans-serif", getFFamily_texto(t));
    TEST_ASSERT_EQUAL_STRING("lighter", getFWeight_texto(t));
    TEST_ASSERT_EQUAL_DOUBLE(20, getFSize_texto(t));

    libera_texto(&t);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(teste_cria_texto);
    RUN_TEST(teste_getId_texto);
    RUN_TEST(teste_getX_texto);
    RUN_TEST(teste_getY_texto);
    RUN_TEST(teste_getCORB_texto);
    RUN_TEST(teste_getCORP_texto);
    RUN_TEST(teste_getA_texto);
    RUN_TEST(teste_getTXTO_texto);
    RUN_TEST(teste_setId_texto);
    RUN_TEST(teste_setX_texto);
    RUN_TEST(teste_setY_texto);
    RUN_TEST(teste_setCORB_texto);
    RUN_TEST(teste_setCORP_texto);
    RUN_TEST(teste_setA_texto);
    RUN_TEST(teste_setTXTO_texto);
    RUN_TEST(teste_muda_estilo);
    RUN_TEST(teste_getFFamily_texto);
    RUN_TEST(teste_getFWeight_texto);
    RUN_TEST(teste_getFSize_texto);
    return UNITY_END();
}