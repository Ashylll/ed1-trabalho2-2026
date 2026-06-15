#include "processa_qry.h"
#include "leitura_geo.h"
#include "arvore.h"
#include "sorting.h"
#include "unity.h"
#include <stdlib.h>
#include <stdio.h>

bool processa_qry(const char* path_qry, const char* path_log, const char* comb_out, Arvore formas, Arvore formas_marcadores);

FILE* fp_qry;
FILE* fp_txt;
FILE* fp_comb;
char* path_qry = "teste.svg";
char* path_txt = "teste.txt";
char* path_svg = "geo-teste.svg";
Arvore formas, formas_marcadores;
void setUp(void) {
    fopen(path_qry, "r");
    fopen(path_txt, "w");
    fopen(path_svg, "w");

    formas = cria_arvore(compara_default);
    formas_marcadores = cria_arvore(compara_default);

    char* path_geo = "teste.geo";
    FILE* fp_geo = fopen(path_geo, "w");
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
    
    leitura_geo(path_geo, formas);

}
void tearDown(void) {
    fclose(fp_qry);
    fclose(fp_txt);
    fclose(fp_comb);

    libera_arvore(&formas);
    libera_arvore(&formas_marcadores);
}

void teste_comandos_sel_cm_mc(void){

}

void teste_comandos_find_findrm(void){
    fp_qry = fopen(path_qry, "w");
    fprintf(fp_qry, "sel 0.0 0.0 400.0 380.0\n");
    fprintf(fp_qry, "find 3 bs a 200.0 200.0 40.0\n");
    fclose(fp_qry);

    bool sucesso = false;
    sucesso = processa_qry(path_qry, path_txt, path_svg, formas, formas_marcadores);
    TEST_ASSERT_TRUE(sucesso);

}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(teste_comandos_sel_cm_mc);
    RUN_TEST(teste_comandos_find_findrm);
    return UNITY_END();
}