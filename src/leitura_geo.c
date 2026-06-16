#include "leitura_geo.h"
#include "forma.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "arvore.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// estilo do texto
static char family[32] = FFAMILY_PADRAO;
static char weight[32] = FWEIGHT_PADRAO;
static double size = FSIZE_PADRAO; 

/* Comandos .geo */

static bool comando_c(const char *linha, Arvore a){
    int i; 
    double x, y, r;
    char corb[32], corp[32];

    if(sscanf(linha, "%*s %d %lf %lf %lf %31s %31s", &i, &x, &y, &r, corb, corp) != 6) return false;

    Circulo c = cria_circulo(i, x, y, r, corb, corp);
    if (!c) return false;

    Forma f = cria_forma('c', c);
    insere_arvore(a, f);

    return true;    
}

static bool comando_r(const char *linha, Arvore a){
    int i;
    double x, y, w, h;
    char corb[32], corp[32];

    if(sscanf(linha, "%*s %d %lf %lf %lf %lf %31s %31s", &i, &x, &y, &w, &h, corb, corp) != 7) return false;
    
    Retangulo r = cria_retangulo(i, x, y, w, h, corb, corp);
    if (!r) return false;

    Forma f = cria_forma('r', r);
    insere_arvore(a, f);

    return true;
}

static bool comando_l(const char *linha, Arvore a){
    int i;
    double x1, y1, x2, y2;
    char cor[32];

    if(sscanf(linha, "%*s %d %lf %lf %lf %lf %31s", &i, &x1, &y1, &x2, &y2, cor) != 6) return false;

    Linha l = NULL;
    if (x1 != x2) l = (x1 < x2) ? cria_linha(i, x1, y1, x2, y2, cor) : cria_linha(i, x2, y2, x1, y1, cor);
    else l = (y1 < y2) ? cria_linha(i, x1, y1, x2, y2, cor) : cria_linha(i, x2, y2, x1, y1, cor);

    if (!l) return false;

    Forma f = cria_forma('l', l);
    insere_arvore(a, f);

    return true;

}

static bool comando_t(const char *linha, Arvore a){
    int i;
    double x, y;
    char corb[32], corp[32], ancora, txto[512];

    if(sscanf(linha, "%*s %d %lf %lf %31s %31s %c %[^\n]", &i, &x, &y, corb, corp, &ancora, txto) < 7) return false;
    
    Texto t = cria_texto(i, x, y, corb, corp, ancora, txto);
    if (!t) return false;
    
    muda_estilo(t, family, weight, size);
    Forma f = cria_forma('t', t);
    insere_arvore(a, f);
    
    return true;
}

static char* converte_weight(char *weight){
    if (!weight) return "normal";
    if (strcmp(weight, "b+") == 0) return "bolder";
    if (strcmp(weight, "b")  == 0) return "bold";
    if (strcmp(weight, "n")  == 0) return "normal";
    if (strcmp(weight, "l")  == 0) return "lighter";
    
    return weight;
}

static bool comando_ts(const char *linha){
    char novo_family[32], novo_weight[8];
    double novo_size;

    if (sscanf(linha, "%*s %31s %7s %lf", novo_family, novo_weight, &novo_size) != 3) return false;
    
    strcpy(family, novo_family);
    strcpy(weight, converte_weight(novo_weight));
    size = novo_size;

    return true;
}

bool leitura_geo(const char* path_geo, Arvore a){
    FILE* fp_geo = fopen(path_geo, "r");
    if(!fp_geo) return false;

    char linha[1024], comando[8];

    while (fgets(linha, sizeof linha, fp_geo)){
        if(sscanf(linha, "%7s", comando) != 1) continue;
        if(comando[0] == '#') continue;
    
        switch (comando[0]){
            case 'c': comando_c(linha, a); break;
            case 'r': comando_r(linha, a); break;
            case 'l': comando_l(linha, a); break;
            case 't':
                if (comando[1] == 's') comando_ts(linha);
                else comando_t(linha, a); break;
            default: return false;
        }
    }

    fclose(fp_geo);
    return true;
}
