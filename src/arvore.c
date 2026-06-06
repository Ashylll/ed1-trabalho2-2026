#include <stdlib.h>
#include "arvore.h"
#include "forma.h"

typedef struct No {
    FORMA forma;
    No *esq;
    No *dir;
} No;

typedef struct Arvore {
    No *raiz;
    FCOMPARA_NOS cmp;
} Arvore;

static No* cria_no(FORMA forma){
    No *no = malloc(sizeof(No));

    if (no){
        no->esq = NULL;
        no->dir = NULL;
        no->forma = forma;
    }

    return no;
}
ARVORE cria_arvore(FCOMPARA_NOS cmp){
    if (!cmp) return NULL;
    Arvore *arvore = malloc(sizeof(Arvore));
    if (arvore) arvore->cmp = cmp;

    return arvore;
}

static void libera_nos(No *no){
    if (no){
        libera_nos(no->esq);
        libera_nos(no->dir);
        free(no);
    }
}

void libera_arvore(ARVORE *a){
    Arvore *arvore = (Arvore*)a;
    if (arvore){
        libera_nos(arvore->raiz);
        free(arvore);
    }

    a = NULL;
}

static No* insere_no(No* no, FORMA forma, FCOMPARA_NOS cmp){
    if (!no){
        return cria_no(forma);
    }

    switch (cmp(forma, no->forma)){
        case -1: no->esq = insere_no(no->esq, forma, cmp); break;
        case 1: no->dir = insere_no(no->dir, forma, cmp);
    }
    return no;
}

void insere_arvore(ARVORE a, FORMA forma) {
    Arvore *arvore = (Arvore*)a;
    arvore->raiz = insere_no(arvore->raiz, forma, arvore->cmp);
}


static No* remove_no(No* no, FORMA forma, FCOMPARA_NOS cmp){
    if (!no){
        return no;
    }
    switch (cmp(forma, no->forma)){
    case -1: no->esq = remove_no(no->esq, forma, cmp); break;
    case 1: no-> dir = remove_no(no->dir, forma, cmp); break;
    default:
        if (!no->esq && !no->dir){ // folha
            libera_forma(&no->forma);
            free(no);
            return NULL;
        }
        else if (no->esq || no->dir){ // um filho
            No* aux = no->esq ? no->esq : no->dir;
            libera_forma(&no->forma);   
            free(no);
            return aux; 
        }
        else { // dois filhos
            No* aux = encontra_maior(no->esq);
            no->forma = aux->forma;
            no->esq = remove_no(no->esq, no->forma, cmp);
        }
        break;
    }
    return no;
}

void remove_arvore(ARVORE a, FORMA forma){
    Arvore* arvore = (Arvore*)a;
    remove_no(arvore->raiz, forma, arvore->cmp);
}

static No* encontra_menor(No* raiz){ 
    while (raiz && raiz->esq){
        raiz = raiz->esq;
    }
    return raiz;
}

static No* encontra_maior(No* raiz){
    while (raiz && raiz->dir){
        raiz = raiz->dir;
    }
    return raiz;
}

static No* getRaiz_arvore(ARVORE a){
    if (!a) return NULL;
    Arvore *arvore = (Arvore*)a;
    return arvore->raiz;
}


static int getTamanho(No* raiz){
    if (!raiz) return 0;

    return 1 + getTamanho(raiz->esq) + getTamanho(raiz->dir);
}

int getTamanho_arvore(ARVORE a){
    if (!a) return -1;
    return getTamanho(getRaiz_arvore(a));
}