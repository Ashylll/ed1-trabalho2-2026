#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>

/*
    arvore.h

    Árvore é um modelo abstrato de estruturação de dados no qual os elementos são organizados em nós:
        - O primeiro nó é a raiz e não possui pai
        - Cada nó pode possuir nenhum, um ou dois filhos
        - O nó filho à esquerda é sempre menor que o nó pai
        - O nó filho à direito é sempre maior que o nó pai
    Para o projeto, a árvore carrega FORMAS e recebe uma função para a comparação entre elas.
*/

typedef void *NO, *Forma, *Arvore;
typedef int (*compara_formas_t)(NO n1, NO n2);

/// @brief cria uma árvore
/// @param cmp função de comparação de dois nós
/// @pre cmp não deve ser NULL
/// @return nó criado
Arvore cria_arvore(compara_formas_t cmp);

/// @brief libera a memória de todos os nós da árvore
/// @param a árvore contendo nó raiz
/// @pre árvore não deve ser NULL
void libera_arvore(Arvore *a);

/// @brief insere um nó na árvore
/// @param a árvore contendo nó raiz
/// @param forma informação contida no nó
/// @pre arvore e forma não devem ser NULL
void insere_arvore(Arvore a, Forma forma);

/// @brief remove um nó da árvore
/// @param a árvore contendo nó raiz
/// @param forma informação contida no nó
/// @pre arvore e forma não devem ser NULL
/// @return nó removido
void remove_arvore(Arvore a, Forma forma);

/// @brief retorna o tamanho da árvore
/// @param a árvore
/// @pre a != NULL
/// @return quantidade de nós
int get_tamanho_arvore(Arvore a);

/// @brief escreve as formas contidas na árvore em um arquivo .svg
/// @param fp arquivo .svg aberto em modo escrita
/// @param a árvore
/// @pre fp != NULL && a != NULL
void escreve_arvore_svg(FILE *fp, Arvore a);

/// @brief guarda todas as formas dentro da área de seleção em um vetor
/// @param formas árvore de formas
/// @param retangulo_selecao retângulo de seleção
/// @param vet vetor das formas selecionadas
/// @param n variável para o tamanho do vetor
/// @pre formas != NULL && retangulo_selecao != NULL && vet != NULL && n != NULL
void formas_selecionadas_para_vetor(Arvore formas, Forma retangulo_selecao,
                                    Forma vet[], int *n);

#endif