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
    fprintf(fp_geo, "l 1 10.0 10.0 40.0 40.0 green\n");
    fprintf(fp_geo, "c 2 30.0 50.0 10.0 red blue\n");
    fprintf(fp_geo, "r 3 90.0 40.0 45.0 15.0 black yellow\n");
    fprintf(fp_geo, "c 4 150.0 60.0 20.0 green white\n");
    fprintf(fp_geo, "r 5 210.0 40.0 20.0 50.0 orange black\n");
    fprintf(fp_geo, "c 6 270.0 75.0 35.0 purple gray\n");
    fprintf(fp_geo, "r 7 330.0 40.0 30.0 30.0 blue pink\n");
    fprintf(fp_geo, "c 8 390.0 45.0 5.0 brown cyan\n");
    fprintf(fp_geo, "r 9 450.0 40.0 50.0 70.0 red yellow\n");
    fprintf(fp_geo, "t 10 10.0 100.0 red blue i maionese\n");

    fclose(fp_geo);
    
    Arvore arvore = cria_arvore(compara_default);
    bool sucesso = leitura_geo(path_teste, arvore);
    TEST_ASSERT_TRUE(sucesso);
    TEST_ASSERT_EQUAL_INT(3, get_tamanho_arvore(arvore));

    libera_arvore(&arvore);
    remove(path_teste);
}

int main(void){
    UNITY_BEGIN();
    RUN_TEST(teste_leitura_geo);
    return UNITY_END();
}