#include <stdlib.h>
#include "arvore.h"

typedef struct No {
    ITEM item;
    No *esq;
    No *dir;
} No;

typedef struct Arvore {
    No *raiz;
    FCOMPARA cmp;
} Arvore;

static No* cria_no(ITEM item){
    No *no = malloc(sizeof(No));

    if (no){
        no->esq = NULL;
        no->dir = NULL;
        no->item = item;
    }

    return no;
}
ARVORE cria_arvore(ITEM item, FCOMPARA cmp){
    Arvore *arvore = malloc(sizeof(Arvore));
    if (arvore){
        arvore->raiz = cria_no(item);
        arvore->cmp = cmp;
    }

    return arvore;
}

static void libera_nos(No *no){
    if (no){
        libera_nos(no->esq);
        libera_nos(no->dir);
        free(no);
    }
}

void libera_arvore(ARVORE a){
    Arvore *arvore = (Arvore*)a;
    if (arvore){
        libera_nos(arvore->raiz);
        free(arvore);
    }
}

static No* insere_no(No* no, ITEM item, FCOMPARA cmp){
    if (!no){
        return cria_no(item);
    }

    if (cmp(item, no->item) < 0){
        no->esq = insere_no(no->esq, item, cmp);
    } 
    else if (cmp(item, no->item) > 0) {
        no->dir = insere_no(no->dir, item, cmp);
    }

    return no;
}

void insere_arvore(ARVORE a, ITEM item) {
    Arvore *arvore = (Arvore*)a;
    arvore->raiz = insere_no(arvore->raiz, item, arvore->cmp);
}