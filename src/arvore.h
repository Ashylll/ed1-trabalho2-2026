#ifndef ARVORE_H
#define ARVORE_h
#endif

#include <stdlib.h>

/*
    arvore.h

*/

typedef void* NO;
typedef void* ITEM;
typedef void* ARVORE;
typedef int(*FCOMPARA_NOS)(NO n1, NO n2);

/// @brief cria uma árvore
/// @param item informação contida no nó
/// @param cmp função de comparação de dois nós
/// @pre item e cmp não devem ser NULL
/// @return nó criado
ARVORE cria_arvore(ITEM item, FCOMPARA_NOS cmp);

/// @brief libera a memória de todos os nós da árvore
/// @param a árvore contendo nó raiz
/// @pre árvore não deve ser NULL
void libera_arvore(ARVORE a);

/// @brief insere um nó na árvore
/// @param a árvore contendo nó raiz
/// @param item informação contida no nó
/// @pre arvore e item não devem ser NULL
void insere_arvore(ARVORE a, ITEM item);

/// @brief remove um nó da árvore
/// @param a árvore contendo nó raiz
/// @param item informação contida no nó
/// @pre arvore e item não devem ser NULL
/// @return nó removido
NO remove_a(ARVORE a, ITEM item);