#ifndef SORTING_H
#define SORTING_H
#endif

/*
    sorting.h

*/

typedef void *Forma, *Arvore;
typedef int(*ComparaFormas)(Forma f1, Forma f2);


void bubble_sort_animado(const char* comb_out, Forma vetor[], int n, int k, ComparaFormas cmp);


/*
    Funções de comparação de formas
    Retorna -1 se f1 for menor que f2, 0 se for igual e 1 se for maior
    Critério default: compara coordenadas y; se empatar compara x e para segundo desempate, a área
    Critérios cor de preenchimento: compara os valores RGB da cor. Primeiro RED, depois GREEN para desempate e BLUE para segundo desempate  
*/

int compara_default(Forma f1, Forma f2);
int compara_area(Forma f1, Forma f2);
int compara_largura(Forma f1, Forma f2);
int compara_altura(Forma f1, Forma f2);
int compara_cor_preenchimento(Forma f1, Forma f2);

/// @brief 
/// @param f1 
/// @param retangulo_selecao 
/// @return 
int dentro_selecao(Forma f, Forma retangulo_selecao);