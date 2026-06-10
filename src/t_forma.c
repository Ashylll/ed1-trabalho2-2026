#include "forma.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

#include "unity.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void setUp(void) {}
void tearDown(void) {}

void teste_cria_libera_forma(void){
    Circulo c = cria_circulo(0, 2.2, 4.4, 2, "pink", "pink");
    Forma f = cria_forma('a', c);
    TEST_ASSERT_NULL(f);
    libera_forma(&f);

    f = cria_forma('c', c);
    TEST_ASSERT_NOT_NULL(f);
    TEST_ASSERT_EQUAL_CHAR('c', get_tipo_forma(f));
    TEST_ASSERT_EQUAL_PTR(c, get_handle_forma(f));
    libera_forma(&f);

    Retangulo r = cria_retangulo(1, 2.2, 4.4, 2.2, 2.2, "pink", "pink");
    f = cria_forma('r', r);
    TEST_ASSERT_NOT_NULL(f);
    TEST_ASSERT_EQUAL_CHAR('r', get_tipo_forma(f));
    TEST_ASSERT_EQUAL_PTR(r, get_handle_forma(f));
    libera_forma(&f);

    Linha l = cria_linha(2, 2.0, 2.0, 4.0, 4.0, "pink");
    f = cria_forma('l', l);
    TEST_ASSERT_NOT_NULL(f);
    TEST_ASSERT_EQUAL_CHAR('l', get_tipo_forma(f));
    TEST_ASSERT_EQUAL_PTR(l, get_handle_forma(f));
    libera_forma(&f);

    Texto t = cria_texto(3, 4.2, 4.4, "pink", "pink", 'm', "rosa");
    f = cria_forma('t', t);
    TEST_ASSERT_NOT_NULL(f);
    TEST_ASSERT_EQUAL_CHAR('t', get_tipo_forma(f));
    TEST_ASSERT_EQUAL_PTR(t, get_handle_forma(f));

    libera_forma(&f);
    TEST_ASSERT_NULL(f);

}

void teste_escreve_forma_svg(void){
    char* path_out_teste = "teste_escrita.svg";
    FILE* fp_svg = fopen(path_out_teste, "w");
    
    Texto t = cria_texto(3, 4.2, 4.4, "pink", "pink", 'm', "rosa");
    Retangulo r = cria_retangulo(1, 2.2, 4.4, 2.2, 2.2, "pink", "pink");
    Linha l = cria_linha(2, 2.0, 2.0, 4.0, 4.0, "pink");
    Circulo c = cria_circulo(0, 2.2, 4.4, 2, "pink", "pink");
    Forma f1 = cria_forma('t', t);
    Forma f2 = cria_forma('r', r);
    Forma f3 = cria_forma('l', l);
    Forma f4 = cria_forma('c', c);
    escreve_forma_svg(fp_svg, f1);
    escreve_forma_svg(fp_svg, f2);
    escreve_forma_svg(fp_svg, f3);
    escreve_forma_svg(fp_svg, f4);

    fclose(fp_svg);

    FILE *checa = fopen(path_out_teste, "r");
    TEST_ASSERT_NOT_NULL(checa);

    char linha[256];
    bool tem_circulo = false;
    bool tem_retangulo = false;
    bool tem_texto = false;
    bool tem_linha = false;
    while (fgets(linha, sizeof(linha), checa)) {
        if (strstr(linha, "<circle")) tem_circulo = true;
        if (strstr(linha, "<rect")) tem_retangulo = true;
        if (strstr(linha, "<text")) tem_texto = true;
        if (strstr(linha, "<line")) tem_linha = true;
    }

    TEST_ASSERT_TRUE(tem_circulo);
    TEST_ASSERT_TRUE(tem_retangulo);
    TEST_ASSERT_TRUE(tem_texto);
    TEST_ASSERT_TRUE(tem_linha);

    fclose(checa);
    remove(path_out_teste);
    libera_forma(&f1);
    libera_forma(&f2);
    libera_forma(&f3);
    libera_forma(&f4);

}

void teste_troca_posicaoX_forma(void){

}

void teste_clona_forma(void){

}

void teste_troca_cores_forma(void){
    
}

void teste_traduz_tipo_forma(void){

}

void teste_reporta_forma(void){

}

void teste_posiciona_forma(void){
    
}

