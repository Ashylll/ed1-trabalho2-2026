#ifndef SVG_H
#define SVG_H
#endif 

#include <stdbool.h>

/*
    svg.h
    Módulo responsável pela escrita em arquivos .svg

    Escreve as figuras iniciais (.geo) e finais (após .qry, caso haja) do programa nos arquivos do sistema

*/

/// @brief escreve o cabeçalho do .svg
/// @param fp arquivo .svg aberto em modo escrita
/// @pre fp != NULL
void svg_begin(FILE *fp);

/// @brief escreve o rodapé do .svg
/// @param fp arquivo .svg aberto em modo escrita
/// @pre fp != NULL
void svg_end(FILE *fp);
