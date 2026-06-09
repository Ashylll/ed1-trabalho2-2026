#ifndef SVG_H
#define SVG_H
#endif 

#include <stdbool.h>

/*
    svg.h
    Módulo responsável pela escrita em arquivos .svg

    Escreve as figuras iniciais (.geo) e finais (após .qry, caso haja) do programa nos arquivos do sistema

*/
typedef void *ARVORE, *FORMA;

/// @brief escreve o cabeçalho do .svg
/// @param fp arquivo .svg aberto em modo escrita
/// @pre fp != NULL
void svg_begin(FILE *fp);

/// @brief escreve o rodapé do .svg
/// @param fp arquivo .svg aberto em modo escrita
/// @pre fp != NULL
void svg_end(FILE *fp);

void gera_svg_inicial(const char* path_geo_svg, ARVORE formas);

void gera_svg_final(const char* path_comb_svg, ARVORE formas, ARVORE formas_marcadores);

void escreve_forma_deslocada_svg(FILE* fp_svg, FORMA f, double x, double y);
void posiciona_formas(FORMA vet[], int n, double x, double y_teto, double dw);
void escreve_frame(const char* comb_out, int numeracao, double x, double y, double dw, FORMA vet_selecionads[], double n_selecionadas);