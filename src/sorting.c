#include "sorting.h"
#include "arvore.h"
#include "forma.h"
#include "svg.h"
#include <string.h>

#define X_INICIAL 100.0
#define Y_INICIAL 100.0
#define DW 10.0

void bubble_sort_animado(const char *comb_out, Forma vetor[], int n, int k,
                         compara_formas_t cmp) {
  int i, j;
  Forma aux;
  int cont_ordenados = 0;
  int numeracao_frame = 0;

  escreve_frame(comb_out, numeracao_frame, X_INICIAL, Y_INICIAL, DW, vetor,
                n); // frame inicial antes da ordenação

  for (i = 0; i < n - 1; i++) {
    if (cont_ordenados == k)
      return;

    for (j = n - 1; j > i; j--) {
      if (cmp(vetor[j], vetor[j - 1]) < 0) {
        aux = vetor[j];
        vetor[j] = vetor[j - 1];
        vetor[j - 1] = aux;

        numeracao_frame += 1;
        escreve_frame(comb_out, numeracao_frame, X_INICIAL, Y_INICIAL, DW,
                      vetor, n); // frame após troca
      }
    }

    cont_ordenados++;
  }
}

void selection_sort_animado(const char *comb_out, Forma vetor[], int n, int k,
                            compara_formas_t cmp) {
  int i, j, min_idx;
  Forma aux;
  int cont_ordenados = 0;
  int numeracao_frame = 0;

  escreve_frame(comb_out, numeracao_frame, X_INICIAL, Y_INICIAL, DW, vetor,
                n);

  for (i = 0; i < n - 1; i++) {
    if (cont_ordenados == k)
      return;

    min_idx = i;
    
    // Encontra o índice do menor elemento
    for (j = i + 1; j < n; j++) {
      if (cmp(vetor[min_idx], vetor[j]) > 0) {
        min_idx = j;
      }
    }

    // Faz a troca e gera o frame
    if (min_idx != i) {
      aux = vetor[i];
      vetor[i] = vetor[min_idx];
      vetor[min_idx] = aux;

      numeracao_frame += 1;
      escreve_frame(comb_out, numeracao_frame, X_INICIAL, Y_INICIAL, DW,
                    vetor, n); // frame após troca
    }

    cont_ordenados++;
  }
}

void insertion_sort_animado(const char *comb_out, Forma vetor[], int n, int k,
                            compara_formas_t cmp) {
  int i, j;
  Forma aux;
  int cont_ordenados = 0;
  int numeracao_frame = 0;

  escreve_frame(comb_out, numeracao_frame, X_INICIAL, Y_INICIAL, DW, vetor, n);

  for (i = 1; i < n; i++) {
    if (cont_ordenados == k) return;

    j = i;
    while (j > 0 && cmp(vetor[j], vetor[j - 1]) < 0) {
      aux = vetor[j];
      vetor[j] = vetor[j - 1];
      vetor[j - 1] = aux;
      
      numeracao_frame += 1;
      escreve_frame(comb_out, numeracao_frame, X_INICIAL, Y_INICIAL, DW, vetor, n);
      
      j = j - 1;
    }
    
    cont_ordenados++;
  }
}

void shell_sort_animado(const char *comb_out, Forma vetor[], int n, compara_formas_t cmp) {
  int i, j, h;
  Forma aux;
  int numeracao_frame = 0;

  escreve_frame(comb_out, numeracao_frame, X_INICIAL, Y_INICIAL, DW, vetor, n);

  h = 1;
  while (h < n / 3) h = 3 * h + 1;

  for (; h > 0; h = (h - 1) / 3) {
    for (i = h; i < n; i++) {
      for (j = i; j >= h && cmp(vetor[j], vetor[j - h]) < 0; j -= h) {
        
        aux = vetor[j];
        vetor[j] = vetor[j - h];
        vetor[j - h] = aux;

        numeracao_frame++;
        escreve_frame(comb_out, numeracao_frame, X_INICIAL, Y_INICIAL, DW, vetor, n);
      }
    }
  }
}

static void troca_e_anima(const char *comb_out, Forma vetor[], int i, int j, int *numeracao_frame, int n) {
    Forma aux = vetor[i];
    vetor[i] = vetor[j];
    vetor[j] = aux;

    (*numeracao_frame)++;

    escreve_frame(comb_out, *numeracao_frame, X_INICIAL, Y_INICIAL, DW, vetor, n);
}

static int particiona(const char *comb_out, Forma vetor[], int baixo, int alto, int *numeracao_frame, int n, compara_formas_t cmp) {
    Forma pivo = vetor[alto];
    int i = (baixo - 1);

    for (int j = baixo; j <= alto - 1; j++) {
        if (cmp(vetor[j], pivo) < 0) {
            i++;
            troca_e_anima(comb_out, vetor, i, j, numeracao_frame, n);
        }
    }
    troca_e_anima(comb_out, vetor, i + 1, alto, numeracao_frame, n);
    return (i + 1);
}

static void quick_sort_recursivo(const char *comb_out, Forma vetor[], int baixo, int alto, int *numeracao_frame, int n, compara_formas_t cmp) {
    if (baixo < alto) {
        int pi = particiona(comb_out, vetor, baixo, alto, numeracao_frame, n, cmp);

        quick_sort_recursivo(comb_out, vetor, baixo, pi - 1, numeracao_frame, n, cmp);
        quick_sort_recursivo(comb_out, vetor, pi + 1, alto, numeracao_frame, n, cmp);
    }
}

