#include "arvore.h"
#include "linha.h"
#include "forma.h"
#include "sorting.h"
#include "unity.h"
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

void teste_cria_libera_arvore(void){
    ARVORE arvore = cria_arvore(NULL);
    TEST_ASSERT_NULL(arvore);
    arvore = cria_arvore(compara_default);
    TEST_ASSERT_NOT_NULL(arvore);

    LINHA l1 = cria_linha(-2, 2.0, 8.0, 4.0, 6.0, "pink");
    LINHA l2 = cria_linha(-4, 2.0, 8.0, 4.0, 6.0, "pink");
    FORMA f1 = cria_forma('l', l1);
    FORMA f2 = cria_forma('l', l2);
    insere_arvore(arvore, f1);
    insere_arvore(arvore, f2);    

    libera_arvore(&arvore);
    TEST_ASSERT_NULL(l1);
    TEST_ASSERT_NULL(l2);
    TEST_ASSERT_NULL(arvore);
}

void teste_insere_remove_tamanho_arvore(void){
    ARVORE arvore = cria_arvore(compara_default);
    
    LINHA l = cria_linha(-2, 2.0, 8.0, 4.0, 6.0, "pink");

    FORMA f1 = cria_forma('l', l);
    FORMA f2 = cria_forma('l', l);
    FORMA f3 = cria_forma('l', l);
    insere_arvore(arvore, f1);
    insere_arvore(arvore, f2);
    insere_arvore(arvore, f3);
    TEST_ASSERT_EQUAL_INT(3, getTamanho_arvore(arvore));
    
    remove_arvore(arvore, f2);
    TEST_ASSERT_EQUAL_INT(2, getTamanho_arvore(arvore));
    remove_arvore(arvore, f1);
    TEST_ASSERT_EQUAL_INT(1, getTamanho_arvore(arvore));
    remove_arvore(arvore, f3);
    TEST_ASSERT_EQUAL_INT(0, getTamanho_arvore(arvore));
    
    libera(&arvore);
}

int main(void){
    UNITY_BEGIN();
    UNITY_RUN(teste_cria_libera_arvore);    
    UNITY_RUN(teste_insere_remove_tamanho_arvore);
    UNITY_RUN();
    UNITY_RUN();
    UNITY_RUN();
    UNITY_RUN();
    return UNITY_END();
}