#ifndef ARVORE_H
#define ARVORE_h
#endif

#include <stdlib.h>

/*
    arvore.h

*/

typedef void* NO;
typedef void* FORMA;
typedef void* ARVORE;
typedef int(*FCOMPARA_NOS)(NO n1, NO n2);

/// @brief cria uma árvore
/// @param cmp função de comparação de dois nós
/// @pre cmp não devem ser NULL
/// @return nó criado
ARVORE cria_arvore(FCOMPARA_NOS cmp);

/// @brief libera a memória de todos os nós da árvore
/// @param a árvore contendo nó raiz
/// @pre árvore não deve ser NULL
void libera_arvore(ARVORE *a);

/// @brief insere um nó na árvore
/// @param a árvore contendo nó raiz
/// @param forma informação contida no nó
/// @pre arvore e forma não devem ser NULL
void insere_arvore(ARVORE a, FORMA forma);

/// @brief remove um nó da árvore
/// @param a árvore contendo nó raiz
/// @param forma informação contida no nó
/// @pre arvore e forma não devem ser NULL
/// @return nó removido
void remove_arvore(ARVORE a, FORMA forma);