void quick_sort_animado(const char *comb_out, Forma vetor[], int n, compara_formas_t cmp) {
    int numeracao_frame = 0; 
    
    escreve_frame(comb_out, numeracao_frame, X_INICIAL, Y_INICIAL, DW, vetor, n);

    quick_sort_recursivo(comb_out, vetor, 0, n - 1, &numeracao_frame, n, cmp);
}

static void merge(const char *comb_out, Forma vetor[], int inicio, int meio, int fim, int *numeracao_frame, int n, compara_formas_t cmp) {
    int i, j, k;
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    Forma *L = (Forma *)malloc(n1 * sizeof(Forma));
    Forma *R = (Forma *)malloc(n2 * sizeof(Forma));

    for (i = 0; i < n1; i++) L[i] = vetor[inicio + i];
    for (j = 0; j < n2; j++) R[j] = vetor[meio + 1 + j];

    i = 0; j = 0; k = inicio;
    while (i < n1 && j < n2) {
        if (cmp(L[i], R[j]) <= 0) {
            vetor[k] = L[i++];
        } else {
            vetor[k] = R[j++];
        }

        (*numeracao_frame)++;
        escreve_frame(comb_out, *numeracao_frame, X_INICIAL, Y_INICIAL, DW, vetor, n);
        k++;
    }

    // Copia o restante dos elementos
    while (i < n1) {
        vetor[k++] = L[i++];
        (*numeracao_frame)++;
        escreve_frame(comb_out, *numeracao_frame, X_INICIAL, Y_INICIAL, DW, vetor, n);
    }
    while (j < n2) {
        vetor[k++] = R[j++];
        (*numeracao_frame)++;
        escreve_frame(comb_out, *numeracao_frame, X_INICIAL, Y_INICIAL, DW, vetor, n);
    }

    free(L);
    free(R);
}

static void merge_sort_recursivo(const char *comb_out, Forma vetor[], int inicio, int fim, int *numeracao_frame, int n, compara_formas_t cmp) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;
        merge_sort_recursivo(comb_out, vetor, inicio, meio, numeracao_frame, n, cmp);
        merge_sort_recursivo(comb_out, vetor, meio + 1, fim, numeracao_frame, n, cmp);

        merge(comb_out, vetor, inicio, meio, fim, numeracao_frame, n, cmp);
    }
}

void merge_sort_animado(const char *comb_out, Forma vetor[], int n, compara_formas_t cmp) {
    int numeracao_frame = 0;
    
    escreve_frame(comb_out, numeracao_frame, X_INICIAL, Y_INICIAL, DW, vetor, n);

    merge_sort_recursivo(comb_out, vetor, 0, n - 1, &numeracao_frame, n, cmp);
}

int compara_default(Forma f1, Forma f2) {
  double x1, y1, x2, y2;
  get_ancora_forma(f1, &x1, &y1);
  get_ancora_forma(f2, &x2, &y2);

  if (y1 != y2)
    return (y1 > y2) ? 1 : -1;

  if (x1 != x2)
    return (x1 > x2) ? 1 : -1;

  double area1 = get_area_forma(f1);
  double area2 = get_area_forma(f2);
  if (area1 != area2)
    return (area1 > area2) ? 1 : -1;

  return 0;
}

int compara_area(Forma f1, Forma f2) {
  double area1 = get_area_forma(f1);
  double area2 = get_area_forma(f2);

  if (area1 != area2)
    return (area1 > area2) ? 1 : -1;

  return 0;
}

int compara_largura(Forma f1, Forma f2) {
  double largura1 = get_largura_forma(f1);
  double largura2 = get_largura_forma(f2);

  if (largura1 != largura2)
    return (largura1 > largura2) ? 1 : -1;

  return 0;
}

int compara_altura(Forma f1, Forma f2) {
  double altura1 = get_altura_forma(f1);
  double altura2 = get_altura_forma(f2);

  if (altura1 != altura2)
    return (altura1 > altura2) ? 1 : -1;

  return 0;
}

int compara_cor_preenchimento(Forma f1, Forma f2) {
  char *cor1 = get_corp_forma(f1);
  char *cor2 = get_corp_forma(f2);

  int r = 0;
  if (strcmp(cor1, cor2) > 0) r = 1; 
  else  if (strcmp(cor1, cor2) < 0) r = - 1; 

  return r;
}

static inline bool ponto_no_retangulo(double x, double y, double xR, double yR,
                                      double w, double h) {
  const double eps = 1e-9;
  return (xR - eps <= x && x <= xR + w + eps) &&
         (yR - eps <= y && y <= yR + h + eps);
}

bool dentro_selecao(Forma f, Forma retangulo_selecao) {
  double xf, yf, hf, wf;
  get_ancora_forma(f, &xf, &yf);
  hf = get_altura_forma(f);
  wf = get_largura_forma(f);

  double xs, ys, hs, ws;
  get_ancora_forma(retangulo_selecao, &xs, &ys);
  hs = get_altura_forma(retangulo_selecao);
  ws = get_largura_forma(retangulo_selecao);

  switch (get_tipo_forma(f)) {
  case 'c':
    if (ponto_no_retangulo(xf + wf / 2, yf, xs, ys, ws, hs) &&
        ponto_no_retangulo(xf - wf / 2, yf, xs, ys, ws, hs) &&
        ponto_no_retangulo(xf, yf + hf / 2, xs, ys, ws, hs) &&
        ponto_no_retangulo(xf, yf - hf / 2, xs, ys, ws, hs))
      return true;
    else
      return false;

  case 'r':
  case 'l':
  case 't':
    if (ponto_no_retangulo(xf, yf, xs, ys, ws, hs) &&
        ponto_no_retangulo(xf + wf, yf + hf, xs, ys, ws, hs))
      return true;
    else
      return false;

  default:
    return false;
  }
}
