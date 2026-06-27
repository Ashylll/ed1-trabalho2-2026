#include "circulo.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct StCirculo {
  int id;
  double x, y, r;
  char *corb, *corp;
} StCirculo;

Circulo cria_circulo(int id, double x, double y, double r, const char *corb,
                     const char *corp) {
  if (!corb || !corp || r <= 0)
    return NULL;

  StCirculo *circulo = malloc(sizeof(*circulo));
  if (!circulo)
    return NULL;

  circulo->id = id;
  circulo->x = x;
  circulo->y = y;
  circulo->r = r;

  circulo->corb = malloc(strlen(corb) + 1);
  if (circulo->corb == NULL) {
    free(circulo);
    return NULL;
  }
  strcpy(circulo->corb, corb);

  circulo->corp = malloc(strlen(corp) + 1);
  if (circulo->corp == NULL) {
    free(circulo->corb);
    free(circulo);
    return NULL;
  }
  strcpy(circulo->corp, corp);

  return circulo;
}

double get_area_circulo(Circulo c) {
  assert(c != NULL);
  StCirculo *circulo = (StCirculo *)c;

  double area = PI * circulo->r * circulo->r;

  return area;
}

void libera_circulo(Circulo *c) {
  if (!c || !*c)
    return;
  StCirculo *circulo = (StCirculo *)*c;

  free(circulo->corb);
  free(circulo->corp);
  free(circulo);

  *c = NULL;
}

int get_id_circulo(Circulo c) {
  ;
  StCirculo *circulo = (StCirculo *)c;

  return circulo->id;
}

double get_x_circulo(Circulo c) {
  StCirculo *circulo = (StCirculo *)c;

  return circulo->x;
}

double get_y_circulo(Circulo c) {
  StCirculo *circulo = (StCirculo *)c;

  return circulo->y;
}

double get_raio_circulo(Circulo c) {
  StCirculo *circulo = (StCirculo *)c;

  return circulo->r;
}

char *get_corb_circulo(Circulo c) {
  if (!c)
    return NULL;
  StCirculo *circulo = (StCirculo *)c;

  return circulo->corb;
}

char *get_corp_circulo(Circulo c) {
  if (!c)
    return NULL;
  StCirculo *circulo = (StCirculo *)c;

  return circulo->corp;
}

bool set_id_circulo(Circulo c, int id) {
  if (!c)
    return false;

  StCirculo *circulo = (StCirculo *)c;
  circulo->id = id;
  return true;
}

bool set_x_circulo(Circulo c, double x) {
  if (!c)
    return false;

  StCirculo *circulo = (StCirculo *)c;
  circulo->x = x;

  return true;
}

bool set_y_circulo(Circulo c, double y) {
  if (!c)
    return false;

  StCirculo *circulo = (StCirculo *)c;
  circulo->y = y;

  return true;
}

bool set_raio_circulo(Circulo c, double r) {
  if (!c || r <= 0)
    return false;

  StCirculo *circulo = (StCirculo *)c;
  circulo->r = r;

  return true;
}

bool set_corb_circulo(Circulo c, const char *corb) {
  if (!c || !corb)
    return false;

  StCirculo *circulo = (StCirculo *)c;

  if (circulo->corb && strcmp(circulo->corb, corb) == 0)
    return true;

  char *novo = malloc(strlen(corb) + 1);
  if (!novo)
    return false;

  strcpy(novo, corb);
  free(circulo->corb);
  circulo->corb = novo;

  return true;
}

bool set_corp_circulo(Circulo c, const char *corp) {
  if (!c || !corp)
    return false;

  StCirculo *circulo = (StCirculo *)c;

  if (circulo->corp && strcmp(circulo->corp, corp) == 0)
    return true;

  char *novo = malloc(strlen(corp) + 1);
  if (!novo)
    return false;

  strcpy(novo, corp);
  free(circulo->corp);
  circulo->corp = novo;

  return true;
}
