#include "arvore.h"
#include "linha.h"
#include "forma.h"
#include "sorting.h"
#include "leitura_geo.h"
#include "unity.h"
#include <stdlib.h>
#include <string.h>

void setUp(void) {}
void tearDown(void) {}

void teste_cria_libera_arvore(void){
    ARVORE arvore = cria_arvore(NULL);
    TEST_ASSERT_NULL(arvore);
    arvore = cria_arvore(compara_default);
    TEST_ASSERT_NOT_NULL(arvore);

    LINHA l1 = cria_linha(-2, 2.0, 8.0, 4.0, 6.0, "pink");
    LINHA l2 = cria_linha(-4, 2.0, 9.0, 4.0, 6.0, "pink");
    FORMA f1 = cria_forma('l', l1);
    FORMA f2 = cria_forma('l', l2);
    insere_arvore(arvore, f1);
    insere_arvore(arvore, f2);    

    libera_arvore(&arvore);
    TEST_ASSERT_NULL(arvore);
}

void teste_insere_remove_tamanho_arvore(void){
    ARVORE arvore = cria_arvore(compara_default);
    
    LINHA l1 = cria_linha(-2, 2.0, 9.0, 4.0, 6.0, "pink");
    LINHA l2 = cria_linha(-2, 2.0, 8.0, 4.0, 6.0, "pink");
    LINHA l3 = cria_linha(-2, 2.0, 7.0, 4.0, 6.0, "pink");

    FORMA f1 = cria_forma('l', l1);
    FORMA f2 = cria_forma('l', l2);
    FORMA f3 = cria_forma('l', l3);
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
    
    libera_arvore(&arvore);
}

void teste_escreve_arvore_svg(void){
    char* path_in = "teste_leitura.geo";
    FILE* fp_geo = fopen(path_in, "w");
    fprintf(fp_geo, "c 10 50.0 50.0 20.0 blue red\n");
    fprintf(fp_geo, "r 20 10.0 10.0 100.0 200.0 green yellow\n");
    fprintf(fp_geo, "ts sans-serif bold 14.0\n");
    fprintf(fp_geo, "t 30 0.0 0.0 black black i Texto de Teste\n");
    fclose(fp_geo);
    fp_geo = fopen(path_in, "r");
    ARVORE arvore = cria_arvore(compara_default);
    leitura_geo(fp_geo, arvore);
    fclose(fp_geo);

    char* path_out_teste = "teste_escrita.svg";
    FILE* fp_svg = fopen(path_out_teste, "w");
    escreve_arvore_svg(fp_svg, arvore);
    fclose(fp_svg);

    FILE *checa = fopen(path_out_teste, "r");
    TEST_ASSERT_NOT_NULL(checa);

    char linha[256];
    bool tem_circulo = false;
    bool tem_retangulo = false;
    bool tem_texto = false;
    bool tem_txto = false;
    while (fgets(linha, sizeof(linha), checa)) {
        if (strstr(linha, "<circle")) tem_circulo = true;
        if (strstr(linha, "<rect")) tem_retangulo = true;
        if (strstr(linha, "<text")) tem_texto = true;
        if (strstr(linha, "Texto de Teste")) tem_txto = true;
    }

    TEST_ASSERT_TRUE(tem_circulo);
    TEST_ASSERT_TRUE(tem_retangulo);
    TEST_ASSERT_TRUE(tem_texto);
    TEST_ASSERT_TRUE(tem_txto);

    fclose(checa);
    libera_arvore(&arvore);
}
int main(void){
    UNITY_BEGIN();
    RUN_TEST(teste_cria_libera_arvore);    
    RUN_TEST(teste_insere_remove_tamanho_arvore);
    RUN_TEST(teste_escreve_arvore_svg);
    return UNITY_END();
}