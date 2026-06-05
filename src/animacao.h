#ifndef ANIMACAO_H
#define ANIMACAO_H
#endif

#include <stdio.h>

/*
    animacao.h

*/

/// @brief gera arquivos SVGs sequencias e log em TXT
/// @param fp_qry arquivo QRY de entrada aberto em modo de leitura
/// @param out_txt caminho pra o TXT de saída
/// @param out_svg caminho para o primeiro SVG de saída
/// @pre nenhum dos parâmetros de entrada devem ser NULL
void gera_animacao(FILE *fp_qry, const char* out_txt, const char* out_svg);