#include "linha.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef struct stLinha {
    int id;
    double x1, y1, x2, y2;
    char *cor;
} stLinha;

LINHA cria_linha(int id, double x1, double y1, double x2, double y2, const char* cor){
    if (!cor) return NULL;
    if (x1 == x2 && x1 == y1 && x1 == y2) return NULL;

    stLinha *linha = malloc(sizeof(*linha));
    if (!linha) return NULL;

    linha->id = id;
    linha->x1 = x1;
    linha->y1 = y1;
    linha->x2 = x2;
    linha->y2 = y2;

    linha->cor = malloc(strlen(cor)+1);
    if (linha->cor == NULL){
        free(linha);
        return NULL;
    }
    strcpy(linha->cor, cor);

    return linha;
}

double getComprimento_linha(LINHA l){
    if (!l) return -1;
    stLinha *linha = (stLinha*)l;

    double deltaX = linha->x2 - linha->x1;
    double deltaY = linha->y2 - linha->y1;

    double comprimento = sqrt(deltaX*deltaX + deltaY*deltaY);

    return comprimento;
}

void libera_linha(LINHA *l){
    if (!l || !*l) return;
    stLinha *linha = (stLinha*)*l;
    
    free(linha->cor);
    free(linha);
    
    *l = NULL;
}

// Funções get

int getId_linha(LINHA l){
    stLinha *linha = (stLinha*)l;

    return linha->id;
}

double getX1_linha(LINHA l){
    stLinha *linha = (stLinha*)l;

    return linha->x1;
}

double getY1_linha(LINHA l){
    stLinha *linha = (stLinha*)l;

    return linha->y1;
}

double getX2_linha(LINHA l){
    stLinha *linha = (stLinha*)l;

    return linha->x2;
}

double getY2_linha(LINHA l){
    stLinha *linha = (stLinha*)l;

    return linha->y2;
}

char* getCOR_linha(LINHA l){
    stLinha *linha = (stLinha*)l;

    return linha->cor;
}

double getArea_lnha(LINHA l){
    double comprimento = getComprimento_linha(l);

    return 1.5 * comprimento;
}

// Funções set

bool setId_linha(LINHA l, int id){
    if (!l) return false;

    stLinha *linha = (stLinha*)l; 
    linha->id = id;

    return true;
}

bool setX1_linha(LINHA l, double x1){
    if (!l) return false;

    stLinha *linha = (stLinha*)l; 
    linha->x1 = x1;
    
    return true;
}

bool setY1_linha(LINHA l, double y1){
    if (!l) return false;

    stLinha *linha = (stLinha*)l; 
    linha->y1 = y1;

    return true;
}

bool setX2_linha(LINHA l, double x2){
    if (!l) return false;

    stLinha *linha = (stLinha*)l; 
    linha->x2 = x2;

    return true;
}

bool setY2_linha(LINHA l, double y2){
    if (!l) return false;

    stLinha *linha = (stLinha*)l; 
    linha->y2 = y2;

    return true;
}

bool setAncora_linha(LINHA l, double x, double y){
    if (!l) return false;

    stLinha *linha = (stLinha*)l;

    double dx = x - linha->x1;
    double dy = y - linha->y1;

    linha->x1 = x;
    linha->y1 = y;
    

    linha->x2 = linha->x2 + dx;
    linha->y2 = linha->y2 + dy;
}

bool setCOR_linha(LINHA l, const char* cor){
    if (!l || !cor) return false;
    stLinha *linha = (stLinha*)l;

    if (linha->cor && strcmp(linha->cor, cor) == 0) return true;

    char *novo = malloc(strlen(cor)+1);
    if (!novo) return false;

    strcpy(novo, cor);
    free(linha->cor);
    linha->cor = novo;

    return true;
}