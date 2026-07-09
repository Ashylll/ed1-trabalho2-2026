#ifndef SORTING_H
#define SORTING_H
#endif

#include <stdbool.h>

/*
    sorting.h

*/

typedef void *Forma, *Arvore;
typedef int (*compara_formas_t)(Forma f1, Forma f2);

/// @brief ordena um vetor utilizando bubble sort e gera SVGs de cada estado da ordenação
/// @param comb_out nome combinado dos arquivos de entrada .geo e .qry
/// @param vetor vetor de formas para ordenação
/// @param n tamanho do vetor
/// @param k quantidade formas que devem ser ordenadas
/// @param cmp função de comparação das formas 
void bubble_sort_animado(const char *comb_out, Forma vetor[], int n, int k, compara_formas_t cmp);

/// @brief ordena um vetor utilizando selection sort e gera SVGs de cada estado da ordenação
/// @param comb_out nome combinado dos arquivos de entrada .geo e .qry
/// @param vetor vetor de formas para ordenação
/// @param n tamanho do vetor
/// @param k quantidade de formas que devem ser ordenadas
/// @param cmp função de comparação das formas
void selection_sort_animado(const char *comb_out, Forma vetor[], int n, int k, compara_formas_t cmp);
                    
/// @brief ordena um vetor utilizando insertion sort e gera SVGs de cada estado da ordenação
/// @param comb_out nome combinado dos arquivos de entrada .geo e .qry
/// @param vetor vetor de formas para ordenação
/// @param n tamanho do vetor
/// @param k quantidade de formas que devem ser ordenadas
/// @param cmp função de comparação das formas
void insertion_sort_animado(const char *comb_out, Forma vetor[], int n, int k, compara_formas_t cmp);

/// @brief ordena um vetor utilizando shell sort e gera SVGs de cada estado da ordenação
/// @param comb_out nome combinado dos arquivos de entrada .geo e .qry
/// @param vetor vetor de formas para ordenação
/// @param n tamanho do vetor
/// @param cmp função de comparação das formas
void shell_sort_animado(const char *comb_out, Forma vetor[], int n, compara_formas_t cmp);

/// @brief ordena um vetor utilizando quick sort e gera SVGs de cada estado da ordenação
/// @param comb_out nome combinado dos arquivos de entrada .geo e .qry
/// @param vetor vetor de formas para ordenação
/// @param n tamanho do vetor
/// @param cmp função de comparação das formas
void quick_sort_animado(const char *comb_out, Forma vetor[], int n, compara_formas_t cmp);

/// @brief ordena um vetor utilizando merge sort e gera SVGs de cada estado da ordenação
/// @param comb_out nome combinado dos arquivos de entrada .geo e .qry
/// @param vetor vetor de formas para ordenação
/// @param n tamanho do vetor
/// @param cmp função de comparação das formas
void merge_sort_animado(const char *comb_out, Forma vetor[], int n, compara_formas_t cmp);

/*
    Funções de comparação de formas
    Retorna -1 se f1 for menor que f2, 0 se for igual e 1 se for maior
    Critério default: compara coordenadas y; se empatar compara x e para segundo desempate, a área.
*/

int compara_default(Forma f1, Forma f2);
int compara_area(Forma f1, Forma f2);
int compara_largura(Forma f1, Forma f2);
int compara_altura(Forma f1, Forma f2);
int compara_cor_preenchimento(Forma f1, Forma f2);

/// @brief checa se a forma está dentro do retângulo de seleção
/// @param f1 forma
/// @param retangulo_selecao retângulo de seleção
/// @return true se estiver dentro; false se estiver fora
bool dentro_selecao(Forma f, Forma retangulo_selecao);
