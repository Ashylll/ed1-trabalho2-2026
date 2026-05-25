#include <stdlib.h>
#include "arvore.h"

typedef struct No {
    ITEM item;
    No *esq;
    No *dir;
} No;

typedef struct Arvore {
    No *raiz;

}

