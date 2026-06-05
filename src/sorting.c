#include <stdlib.h>
#include "sorting.h"
#include "forma.h"

void bubble_sort(FORMA vetor[], int n, int k, FCOMPARA_FORMAS cmp) {
    int i, j;
    FORMA aux;
    int cont_ordenados = 0;

    for (i = 0; i < n - 1; i++) {
        if (cont_ordenados == k) return;

        for (j = n - 1; j > i; j--) {

            if (cmp(vetor[j], vetor[j - 1]) < 0) {
                aux = vetor[j];
                vetor[j] = vetor[j - 1];
                vetor[j - 1] = aux;
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
RGB cor_para_RGB(char* cor);
int compara_RGB(RGB cor1, RGB cor2);

int compara_cor_preenchimento(FORMA f1, FORMA f2){
    char* corp1 = getCORP_forma(f1);
    char* corp2 = getCORP_forma(f2);

    RGB c1 = cor_para_RGB(corp1);
    RGB c2 = cor_para_RGB(corp2);

    return compara_RGB(c1, c2);
}