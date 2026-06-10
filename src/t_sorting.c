#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "forma.h"
#include "svg.h"
#include "arvore.h"
#include "sorting.h"
#include "leitura_geo.h"
#include "unity.h"
#include <stdlib.h>
#include <stdio.h>

char* path_teste = "teste_leitura.geo";
Arvore arvore_teste;
Forma vet_sel;
void setUp(void) {
    arvore_teste = cria_arvore(compara_default);
    vet_sel = malloc(100 * sizeof(Forma));
    FILE* fp_geo = fopen(path_teste, "w");
    fprintf(fp_geo, "c 1 65.0 50.0 10.0 red blue\n");
    fprintf(fp_geo, "r 2 130.0 40.0 30.0 20.0 black yellow\n");
    fprintf(fp_geo, "l 3 100.0 40.0 120.0 100.0 green\n");
    fprintf(fp_geo, "t 4 10.0 100.0 red blue i maionese\n");
    fprintf(fp_geo, "c 1 30.0 50.0 10.0 red blue\n");

    // Figura 2: Retângulo (Âncora canto sup. esquerdo em X=90, Y=40. Altura=20, Largura=30)
    fprintf(fp_geo, "r 2 90.0 40.0 30.0 20.0 black yellow\n");

    // Figura 3: Linha (Ponto inicial em X=150, Y=40. Linha vertical descendo até Y=80)
    fprintf(fp_geo, "l 3 150.0 40.0 150.0 80.0 green\n");

    // Figura 4: Texto (Âncora em X=210, Y=40)
    fprintf(fp_geo, "t 4 210.0 40.0 red blue i maionese\n");

    // Figura 5: Círculo (Centro em X=270, Y=65. Raio=25 -> Teto encosta em Y=40)
    fprintf(fp_geo, "c 5 270.0 65.0 25.0 purple orange\n");

    // Figura 6: Retângulo (Âncora em X=330, Y=40. Altura=50, Largura=40)
    fprintf(fp_geo, "r 6 330.0 40.0 40.0 50.0 white gray\n");

    // Figura 7: Linha (Ponto inicial em X=390, Y=40. Linha inclinada até X=410, Y=90)
    fprintf(fp_geo, "l 7 390.0 40.0 410.0 90.0 pink\n");

    // Figura 8: Texto (Âncora em X=450, Y=40)
    fprintf(fp_geo, "t 8 450.0 40.0 black white i ketchup\n");
    fclose(fp_geo);
    leitura_geo(path_teste, arvore_teste);
    gera_svg_inicial("t1-inicial.svg", arvore_teste);
}
void tearDown(void) {
    libera_arvore(&arvore_teste);
    free(vet_sel);
}

void teste_compara_formas(void){
    Retangulo r = cria_retangulo(1, 4.0, 0.0, 10.0, 10.0, "black", "white");
    Linha l = cria_linha(3, 6.0, 2.0, 6.0, 6.0, "green");
    Forma f1 = cria_forma('r', r);
    Forma f2 = cria_forma('l', l);

    TEST_ASSERT_EQUAL_INT(-1, compara_default(f1, f2));
    TEST_ASSERT_EQUAL_INT(1, compara_area(f1, f2));
    TEST_ASSERT_EQUAL_INT(1, compara_largura(f1, f2));
    TEST_ASSERT_EQUAL_INT(-1, compara_altura(f2, f1));
    //TEST_ASSERT_EQUAL_INT(-1, compara_cor_preenchimento(f1, f2));
    libera_forma(&f1); libera_forma(&f2);


    Circulo c = cria_circulo(1, 4.2, -4.8, 4.0, "#AA1244", "#884466");
    Texto t = cria_texto(1, 4.2, -4.8, "#AAAAAA", "#88CCAA", 'm', ":3");
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
    char* path_svg = "t1-bs.svg";
    Forma ret_sel = cria_forma('r', cria_retangulo(-1, 0.0, 0.0, 200.0, 200.0, "red", "none"));

    int n = 0;
    formas_selecionadas_para_vetor(arvore_teste, ret_sel, vet_sel, &n);
    posiciona_formas(vet_sel, n, 100.0, 100.0, 40.0);
    bubble_sort_animado(path_svg, vet_sel, n, n, compara_area);

    libera_forma(&ret_sel);
}

int main(void){
    UNITY_BEGIN();
    RUN_TEST(teste_compara_formas);
    RUN_TEST(teste_dentro_selecao);
    RUN_TEST(teste_bubble_sort_animado);
    return UNITY_END();
}