void teste_getters_forma(void){
    Linha l = cria_linha(-2, 2.0, 8.0, 4.0, 6.0, "pink");
    Forma f = cria_forma('l', l);
    
    TEST_ASSERT_EQUAL_INT(-2, get_id_forma(f)); // id
    TEST_ASSERT_EQUAL_CHAR('l', get_tipo_forma(f)); // tipo
    TEST_ASSERT_EQUAL_PTR(l, get_handle_forma(f)); // handle
    
    // âncora
    double x, y;
    get_ancora_forma(f, &x, &y);
    
    TEST_ASSERT_EQUAL_DOUBLE(2.0, x);
    TEST_ASSERT_EQUAL_DOUBLE(8.0, y);

    double x2, y2;
    x2 = get_x_forma(f);
    y2 = get_y_forma(f);
    TEST_ASSERT_EQUAL_DOUBLE(2.0, x);
    TEST_ASSERT_EQUAL_DOUBLE(8.0, y);

    
    // área
    double area_linha = get_area_linha(l);
    
    double area_forma = get_area_forma(f);
    TEST_ASSERT_EQUAL_DOUBLE(area_linha, area_forma);

    libera_forma(&f);
    Circulo c = cria_circulo(1, 2.2, 4.4, 0.8, "yellow", "pink"); 
    double area_circulo = get_area_circulo(c);
    f = cria_forma('c', c);
    area_forma = get_area_forma(f);
    TEST_ASSERT_EQUAL_DOUBLE(area_circulo, area_forma);

    // corb
    char* cor_teste = get_corb_forma(f);
    TEST_ASSERT_EQUAL_STRING("yellow", cor_teste);
    // corp
    cor_teste = get_corp_forma(f);
    TEST_ASSERT_EQUAL_STRING("pink", cor_teste);

    // altura
    double altura_teste = get_altura_forma(f);
    TEST_ASSERT_EQUAL_DOUBLE(1.6, altura_teste);    
    // largura
    double largura_teste = get_largura_forma(f);
    TEST_ASSERT_EQUAL_DOUBLE(1.6, altura_teste);    

    libera_forma(&f);
}



void teste_setters_forma(void){
    // âncora
    Linha l = cria_linha(-2, 2.0, 8.0, 4.0, 6.0, "pink");
    Forma f = cria_forma('l', l);

    TEST_ASSERT_FALSE(set_ancora_forma(NULL, 10.2, 10.4));
    TEST_ASSERT_TRUE(set_ancora_forma(f, 10.2, 10.4));

    double x, y;
    get_ancora_forma(f, &x, &y);

    TEST_ASSERT_EQUAL_DOUBLE(10.2, x);
    TEST_ASSERT_EQUAL_DOUBLE(10.4, y);
    TEST_ASSERT_EQUAL_DOUBLE(10.2 - 2 + 4, get_x2_linha(l));
    TEST_ASSERT_EQUAL_DOUBLE(10.4 - 8 + 6, get_y2_linha(l));
    libera_forma(&f);

    // corb
    Circulo c = cria_circulo(2, 2.2, 2.2, 2.2, "pink", "pink");
    f = cria_forma('c', c);
    
    set_corb_forma(f, "yellow");
    
    TEST_ASSERT_EQUAL_STRING("yellow", get_corb_circulo(c));
    libera_forma(&f);
    
    l = cria_linha(-2, 2.0, 8.0, 4.0, 6.0, "pink");
    f = cria_forma('l', l);
    
    set_corb_forma(f, "purple");
    
    TEST_ASSERT_EQUAL_STRING("purple", get_cor_linha(l));
    libera_forma(&f);

    // corp
    c = cria_circulo(2, 2.2, 2.2, 2.2, "pink", "pink");
    f = cria_forma('c', c);
    
    set_corp_forma(f, "yellow");
    
    TEST_ASSERT_EQUAL_STRING("yellow", get_corp_circulo(c));
    libera_forma(&f);
    
    l = cria_linha(-2, 2.0, 8.0, 4.0, 6.0, "pink");
    f = cria_forma('l', l);
    
    set_corp_forma(f, "purple");
    
    TEST_ASSERT_EQUAL_STRING("pink", get_cor_linha(l));
    
    libera_forma(&f);
}

void teste_desloca_forma(void){
    Linha l = cria_linha(-2, 2.0, 8.0, 4.0, 6.0, "pink");
    Forma f = cria_forma('l', l);

    TEST_ASSERT_FALSE(desloca_forma(NULL, 2, -4));
    TEST_ASSERT_TRUE(desloca_forma(f, 2, -4));

    TEST_ASSERT_EQUAL_DOUBLE(2 + 2, get_x1_linha(l));
    TEST_ASSERT_EQUAL_DOUBLE(8 - 4, get_y1_linha(l));
    TEST_ASSERT_EQUAL_DOUBLE(4 + 2, get_x2_linha(l));
    TEST_ASSERT_EQUAL_DOUBLE(6 - 4, get_y2_linha(l));

    libera_forma(&f);
}

int main(void){
    UNITY_BEGIN();
    RUN_TEST(teste_cria_libera_forma);
    RUN_TEST(teste_escreve_forma_svg);
    RUN_TEST(teste_troca_posicaoX_forma);
    RUN_TEST(teste_getters_forma);
    RUN_TEST(teste_setters_forma);
    RUN_TEST(teste_desloca_forma);
    return UNITY_END();
}