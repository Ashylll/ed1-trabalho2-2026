#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sorting.h"
#include "svg.h"
#include "forma.h"
#include "arvore.h"

void bubble_sort_animado(const char* comb_out, Forma vetor[], int n, int k, ComparaFormas cmp) {
    int i, j;
    Forma aux;
    int cont_ordenados = 0;
    int numeracao_frame = 0;
    
    escreve_frame(comb_out, numeracao_frame, 100, 100, 10, vetor, n); // frame inicial antes da ordenação

    for (i = 0; i < n - 1; i++) {
        if (cont_ordenados == k) return;

        for (j = n - 1; j > i; j--) {

            if (cmp(vetor[j], vetor[j - 1]) < 0) {
                aux = vetor[j];
                vetor[j] = vetor[j - 1];
                vetor[j - 1] = aux;
                
                escreve_frame(comb_out, numeracao_frame, 100, 100, 10, vetor, n);                
                numeracao_frame += 1;
            }
        }
  
        cont_ordenados++;
    }
}

int compara_default(Forma f1, Forma f2){
    double x1, y1, x2, y2;
    get_ancora_forma(f1, &x1, &y1);
    get_ancora_forma(f2, &x2, &y2);

    if (y1 != y2) return (y1 > y2) ? 1 : -1;
    if (x1 != x2) return (x1 > x2) ? 1 : -1;

    double area1 = get_area_forma(f1);
    double area2 = get_area_forma(f2);
    if (area1 != area2) return (area1 > area2) ? 1 : -1;

    return 0;
}

int compara_area(Forma f1, Forma f2){
    double area1 = get_area_forma(f1);
    double area2 = get_area_forma(f2);

    if (area1 != area2) return (area1 > area2) ? 1 : -1;
    
    return 0;
}

int compara_largura(Forma f1, Forma f2){
    double largura1 = get_largura_forma(f1);
    double largura2 = get_largura_forma(f2);

    if (largura1 != largura2) return (largura1 > largura2) ? 1 : -1;

    return 0;
}

int compara_altura(Forma f1, Forma f2){
    double altura1 = get_altura_forma(f1);
    double altura2 = get_altura_forma(f2);

    if (altura1 != altura2) return (altura1 > altura2) ? 1 : -1;

    return 0;
}

int compara_cor_preenchimento(Forma f1, Forma f2){
    char* cor1 = get_corp_forma(f1);       
    char* cor2 = get_corp_forma(f2);       

    return strcmp(cor1, cor2);
}

static inline bool ponto_no_retangulo(double x, double y, double xR, double yR, double w, double h){
    const double eps = 1e-9;
    return (xR - eps <= x && x <= xR + w + eps) && (yR - eps <= y && y <= yR + h + eps);
}

int dentro_selecao(Forma f, Forma retangulo_selecao){\
    double xf, yf, hf, wf;
    get_ancora_forma(f, &xf, &yf);
    hf = get_altura_forma(f);
    wf = get_largura_forma(f);

    double xs, ys, hs, ws;
    get_ancora_forma(retangulo_selecao, &xs, &ys);
    hs = get_altura_forma(retangulo_selecao);
    ws = get_largura_forma(retangulo_selecao);

    switch (get_tipo_forma(f)){
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