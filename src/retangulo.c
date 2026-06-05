#include "retangulo.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct stRetangulo {
    int id;
    double x, y, w, h;
    char *corb, *corp;
} stRetangulo;

RETANGULO cria_retangulo(int id, double x, double y, double w, double h, const char* corb, const char* corp){
    if (!corb || !corp || w <= 0 || h <= 0) return NULL;
 
    stRetangulo *retangulo = malloc(sizeof(*retangulo));
    if (!retangulo) return NULL;

    retangulo->id = id;
    retangulo->x = x;
    retangulo->y = y;
    retangulo->w = w;
    retangulo->h = h;

    retangulo->corb = malloc(strlen(corb)+1);
    if (!retangulo->corb){
        free(retangulo);
        return NULL;
    }
    strcpy(retangulo->corb, corb);

    retangulo->corp = malloc(strlen(corp)+1);
    if (!retangulo->corp){
        free(retangulo->corb);
        free(retangulo);
        return NULL;
    }
    strcpy(retangulo->corp, corp);

    return retangulo;
}

double getArea_retangulo(RETANGULO r){
    if(!r) return -1;
    stRetangulo *retangulo = (stRetangulo*)r;

     double area = retangulo->w * retangulo->h;

     return area;
} 

void libera_retangulo(RETANGULO *r){
    if(!r || !*r) return;
    stRetangulo *retangulo = (stRetangulo*)*r;

    free(retangulo->corb);
    free(retangulo->corp);
    free(retangulo);

    *r = NULL;
}

int getId_retangulo(RETANGULO r){
    stRetangulo *retangulo = (stRetangulo*)r;

    return retangulo->id;
}

double getX_retangulo(RETANGULO r){
    stRetangulo *retangulo = (stRetangulo*)r;

    return retangulo->x;
}

double getY_retangulo(RETANGULO r){
    stRetangulo *retangulo = (stRetangulo*)r;

    return retangulo->y;
}

double getW_retangulo(RETANGULO r){
    stRetangulo *retangulo = (stRetangulo*)r;

    return retangulo->w;
}

double getH_retangulo(RETANGULO r){
    stRetangulo *retangulo = (stRetangulo*)r;

    return retangulo->h;
}

char* getCORB_retangulo(RETANGULO r){
    if (!r)  return NULL;
    stRetangulo *retangulo = (stRetangulo*)r;

    return retangulo->corb;
}

char* getCORP_retangulo(RETANGULO r){
    if (!r)  return NULL;
    stRetangulo *retangulo = (stRetangulo*)r;

    return retangulo->corp;
}

bool setId_retangulo(RETANGULO r, int id){
    if (!r) return false;

    stRetangulo *retangulo = (stRetangulo*)r; 
    retangulo->id = id;

    return true;
}

bool setX_retangulo(RETANGULO r, double x){
    if (!r) return false;

   stRetangulo *retangulo = (stRetangulo*)r; 
    retangulo->x = x;

    return true;
}

bool setY_retangulo(RETANGULO r, double y){
    if (!r) return false;

    stRetangulo *retangulo = (stRetangulo*)r; 
    retangulo->y = y;

    return true;
}

bool setW_retangulo(RETANGULO r, double w){
    if (!r || w <= 0) return false;

    stRetangulo *retangulo = (stRetangulo*)r; 
    retangulo->w = w;

    return true;
}

bool setH_retangulo(RETANGULO r, double h){
    if (!r || h <= 0) return false;

    stRetangulo *retangulo = (stRetangulo*)r; 
    retangulo->h = h;

    return true;
}


bool setCORB_retangulo(RETANGULO r, const char* corb){
    if (!r || !corb) return false;

    stRetangulo *retangulo = (stRetangulo*)r;
    
    if (retangulo->corb && strcmp(retangulo->corb, corb) == 0) return true;

    char *novo = malloc(strlen(corb)+1);
    if (!novo) return false;

    strcpy(novo, corb);
    free(retangulo->corb);
    retangulo->corb = novo;

    return true;
}

bool setCORP_retangulo(RETANGULO r, const char* corp){
    if (!r || !corp) return false;

    stRetangulo *retangulo = (stRetangulo*)r;
    
    if (retangulo->corp && strcmp(retangulo->corp, corp) == 0) return true;             

    char *novo = malloc(strlen(corp)+1);
    if (!novo) return false;

    strcpy(novo, corp);
    free(retangulo->corp);
    retangulo->corp = novo;

    return true;
}