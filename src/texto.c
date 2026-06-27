#include "texto.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct StEstilo {
  char *fFamily;
  char *fWeight;
  double fSize;
} StEstilo;

typedef struct StTexto {
  int id;
  double x, y;
  char *corb, *corp, a, *txto;

  StEstilo estilo;
} StTexto;

Texto cria_texto(int id, double x, double y, const char *corb, const char *corp,
                 char a, const char *txto) {
  if (!corb || !corp || !txto || a != 'i' && a != 'm' && a != 'f')
    return NULL;

  StTexto *texto = malloc(sizeof(*texto));
  if (!texto)
    return NULL;

  texto->id = id;
  texto->x = x;
  texto->y = y;
  texto->a = a;

  texto->estilo.fFamily = malloc(strlen(FFAMILY_PADRAO) + 1);
  if (!texto->estilo.fFamily) {
    free(texto);
    return NULL;
  }
  strcpy(texto->estilo.fFamily, FFAMILY_PADRAO);

  texto->estilo.fWeight = malloc(strlen(FWEIGHT_PADRAO) + 1);
  if (!texto->estilo.fWeight) {
    free(texto->estilo.fFamily);
    free(texto);
    return NULL;
  }
  strcpy(texto->estilo.fWeight, FWEIGHT_PADRAO);

  texto->estilo.fSize = FSIZE_PADRAO;

  texto->corb = malloc(strlen(corb) + 1);
  if (!texto->corb) {
    free(texto->estilo.fFamily);
    free(texto->estilo.fWeight);
    free(texto);
    return NULL;
  }
  strcpy(texto->corb, corb);

  texto->corp = malloc(strlen(corp) + 1);
  if (!texto->corp) {
    free(texto->corb);
    free(texto->estilo.fFamily);
    free(texto->estilo.fWeight);
    free(texto);
    return NULL;
  }
  strcpy(texto->corp, corp);

  texto->txto = malloc(strlen(txto) + 1);
  if (!texto->txto) {
    free(texto->corp);
    free(texto->corb);
    free(texto->estilo.fFamily);
    free(texto->estilo.fWeight);
    free(texto);
    return NULL;
  }
  strcpy(texto->txto, txto);

  return texto;
}

void libera_texto(Texto *t) {
  if (!t || !*t)
    return;
  StTexto *texto = (StTexto *)*t;

  free(texto->estilo.fFamily);
  free(texto->estilo.fWeight);
  free(texto->corb);
  free(texto->corp);
  free(texto->txto);

  free(texto);

  *t = NULL;
}

int get_id_texto(Texto t) {
  StTexto *texto = (StTexto *)t;

  return texto->id;
}

double get_x_texto(Texto t) {
  StTexto *texto = (StTexto *)t;

  return texto->x;
}

double get_y_texto(Texto t) {
  StTexto *texto = (StTexto *)t;

  return texto->y;
}

char *get_corb_texto(Texto t) {
  if (!t)
    return NULL;
  StTexto *texto = (StTexto *)t;

  return texto->corb;
}

char *get_corp_texto(Texto t) {
  if (!t)
    return NULL;
  StTexto *texto = (StTexto *)t;

  return texto->corp;
}

char get_posicao_ancora_texto(Texto t) {
  StTexto *texto = (StTexto *)t;

  return texto->a;
}

char *get_palavra_texto(Texto t) {
  if (!t)
    return NULL;
  StTexto *texto = (StTexto *)t;

  return texto->txto;
}

double get_area_texto(Texto t) {
  char *texto = get_palavra_texto(t);
  int comprimento = strlen(texto);

  return 10 * comprimento;
}

bool set_id_texto(Texto t, int id) {
  if (!t)
    return false;

  StTexto *texto = (StTexto *)t;
  texto->id = id;

  return true;
}

bool set_x_texto(Texto t, double x) {
  if (!t)
    return false;

  StTexto *texto = (StTexto *)t;
  texto->x = x;

  return true;
}

bool set_y_texto(Texto t, double y) {
  if (!t)
    return false;

  StTexto *texto = (StTexto *)t;
  texto->y = y;

  return true;
}

bool set_corb_texto(Texto t, const char *corb) {
  if (!t || !corb)
    return false;

  StTexto *texto = (StTexto *)t;

  if (texto->corb && strcmp(texto->corb, corb) == 0)
    return true;

  char *novo = malloc(strlen(corb) + 1);
  if (!novo)
    return false;

  strcpy(novo, corb);
  free(texto->corb);
  texto->corb = novo;

  return true;
}

bool set_corp_texto(Texto t, const char *corp) {
  if (!t || !corp)
    return false;

  StTexto *texto = (StTexto *)t;

  if (texto->corp && strcmp(texto->corp, corp) == 0)
    return true;

  char *novo = malloc(strlen(corp) + 1);
  if (!novo)
    return false;

  strcpy(novo, corp);
  free(texto->corp);
  texto->corp = novo;

  return true;
}

bool set_posicao_ancora_texto(Texto t, char a) {
  if (!t)
    return false;
  if (a != 'i' && a != 'm' && a != 'f')
    return false;

  StTexto *texto = (StTexto *)t;
  texto->a = a;

  return true;
}

bool set_palavra_texto(Texto t, const char *txto) {
  if (!t || !txto)
    return false;

  StTexto *texto = (StTexto *)t;

  if (texto->txto && strcmp(texto->txto, txto) == 0)
    return true;

  char *novo = malloc(strlen(txto) + 1);
  if (!novo)
    return false;

  strcpy(novo, txto);
  free(texto->txto);
  texto->txto = novo;

  return true;
}

bool muda_estilo(Texto t, const char *fFamily, const char *fWeight,
                 double fSize) {
  if (!t || !fFamily || !fWeight || fSize <= 0)
    return false;

  StTexto *texto = (StTexto *)t;

  if (texto->estilo.fFamily && texto->estilo.fWeight &&
      strcmp(texto->estilo.fFamily, fFamily) == 0 &&
      strcmp(texto->estilo.fWeight, fWeight) == 0 &&
      texto->estilo.fSize == fSize) {
    return true;
  }

  char *novaFamily = malloc(strlen(fFamily) + 1);
  if (!novaFamily)
    return false;

  char *novoWeight = malloc(strlen(fWeight) + 1);
  if (!novoWeight) {
    free(novaFamily);
    return false;
  }

  strcpy(novaFamily, fFamily);
  free(texto->estilo.fFamily);

  strcpy(novoWeight, fWeight);
  free(texto->estilo.fWeight);

  texto->estilo.fFamily = novaFamily;
  texto->estilo.fWeight = novoWeight;
  texto->estilo.fSize = fSize;

  return true;
}

char *get_family_texto(Texto t) {
  if (!t)
    return NULL;
  StTexto *texto = (StTexto *)t;

  return texto->estilo.fFamily;
}

char *get_weight_texto(Texto t) {
  if (!t)
    return NULL;
  StTexto *texto = (StTexto *)t;

  return texto->estilo.fWeight;
}

double get_size_texto(Texto t) {
  if (!t)
    return -1;
  StTexto *texto = (StTexto *)t;

  return texto->estilo.fSize;
}
