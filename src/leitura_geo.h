#ifndef LEITURA_GEO
#define LEITURA_GEO 
#endif

#include <stdbool.h>
#include <stdio.h>

/*
    leitura.h
    Módulo responsável pela leitura do arquivo de entrada .geo e pela consequente inserção das formas criadas na árvore
    .geo: contém informações das formas

*/

typedef void* ARVORE;

/// @brief realiza a leitura do arquivo .geo, cria as figuras iniciais e as insere na árvore de formas
/// @param fp_geo arquivo .geo aberto em modo de leitura
/// @param a árvore
/// @return true se a operação foi bem-sucedida; false se não
bool leitura_geo(FILE* fp_geo, ARVORE a);