#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sorting.h"
#include "forma.h"
#include "arvore.h"

static void remove_extensao(const char *path, char *dest) {
    strcpy(dest, path);
    char *ponto = strrchr(dest, '.'); 
    if (ponto) *ponto = '\0';
}

static void transforma_numero(int n, char* n_final){
    char n_string[8];
    snprintf(n_string, sizeof(n_string), "%d", n);

    strcpy(n_final, "000000");
    int i = 5;
    int j = strlen(n_string) - 1;

    while (i >= 0 && j >= 0){
        n_final[i] = n_string[j];
        i--; j--;
    }
}

static FILE* cria_file_frame(int numeracao_frame, const char* comb_out){
    char nome_svg[256];
    char base_comb_svg[256];
    char n_final[8];
    transforma_numero(numeracao_frame, n_final);

    remove_extensao(comb_out, base_comb_svg);
    snprintf(nome_svg, sizeof(nome_svg), "%s%s.svg", base_comb_svg, n_final);    
    
    FILE* fp = fopen(nome_svg, "w");
    return fp;
}

static void desenha_frame(int numeracao_frame, const char* comb_out, ARVORE a){
    FILE* frame_svg = cria_file_frame(numeracao_frame, comb_out);
    if (!frame_svg) return;

    escreve_arvore_svg(frame_svg, a);
    fclose(frame_svg);
}

void bubble_sort_animado(const char* comb_out, ARVORE a, FORMA vetor[], int n, int k, FCOMPARA_FORMAS cmp) {
    int i, j;
    FORMA aux;
    int cont_ordenados = 0;
    int numeracao_frame = 0;

    for (i = 0; i < n - 1; i++) {
        if (cont_ordenados == k) return;

        for (j = n - 1; j > i; j--) {

            if (cmp(vetor[j], vetor[j - 1]) < 0) {
                aux = vetor[j];
                vetor[j] = vetor[j - 1];
                vetor[j - 1] = aux;
                
                numeracao_frame += 1;
                troca_posicaoX_formas(vetor[j], vetor[j - 1], 20);

                desenha_frame(numeracao_frame, comb_out, a);
            }
        }
        cont_ordenados++;
    }
}

int compara_default(FORMA f1, FORMA f2){
    double x1, y1, x2, y2;
    getAncora_forma(f1, &x1, &y1);
    getAncora_forma(f2, &x2, &y2);

    if (y1 != y2) return (y1 > y2) ? 1 : -1;
    if (x1 != x2) return (x1 > x2) ? 1 : -1;

    double area1 = getArea_forma(f1);
    double area2 = getArea_forma(f2);
    if (area1 != area2) return (area1 > area2) ? 1 : -1;

    return 0;
}

int compara_area(FORMA f1, FORMA f2){
    double area1 = getArea_forma(f1);
    double area2 = getArea_forma(f2);

    if (area1 != area2) return (area1 > area2) ? 1 : -1;
    
    return 0;
}

int compara_largura(FORMA f1, FORMA f2){
    double largura1 = getLargura_forma(f1);
    double largura2 = getLargura_forma(f2);

    if (largura1 != largura2) return (largura1 > largura2) ? 1 : -1;

    return 0;
}

int compara_altura(FORMA f1, FORMA f2){
    double altura1 = getAltura_forma(f1);
    double altura2 = getAltura_forma(f2);

    if (altura1 != altura2) return (altura1 > altura2) ? 1 : -1;

    return 0;
}


typedef struct RGB{
    unsigned char r, g, b;
} RGB;

// A implementar...
//RGB cor_para_RGB(char* cor);
//int compara_RGB(RGB cor1, RGB cor2);

/*int compara_cor_preenchimento(FORMA f1, FORMA f2){
    char* corp1 = getCORP_forma(f1);
    char* corp2 = getCORP_forma(f2);

    RGB c1 = cor_para_RGB(corp1);
    RGB c2 = cor_para_RGB(corp2);

    return compara_RGB(c1, c2);
}*/

static inline bool ponto_no_retangulo(double x, double y, double xR, double yR, double w, double h){
    const double eps = 1e-9;
    return (xR - eps <= x && x <= xR + w + eps) && (yR - eps <= y && y <= yR + h + eps);
}

int dentro_selecao(FORMA f, FORMA retangulo_selecao){\
    double xf, yf, hf, wf;
    getAncora_forma(f, &xf, &yf);
    hf = getAltura_forma(f);
    wf = getLargura_forma(f);

    double xs, ys, hs, ws;
    getAncora_forma(retangulo_selecao, &xs, &ys);
    hs = getAltura_forma(retangulo_selecao);
    ws = getLargura_forma(retangulo_selecao);

    switch (getTipo_forma(f)){
        case 'c':
            if (
            ponto_no_retangulo(xf + wf/2, yf, xs, ys, ws, hs) &&
            ponto_no_retangulo(xf - wf/2, yf, xs, ys, ws, hs) && 
            ponto_no_retangulo(xf, yf + hf/2, xs, ys, ws, hs) &&
            ponto_no_retangulo(xf, yf - hf/2, xs, ys, ws, hs)
            )
            return 1;
            else return 0;

        case 'r':
            if (ponto_no_retangulo(xf, yf, xs, ys, ws, hs) && ponto_no_retangulo(xf + wf, yf + hf, xs, ys, ws, hs))  
            return 1;
            else return 0;

        case 'l':
            if (ponto_no_retangulo(xf, yf, xs, ys, ws, hs) && ponto_no_retangulo(xf + wf, yf + wf, xs, ys, ws, hs))  
            return 1;
            else return 0;

        case 't':
            if (ponto_no_retangulo(xf, yf, xs, ys, ws, hs) && ponto_no_retangulo(xf + wf, yf + wf, xs, ys, ws, hs))  
            return 1;
            else return 0;

        default: return -1;
    }
}