#include "forma.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct stForma{
    char tipo;
    void* handle;
} stForma;

FORMA cria_forma(char tipo, void* handle){
    if (!handle || (tipo != 'c' && tipo != 'r' && tipo != 't' && tipo != 'l')) return NULL;

    stForma* forma = malloc(sizeof(stForma));
    if (!forma) return NULL;

    forma->tipo = tipo;
    forma->handle = handle;

    return forma;
}

void libera_forma(FORMA *f){
    if (!f || !*f) return;
    stForma *forma = (stForma*)*f;

    void *h = forma->handle;
    if (!h) return;
    switch (forma->tipo){
        case 'c': libera_circulo((CIRCULO*)&h); break;
        case 'r': libera_retangulo((RETANGULO*)&h); break;
        case 't': libera_texto((TEXTO*)&h); break;
        case 'l': libera_linha((LINHA*)&h); break;
    }
    
    free(forma);
    *f = NULL;
}

void escreve_forma_svg(FILE *fp, FORMA f){
    if (!fp || !f) return;

    char tipo = getTipo_forma(f);
    void *hand = getHandle_forma(f);

    switch (tipo){
        case 'c': { 
            double x = getX_circulo(hand);
            double y = getY_circulo(hand);
            double r = getR_circulo(hand);
            const char *corb = getCORB_circulo(hand);
            const char *corp = getCORP_circulo(hand);

            double opacidade = 0.6;

            fprintf(fp,
            "<circle style=\"fill:%s;fill-opacity:%.1f;stroke:%s;stroke-width:1.0\" r=\"%.2f\" cy=\"%.2f\" cx=\"%.2f\" />\n", corp, opacidade, corb, r, y, x);

            break;
        }

        case 'r': { 
            double x = getX_retangulo(hand);
            double y = getY_retangulo(hand);
            double w = getW_retangulo(hand);
            double h = getH_retangulo(hand);
            const char *corb = getCORB_retangulo(hand);
            const char *corp = getCORP_retangulo(hand);

            double opacidade = 0.6;

            if (getId_retangulo(hand) == -1){
                fprintf(fp,
            "<rect style=\"fill:%s;fill-opacity:%.1f;stroke:%s;stroke-dasharray:5;stroke-width:1.0\" x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" />\n"
            , corp, opacidade, corb, x, y, w, h);
            } else {
                fprintf(fp,
            "<rect style=\"fill:%s;fill-opacity:%.1f;stroke:%s;stroke-width:1.0\" x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" />\n"
            , corp, opacidade, corb, x, y, w, h);
            }

            break;
        }

        case 'l': {
            double x1 = getX1_linha(hand);
            double y1 = getY1_linha(hand);
            double x2 = getX2_linha(hand);
            double y2 = getY2_linha(hand);
            const char *cor = getCOR_linha(hand);

            double opacidade = 0.8;

            fprintf(fp,
            "<line style=\"stroke:%s;stroke-width:2.0;stroke-opacity:%.1f\" x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" />\n", cor, opacidade, x1, y1, x2, y2);

            break;
        }

        case 't': {
            double x = getX_texto(hand);
            double y = getY_texto(hand);
            const char *corb = getCORB_texto(hand);  
            const char *corp = getCORP_texto(hand);   
            const char *txto = getTXTO_texto(hand);   
            const char *family = getFFamily_texto(hand);
            const char *weight = getFWeight_texto(hand);
            const char a = getA_texto(hand);
            const char *ancora;
            switch (a){
                case 'i': ancora = "start"; break;
                case 'm': ancora = "middle"; break;
                case 'f': ancora = "end"; break;
            }
            int size = getFSize_texto(hand);

            double opacidade = 1.0;

            fprintf(fp,
                "<text style=\"text-anchor:%s;alignment-baseline:central;fill:%s;fill-opacity:%.1f;stroke:%s;stroke-width:0.7;"
                "font-family:%s;font-weight:%s;font-size:%dpx;line-height:0%%\" "
                "x=\"%.2f\" y=\"%.2f\">%s</text>\n", ancora, corp, opacidade, corb, family, weight, size, x, y, txto);
                
                break;
        }

        default:
            fprintf(stderr, "[escreve_forma_svg] tipo desconhecido: %c\n", tipo);
            break;
    }
}

double getLarguraX_forma(FORMA f){
    if (!f) return -1;
    void* hand = getHandle_forma(f);

    switch (getTipo_forma(f)){
        case 'c':
            return 2 * getR_circulo(hand);

        case 'r':
            return getW_retangulo(hand);

        case 'l':
            double x1 = getX1_linha(hand);
            double x2 = getX2_linha(hand);
            return x2 - x1;

        case 't':
            return strlen(getTXTO_texto(hand));
            
        default: return -1;
    }
}

FORMA clona_forma(FORMA f){
    if (!f) return NULL;
    stForma *forma = (stForma*)f;
    
    void *hand = forma->handle;
    int id_clone = -10;

    switch (forma->tipo){
        case 'c': {
            double x = getX_circulo(hand);
            double y = getY_circulo(hand);
            double r = getR_circulo(hand);
            const char *corb = getCORB_circulo(hand);
            const char *corp = getCORP_circulo(hand);

            return cria_forma('c',  cria_circulo(id_clone, x, y, r, corb, corp));
        }

        case 'r': {
            double x = getX_retangulo(hand);
            double y = getY_retangulo(hand);
            double w = getW_retangulo(hand);
            double h = getH_retangulo(hand);
            const char *corb = getCORB_retangulo(hand);
            const char *corp = getCORP_retangulo(hand);

            return cria_forma('r', cria_retangulo(id_clone, x, y, w, h, corb, corp));
        }

        case 'l': {
            double x1 = getX1_linha(hand);
            double y1 = getY1_linha(hand);
            double x2 = getX2_linha(hand);
            double y2 = getY2_linha(hand);
            const char *cor = getCOR_linha(hand);

            return cria_forma('l', cria_linha(id_clone, x1, y1, x2, y2, cor));
        }

        case 't': {
            double x = getX_texto(hand);
            double y = getY_texto(hand);
            const char *corb = getCORB_texto(hand);
            const char *corp = getCORP_texto(hand);
            char a = getA_texto(hand);
            const char *txt = getTXTO_texto(hand);

            return cria_forma('t', cria_texto(id_clone, x, y, corb, corp, a, txt));
        }

        default:
            return NULL;
    }
}

void troca_cores_forma(FORMA f){
    if (!f) return;

    setCORB_forma(f, getCORP_forma(f));
    setCORP_forma(f, getCORB_forma(f));
}

char* traduz_tipo_forma(const char tipo, bool maiusculo) {
    if (maiusculo){
        switch(tipo) {
            case 'r': return "Retângulo";
            case 'c': return "Círculo";
            case 'l': return "Linha";
            case 't': return "Texto";
            default:  return "Desconhecido";
        }
    }
    else {
        switch(tipo) {
            case 'r': return "retângulo";
            case 'c': return "círculo";
            case 'l': return "linha";
            case 't': return "texto";
            default:  return "desconhecido";
        }
    }
}

void reporta_forma(FILE* fp_txt, FORMA f, const char criterio_ordenacao){
    if (!f || !fp_txt) return;

    char t = getTipo_forma(f);
    char* tipo = traduz_tipo_forma(t, true); 

    switch (criterio_ordenacao){
        case 'd':
            fprintf(fp_txt, "== %s ==\nId: %d\nÂncora: y = %.2lf || x = %.2lf\nÁrea: %.2lf\n",
            tipo, getId_forma(f), getY_forma(f), getX_forma(f), getArea_forma(f));

            break;
        case 'a':
            fprintf(fp_txt, "== %s ==\nId: %d\nÁrea: %.2lf\n",
            tipo, getId_forma(f), getArea_forma(f));
            
            break;
        case 'w': 
            fprintf(fp_txt, "== %s ==\nId: %d\nLargura: %.2lf\n",
            tipo, getId_forma(f), getLargura_forma(f));

            break;
        case 'h':
            fprintf(fp_txt, "== %s ==\nId: %d\nAltura: %.2lf\n",
            tipo, getId_forma(f), getAltura_forma(f)); 

            break;
        case 'c': 
            if (t == 'l'){
                fprintf(fp_txt, "== Linha ==\nId: %d\nCor: %s\n",
                getId_forma(f), getCORP_forma(f));
            }
            else {
                fprintf(fp_txt, "== %s ==\nId: %d\nCor de preenchimento: %.s\n",
                tipo, getId_forma(f), getCORP_forma(f));
            }

            break;
        default:
            fprintf(fp_txt, "Critério desconhecido\n");
    }
}

void get_correcao_ancora(FORMA f, double *dx, double *dy) {
    *dx = 0;
    *dy = 0;

    switch (getTipo_forma(f)) {
        case 'c': { 
            CIRCULO c = getHandle_forma(f);
            double raio = getR_circulo(c);
            *dx = raio;
            *dy = raio; 
            break;
        }
        case 't': { 
            char ancora = getA_texto(getHandle_forma(f));
            if (ancora == 'm') *dx = getLarguraX_forma(f) / 2.0;
            else if (ancora == 'f') *dx = getLarguraX_forma(f);
            break;
        }
        case 'l': {
            LINHA l = getHandle_forma(f);
            double y1 = getY1_linha(l);
            double y2 = getY2_linha(l);
            double min_y = (y1 < y2) ? y1 : y2; 

            *dx = 0;
            *dy = y1 - min_y; 
            break;
        }
        default:
            break;
    }
}

void posiciona_formas(FORMA vet[], int n, double x_inicial, double y_teto, double dw) {
    double x_atual = x_inicial;
    double dx, dy;

    for (int i = 0; i < n; i++) {
        get_correcao_ancora(vet[i], &dx, &dy);
        
        setX_forma(vet[i], x_atual + dx);
        setY_forma(vet[i], y_teto + dy);
        
        x_atual += getLarguraX_forma(vet[i]) + dw;
    }
}

int getId_forma(FORMA f){
    stForma *forma = (stForma*)f;

    switch (forma->tipo){
        case 'c': return getId_circulo(forma->handle);
        case 'r': return getId_retangulo(forma->handle);
        case 't': return getId_texto(forma->handle);
        case 'l': return getId_linha(forma->handle); 
        default: return -100;
    }
}

char getTipo_forma(FORMA f){
    stForma* forma = (stForma*)f;

    return forma->tipo;
}

void* getHandle_forma(FORMA f){
    if (!f) return NULL;
    stForma* forma = (stForma*)f;

    return forma->handle;
}

bool getAncora_forma(FORMA f, double *x, double *y){
    if (!f || !x || !y) return false;
    stForma* forma = (stForma*)f;

    switch (forma->tipo){
        case 'c': *x = getX_circulo(forma->handle); *y = getY_circulo(forma->handle); break;
        case 'r': *x = getX_retangulo(forma->handle); *y = getY_retangulo(forma->handle); break;
        case 't': *x = getX_texto(forma->handle); *y = getY_texto(forma->handle); break;
        case 'l': *x = getX1_linha(forma->handle); *y = getY1_linha(forma->handle); break;
        default: return false;
    }

    return true;
}

double getX_forma(FORMA f){
    if (!f) return -1;
    stForma* forma = (stForma*)f;

    switch(getTipo_forma(f)){
        case 'c': 
            return getX_circulo(forma->handle);
        case 'r': 
            return getX_retangulo(forma->handle);
        case 'l': 
            return getX1_linha(forma->handle);
        case 't': 
            return getX_texto(forma->handle);
        default:
            return -1;
    }
}

double getY_forma(FORMA f){
    if (!f) return -1;
    stForma* forma = (stForma*)f;

    switch(getTipo_forma(f)){
        case 'c': 
            return getY_circulo(forma->handle);
        case 'r': 
            return getY_retangulo(forma->handle);
        case 'l': 
            return getY1_linha(forma->handle);
        case 't': 
            return getY_texto(forma->handle);
        default:
            return -1;
    }
}

double getArea_forma(FORMA f){
    if (!f) return -1;
    char tipo = getTipo_forma(f);
    void* hand = getHandle_forma(f);

    switch (tipo){
        case 'c': return getArea_circulo(hand);
        case 'r': return getArea_retangulo(hand);
        case 't': return getArea_texto(hand);
        case 'l': return getArea_linha(hand);
        default: return -2;
    }
}

double getLargura_forma(FORMA f){
    if (!f) return -1;
    char tipo = getTipo_forma(f);
    void* hand = getHandle_forma(f);

    switch (tipo){
        case 'c': return 2 * getR_circulo(hand);
        case 'r': return getW_retangulo(hand);
        case 't': return strlen(getTXTO_texto(hand));
        case 'l': return getComprimento_linha(hand);
        default : return -2;
    }
}

double getAltura_forma(FORMA f){
    if (!f) return -1;
    char tipo = getTipo_forma(f);
    void* hand = getHandle_forma(f);

    switch (tipo){
        case 'c': return 2 * getR_circulo(hand);
        case 'r': return getH_retangulo(hand);
        case 't': return 10.0;
        case 'l': return 1.5;
        default : return -2;
    }
}

char* getCORB_forma(FORMA f){
    if (!f) return NULL;
    char tipo = getTipo_forma(f);
    void* hand = getHandle_forma(f);

    switch (tipo){
        case 'c': return getCORB_circulo(hand);
        case 'r': return getCORB_retangulo(hand);
        case 't': return getCORB_texto(hand);
        case 'l': return getCOR_linha(hand);
        default : return NULL;
    }
}

char* getCORP_forma(FORMA f){
    if (!f) return NULL;
    char tipo = getTipo_forma(f);
    void* hand = getHandle_forma(f);

    switch (tipo){
        case 'c': return getCORP_circulo(hand);
        case 'r': return getCORP_retangulo(hand);
        case 't': return getCORP_texto(hand);
        case 'l': return getCOR_linha(hand);
        default : return NULL;
    }
}

bool setAncora_forma(FORMA f, double x, double y){
    if (!f) return false;

    stForma* forma = (stForma*)f;

    switch (forma->tipo){
        case 'c': return setX_circulo(forma->handle, x) && setY_circulo(forma->handle, y);
        case 'r': return setX_retangulo(forma->handle, x) && setY_retangulo(forma->handle, y);
        case 't': return setX_texto(forma->handle, x) && setY_texto(forma->handle, y);
        case 'l': return setAncora_linha(forma->handle, x, y);
        
        default: return false;
    }
}

void setX_forma(FORMA f, double x){
    if (!f) return;

    stForma* forma = (stForma*)f;
    void* hand = getHandle_forma(f);
    switch (forma->tipo){
        case 'c': setX_circulo(hand, x);
        case 'r': setX_retangulo(hand, x);
        case 't': setX_texto(hand, x);
        case 'l': setAncora_linha(hand, x, getY1_linha(hand));
        
        default: return;
    }
}

void setY_forma(FORMA f, double y){
    if (!f) return;

    stForma* forma = (stForma*)f;
    void* hand = getHandle_forma(f);
    switch (forma->tipo){
        case 'c': setY_circulo(hand, y);
        case 'r': setY_retangulo(hand, y);
        case 't': setY_texto(hand, y);
        case 'l': setAncora_linha(hand, getX1_linha(hand), y);
        
        default: return;
    }
}

void setCORB_forma(FORMA f, char* corb){
    if (!f || !corb) return;

    FORMA figura = getHandle_forma(f);
    switch (getTipo_forma(f)){
        case 'c': {
            setCORB_circulo(figura, corb);
            break;
        }
        case 'r': {
            setCORB_retangulo(figura, corb);
            break;
        }
        case 't': {
            setCORB_texto(figura, corb);
            break;
        }
        case 'l': {
            setCOR_linha(figura, corb);
            break;
        }
    }
    return;
}

void setCORP_forma(FORMA f, char* corp){
    if (!f || !corp) return;

    FORMA figura = getHandle_forma(f);
    switch (getTipo_forma(f)){
        case 'c': {
            setCORP_circulo(figura, corp);
            break;
        }
        case 'r': {
            setCORP_retangulo(figura, corp);
            break;
        }
        case 't': {
            setCORP_texto(figura, corp);
            break;
        }
        default:
            break;
    }
    return;
}

bool desloca_forma(FORMA f, double dx, double dy){
    if (!f) return false;

    double x, y;

    if (!getAncora_forma(f, &x, &y)) return false;

    return setAncora_forma(f, x + dx, y + dy);
}