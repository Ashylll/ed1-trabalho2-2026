#ifndef ARVORE_H
#define ARVORE_h
#endif

#include <stdlib.h>

/*
    arvore.h

*/

typedef void* NO;
typedef void* ITEM;

/// @brief cria uma árvore
/// @param item informação contida no nó
/// @pre item não deve ser NULL
/// @return nó criado
NO cria_arvore(ITEM item, int (*compara)(NO n1, NO n2));

/// @brief libera a memória de todos os nós da árvore
/// @param raiz nó raiz da árvore
/// @pre raiz não deve ser NULL
void libera_arvore(NO raiz);

/// @brief insere um nó na árvore
/// @param raiz nó raiz da árvore
/// @param item informação contida no nó
/// @pre raiz não deve ser NULL
void insere_arvore(NO raiz, ITEM item, );

/// @brief remove um nó da árvore
/// @param raiz nó raiz da árvore
/// @param item informação contida no nó
/// @pre raiz e item não devem ser NULL
/// @return nó removido
NO remove_no(NO raiz, ITEM item);





