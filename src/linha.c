#include "linha.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct StLinha {
  int id;
  double x1, y1, x2, y2;
  char *cor;
} StLinha;

Linha cria_linha(int id, double x1, double y1, double x2, double y2,
                 const char *cor) {
  if (!cor)
    return NULL;
  if (x1 == x2 && x1 == y1 && x1 == y2)
    return NULL;

  StLinha *linha = malloc(sizeof(*linha));
  if (!linha)
    return NULL;

  linha->id = id;
  linha->x1 = x1;
  linha->y1 = y1;
  linha->x2 = x2;
  linha->y2 = y2;

  linha->cor = malloc(strlen(cor) + 1);
  if (linha->cor == NULL) {
    free(linha);
    return NULL;
  }
  strcpy(linha->cor, cor);

  return linha;
}

double get_comprimento_linha(Linha l) {
  if (!l)
    return -1;
  StLinha *linha = (StLinha *)l;

  double deltaX = linha->x2 - linha->x1;
  double deltaY = linha->y2 - linha->y1;

  double comprimento = sqrt(deltaX * deltaX + deltaY * deltaY);

  return comprimento;
}

void libera_linha(Linha *l) {
  if (!l || !*l)
    return;
  StLinha *linha = (StLinha *)*l;

  free(linha->cor);
  free(linha);

  *l = NULL;
}

// Funções get

int get_id_linha(Linha l) {
  StLinha *linha = (StLinha *)l;

  return linha->id;
}

double get_x1_linha(Linha l) {
  StLinha *linha = (StLinha *)l;

  return linha->x1;
}

double get_y1_linha(Linha l) {
  StLinha *linha = (StLinha *)l;

  return linha->y1;
}

double get_x2_linha(Linha l) {
  StLinha *linha = (StLinha *)l;

  return linha->x2;
}

double get_y2_linha(Linha l) {
  StLinha *linha = (StLinha *)l;

  return linha->y2;
}

char *get_cor_linha(Linha l) {
  StLinha *linha = (StLinha *)l;

  return linha->cor;
}

double get_area_linha(Linha l) {
  double comprimento = get_comprimento_linha(l);

  return 1.5 * comprimento;
}

// Funções set

bool set_id_linha(Linha l, int id) {
  if (!l)
    return false;

  StLinha *linha = (StLinha *)l;
  linha->id = id;

  return true;
}

bool set_x1_linha(Linha l, double x1) {
  if (!l)
    return false;

  StLinha *linha = (StLinha *)l;
  linha->x1 = x1;

  return true;
}

bool set_y1_linha(Linha l, double y1) {
  if (!l)
    return false;

  StLinha *linha = (StLinha *)l;
  linha->y1 = y1;

  return true;
}

bool set_x2_linha(Linha l, double x2) {
  if (!l)
    return false;

  StLinha *linha = (StLinha *)l;
  linha->x2 = x2;

  return true;
}

bool set_y2_linha(Linha l, double y2) {
  if (!l)
    return false;

  StLinha *linha = (StLinha *)l;
  linha->y2 = y2;

  return true;
}

bool set_ancora_linha(Linha l, double x, double y) {
  if (!l)
    return false;

  StLinha *linha = (StLinha *)l;

  double dx = x - linha->x1;
  double dy = y - linha->y1;

  linha->x1 = x;
  linha->y1 = y;

  linha->x2 = linha->x2 + dx;
  linha->y2 = linha->y2 + dy;

  return true;
}

bool set_cor(Linha l, const char *cor) {
  if (!l || !cor)
    return false;
  StLinha *linha = (StLinha *)l;

  if (linha->cor && strcmp(linha->cor, cor) == 0)
    return true;

  char *novo = malloc(strlen(cor) + 1);
  if (!novo)
    return false;

  strcpy(novo, cor);
  free(linha->cor);
  linha->cor = novo;

  return true;
}
