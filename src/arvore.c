#include "arvore.h"
#include "forma.h"
#include "sorting.h"
#include <stdlib.h>

typedef struct No {
  Forma forma;
  struct No *esq;
  struct No *dir;
} No;

typedef struct StArvore {
  No *raiz;
  compara_formas_t cmp;
} StArvore;

static No *cria_no(Forma forma) {
  No *no = malloc(sizeof(No));

  if (no) {
    no->esq = NULL;
    no->dir = NULL;
    no->forma = forma;
  }

  return no;
}

Arvore cria_arvore(compara_formas_t cmp) {
  if (!cmp)
    return NULL;
  StArvore *arvore = malloc(sizeof(StArvore));
  if (arvore) {
    arvore->raiz = NULL;
    arvore->cmp = cmp;
  }
  return arvore;
}

static void libera_nos(No *no) {
  if (no) {
    libera_nos(no->esq);
    libera_nos(no->dir);
    libera_forma(&no->forma);
    free(no);
  }
}

void libera_arvore(Arvore *a) {
  if (!a || !*a)
    return;
  StArvore *arvore = (StArvore *)*a;

  libera_nos(arvore->raiz);
  free(arvore);

  *a = NULL;
}

static No *insere_no(No *no, Forma forma, compara_formas_t cmp) {
  if (!no) {
    return cria_no(forma);
  }

  switch (cmp(forma, no->forma)) {
  case -1:
    no->esq = insere_no(no->esq, forma, cmp);
    break;
  case 1:
    no->dir = insere_no(no->dir, forma, cmp);
  }
  return no;
}

void insere_arvore(Arvore a, Forma forma) {
  StArvore *arvore = (StArvore *)a;
  arvore->raiz = insere_no(arvore->raiz, forma, arvore->cmp);
}

static No *encontra_menor(No *raiz) {
  while (raiz && raiz->esq) {
    raiz = raiz->esq;
  }
  return raiz;
}

static No *encontra_maior(No *raiz) {
  while (raiz && raiz->dir) {
    raiz = raiz->dir;
  }
  return raiz;
}

static No *remove_no(No *no, Forma forma, compara_formas_t cmp) {
  if (!no) {
    return no;
  }
  switch (cmp(forma, no->forma)) {
  case -1:
    no->esq = remove_no(no->esq, forma, cmp);
    break;
  case 1:
    no->dir = remove_no(no->dir, forma, cmp);
    break;
  default:
    if (!no->esq && !no->dir) { // folha
      free(no);
      return NULL;
    } else if (no->esq || no->dir) { // um filho
      No *aux = no->esq ? no->esq : no->dir;
      free(no);
      return aux;
    } else { // dois filhos
      No *aux = encontra_maior(no->esq);
      no->forma = aux->forma;
      no->esq = remove_no(no->esq, no->forma, cmp);
    }
    break;
  }
  return no;
}

void remove_arvore(Arvore a, Forma forma) {
  StArvore *arvore = (StArvore *)a;
  arvore->raiz = remove_no(arvore->raiz, forma, arvore->cmp);
}

static No *get_raiz_arvore(Arvore a) {
  if (!a)
    return NULL;
  StArvore *arvore = (StArvore *)a;
  return arvore->raiz;
}

static int get_tamanho(No *raiz) {
  if (!raiz)
    return 0;

  return 1 + get_tamanho(raiz->esq) + get_tamanho(raiz->dir);
}

int get_tamanho_arvore(Arvore a) {
  if (!a)
    return -1;
  return get_tamanho(get_raiz_arvore(a));
}

static void escreve_no_svg(FILE *fp, No *raiz) {
  if (!raiz)
    return;

  escreve_forma_svg(fp, raiz->forma);
  escreve_no_svg(fp, raiz->esq);
  escreve_no_svg(fp, raiz->dir);
}

void escreve_arvore_svg(FILE *fp, Arvore a) {
  escreve_no_svg(fp, get_raiz_arvore(a));
}

static void formas_para_vetor(No *no, Forma retangulo_selecao, Forma vet[],
                              int *n) {
  if (!no)
    return;

  formas_para_vetor(no->esq, retangulo_selecao, vet, n);

  if (dentro_selecao(no->forma, retangulo_selecao)) {
    vet[*n] = no->forma;
    (*n)++;
  }

  formas_para_vetor(no->dir, retangulo_selecao, vet, n);
}

void formas_selecionadas_para_vetor(Arvore a, Forma retangulo_selecao,
                                    Forma vet[], int *n) {
  StArvore *arvore = (StArvore *)a;
  if (arvore && arvore->raiz) {
    formas_para_vetor(arvore->raiz, retangulo_selecao, vet, n);
  }
}
