#include <stdio.h>
#include <string.h>
#include "svg.h"
#include "arvore.h"
#include "forma.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

void svg_begin(FILE *fp){
    if (!fp) return;

    fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(fp,
        "<svg xmlns:svg=\"http://www.w3.org/2000/svg\" "
        "xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n"
    );
}

void svg_end(FILE *fp){
    if (!fp) return;
    
    fprintf(fp, "</svg>\n");
}

void gera_svg_inicial(const char* path_geo_svg, ARVORE formas){
    FILE* fp_svg = fopen(path_geo_svg, "w");

    svg_begin(fp_svg);
    escreve_arvore_svg(fp_svg, formas);
    svg_end(fp_svg);

    fclose(fp_svg);
}

void gera_svg_final(const char* path_comb_svg, ARVORE formas, ARVORE formas_marcadores){
    FILE* fp_svg = fopen(path_comb_svg, "w");

    svg_begin(fp_svg);
    escreve_arvore_svg(fp_svg, formas);
    escreve_arvore_svg(fp_svg, formas_marcadores);
    svg_end(fp_svg);

    fclose(fp_svg);
}

void escreve_forma_deslocada_svg(FILE *fp_svg, FORMA f, double x, double y){
    if (!fp_svg || !f) return;

    char tipo = getTipo_forma(f);
    void *hand = getHandle_forma(f);

    switch (tipo){
        case 'c': { 
            double y = getY_circulo(hand);
            double r = getR_circulo(hand);
            const char *corb = getCORB_circulo(hand);
            const char *corp = getCORP_circulo(hand);

            double opacidade = 0.6;

            fprintf(fp_svg,
            "<circle style=\"fill:%s;fill-opacity:%.1f;stroke:%s;stroke-width:1.0\" r=\"%.2f\" cy=\"%.2f\" cx=\"%.2f\" />\n", corp, opacidade, corb, r, y, x);

            break;
        }

        case 'r': { 
            double y = getY_retangulo(hand);
            double w = getW_retangulo(hand);
            double h = getH_retangulo(hand);
            const char *corb = getCORB_retangulo(hand);
            const char *corp = getCORP_retangulo(hand);

            double opacidade = 0.6;

            if (getId_retangulo(hand) == -1){
                fprintf(fp_svg,
            "<rect style=\"fill:%s;fill-opacity:%.1f;stroke:%s;stroke-dasharray:5;stroke-width:1.0\" x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" />\n"
            , corp, opacidade, corb, x, y, w, h);
            } else {
                fprintf(fp_svg,
            "<rect style=\"fill:%s;fill-opacity:%.1f;stroke:%s;stroke-width:1.0\" x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" />\n"
            , corp, opacidade, corb, x, y, w, h);
            }

            break;
        }

        case 'l': {
            double y1 = getY1_linha(hand);
            double y2 = getY2_linha(hand);
            double dy = y;
            dy += (y1 > y2)? y1 - y2: y2 - y1;
            
            double x1 = getX1_linha(hand);
            double x2 = getX2_linha(hand);
            double dx = x;
            dx = x2 - x1;
            
            const char *cor = getCOR_linha(hand);

            double opacidade = 0.8;
 
            fprintf(fp_svg,
            "<line style=\"stroke:%s;stroke-width:2.0;stroke-opacity:%.1f\" x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" />\n", cor, opacidade, x, y1, dx, dy);

            break;
        }

        case 't': {
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

            fprintf(fp_svg,
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

static void remove_extensao(const char *path, char *dest) {
    strcpy(dest, path);
    
    char *barra = strrchr(dest, '/'); 
    char *ponto = strrchr(dest, '.'); 
    
    if (ponto && (!barra || ponto > barra)) {
        *ponto = '\0';
    }
}

static FILE* cria_file_frame(int numeracao_frame,   const char* comb_out){
    char nome_svg[280];
    char base_comb_svg[256];

    remove_extensao(comb_out, base_comb_svg);
    snprintf(nome_svg, sizeof(nome_svg), "%s%06d.svg", base_comb_svg, numeracao_frame);    
    
    FILE* fp = fopen(nome_svg, "w");
    return fp;
}

void escreve_frame(const char* comb_out, int numeracao, double x, double y, double dw, FORMA vet_selecionadas[], double n_selecionadas){
    double dx = 0;
    FILE* fp_svg = cria_file_frame(numeracao, comb_out);

    for (int i = 0; i < n_selecionadas; i++){
        FORMA f = vet_selecionadas[i];
        double l = getLarguraX_forma(f);
        
        get_correcao_ancora(f, &x, &y);
        escreve_forma_deslocada_svg(fp_svg, f, x + dx, y);

        dx += l + dw;
    }
}