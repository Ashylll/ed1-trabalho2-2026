#include "unity.h"
#include "leitura_geo.h"
#include "arvore.h"
#include "sorting.h"
#include <stdio.h>

void setUp(void) {}
void tearDown(void) {}


void teste_leitura_geo(void){
    char* path_teste = "teste_leitura.geo";
    FILE* fp_geo = fopen(path_teste, "w");
    fprintf(fp_geo, "c 10 50.0 50.0 20.0 blue red\n");
    fprintf(fp_geo, "r 20 10.0 10.0 100.0 200.0 green yellow\n");
    fprintf(fp_geo, "ts sans-serif bold 14.0\n");
    fprintf(fp_geo, "t 30 0.0 0.0 black black i Texto de Teste\n");
    fclose(fp_geo);
    
    fp_geo = fopen(path_teste, "r");
    Arvore arvore = cria_arvore(compara_default);
    bool sucesso = leitura_geo(fp_geo, arvore);
    TEST_ASSERT_TRUE(sucesso);
    TEST_ASSERT_EQUAL_INT(3, get_tamanho_arvore(arvore));
    fclose(fp_geo);

    libera_arvore(&arvore);
    remove(path_teste);
}

int main(void){
    UNITY_BEGIN();
    RUN_TEST(teste_leitura_geo);
    return UNITY_END();
}