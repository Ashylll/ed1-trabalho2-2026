#ifndef SORTING_H
#define SORTING_H
#endif

/*
    sorting.h

*/

typedef void* FORMA;
typedef int(*FCOMPARA_FORMAS)(FORMA f1, FORMA f2);


void bubble_sort(FORMA vetor_formas[], int n, int k, FCOMPARA_FORMAS cmp);


/*
    Funções de comparação de formas
    Retorna -1 se f1 for menor que f2, 0 se for igual e 1 se for maior
    Critério default: compara coordenadas y; se empatar compara x e para segundo desempate, a área
    Critérios cor de preenchimento: compara os valores RGB da cor. Primeiro RED, depois GREEN para desempate e BLUE para segundo desempate  
*/

int compara_default(FORMA f1, FORMA f2);
int compara_area(FORMA f1, FORMA f2);
int compara_largura(FORMA f1, FORMA f2);
int compara_altura(FORMA f1, FORMA f2);
int compara_cor_preenchimento(FORMA f1, FORMA f2);

/// @brief 
/// @param f1 
/// @param retangulo_selecao 
/// @return 
int dentro_selecao(FORMA f, FORMA retangulo_selecao);