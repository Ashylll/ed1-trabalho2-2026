#include <stdio.h>
#include "svg.h"
#include "arvore.h"

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