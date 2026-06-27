#include "retangulo.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct StRetangulo {
  int id;
  double x, y, w, h;
  char *corb, *corp;
} StRetangulo;

Retangulo cria_retangulo(int id, double x, double y, double w, double h,
                         const char *corb, const char *corp) {
  if (!corb || !corp || w <= 0 || h <= 0)
    return NULL;

  StRetangulo *retangulo = malloc(sizeof(*retangulo));
  if (!retangulo)
    return NULL;

  retangulo->id = id;
  retangulo->x = x;
  retangulo->y = y;
  retangulo->w = w;
  retangulo->h = h;

  retangulo->corb = malloc(strlen(corb) + 1);
  if (!retangulo->corb) {
    free(retangulo);
    return NULL;
  }
  strcpy(retangulo->corb, corb);

  retangulo->corp = malloc(strlen(corp) + 1);
  if (!retangulo->corp) {
    free(retangulo->corb);
    free(retangulo);
    return NULL;
  }
  strcpy(retangulo->corp, corp);

  return retangulo;
}

double get_area_retangulo(Retangulo r) {
  if (!r)
    return -1;
  StRetangulo *retangulo = (StRetangulo *)r;

  double area = retangulo->w * retangulo->h;

  return area;
}

void libera_retangulo(Retangulo *r) {
  if (!r || !*r)
    return;
  StRetangulo *retangulo = (StRetangulo *)*r;

  free(retangulo->corb);
  free(retangulo->corp);
  free(retangulo);

  *r = NULL;
}

int get_id_retangulo(Retangulo r) {
  StRetangulo *retangulo = (StRetangulo *)r;

  return retangulo->id;
}

double get_x_retangulo(Retangulo r) {
  StRetangulo *retangulo = (StRetangulo *)r;

  return retangulo->x;
}

double get_y_retangulo(Retangulo r) {
  StRetangulo *retangulo = (StRetangulo *)r;

  return retangulo->y;
}

double get_w_retangulo(Retangulo r) {
  StRetangulo *retangulo = (StRetangulo *)r;

  return retangulo->w;
}

double get_h_retangulo(Retangulo r) {
  StRetangulo *retangulo = (StRetangulo *)r;

  return retangulo->h;
}

char *get_corb_retangulo(Retangulo r) {
  if (!r)
    return NULL;
  StRetangulo *retangulo = (StRetangulo *)r;

  return retangulo->corb;
}

char *get_corp_retangulo(Retangulo r) {
  if (!r)
    return NULL;
  StRetangulo *retangulo = (StRetangulo *)r;

  return retangulo->corp;
}

bool set_id_retangulo(Retangulo r, int id) {
  if (!r)
    return false;

  StRetangulo *retangulo = (StRetangulo *)r;
  retangulo->id = id;

  return true;
}

bool set_x_retangulo(Retangulo r, double x) {
  if (!r)
    return false;

  StRetangulo *retangulo = (StRetangulo *)r;
  retangulo->x = x;

  return true;
}

bool set_y_retangulo(Retangulo r, double y) {
  if (!r)
    return false;

  StRetangulo *retangulo = (StRetangulo *)r;
  retangulo->y = y;

  return true;
}

bool set_w_retangulo(Retangulo r, double w) {
  if (!r || w <= 0)
    return false;

  StRetangulo *retangulo = (StRetangulo *)r;
  retangulo->w = w;

  return true;
}

bool set_h_retangulo(Retangulo r, double h) {
  if (!r || h <= 0)
    return false;

  StRetangulo *retangulo = (StRetangulo *)r;
  retangulo->h = h;

  return true;
}

bool set_corb_retangulo(Retangulo r, const char *corb) {
  if (!r || !corb)
    return false;

  StRetangulo *retangulo = (StRetangulo *)r;

  if (retangulo->corb && strcmp(retangulo->corb, corb) == 0)
    return true;

  char *novo = malloc(strlen(corb) + 1);
  if (!novo)
    return false;

  strcpy(novo, corb);
  free(retangulo->corb);
  retangulo->corb = novo;

  return true;
}

bool set_corp_retangulo(Retangulo r, const char *corp) {
  if (!r || !corp)
    return false;

  StRetangulo *retangulo = (StRetangulo *)r;

  if (retangulo->corp && strcmp(retangulo->corp, corp) == 0)
    return true;

  char *novo = malloc(strlen(corp) + 1);
  if (!novo)
    return false;

  strcpy(novo, corp);
  free(retangulo->corp);
  retangulo->corp = novo;

  return true;
}
