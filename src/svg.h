#ifndef SVG_H
#define SVG_H

#include <stdbool.h>
#include <stdio.h>

/*
    svg.h
    Módulo responsável pela escrita em arquivos .svg

*/
typedef void *Arvore, *Forma;

/// @brief escreve o cabeçalho do .svg
/// @param fp arquivo .svg aberto em modo escrita
/// @pre fp != NULL
void svg_begin(FILE *fp);

/// @brief escreve o rodapé do .svg
/// @param fp arquivo .svg aberto em modo escrita
/// @pre fp != NULL
void svg_end(FILE *fp);

/// @brief gera SVG das formas contidas na árvore
/// @param path_geo_svg caminho do SVG inicial
/// @param formas árvore de formas
/// @pre path_geo_svg != NULL && formas != NULL
void gera_svg_inicial(const char *path_geo_svg, Arvore formas);

/// @brief gera SVG das formas contidas nas árvores principal e de marcadores
/// @param path_comb_svg caminho combinado do .geo e .qry
/// @param formas árvore de formas principais
/// @param formas_marcadores árvore de marcadores 
/// @pre path_comb_svg != NULL && formas != NULL && formas_marcadores
void gera_svg_final(const char *path_comb_svg, Arvore formas,
                    Arvore formas_marcadores);

/// @brief escreve em um SVG uma forma na posição x e y
/// @param fp_svg arquivo SVG
/// @param f forma
/// @param x coordenada x
/// @param y coordenada y
void escreve_forma_deslocada_svg(FILE *fp_svg, Forma f, double x, double y);

/// @brief gera um SVG das formas contidas no vetor a partir do ponto p = (x,y) 
/// @param comb_out nome combinado do .geo e .qry
/// @param numeracao numeração do frame
/// @param x coordenada x inicial 
/// @param y coordenada y inicial 
/// @param dw espaçamento das formas
/// @param vet_selecionads vetor de formas
/// @param n_selecionadas tamanho do vetor
/// @pre numeração deve pertencer ao intervalo [0, 999999]
void escreve_frame(const char *comb_out, int numeracao, double x, double y,
                   double dw, Forma vet_selecionads[], double n_selecionadas);

#endif