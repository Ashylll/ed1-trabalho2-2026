#ifndef LEITURA_GEO
#define LEITURA_GEO

#include <stdbool.h>
#include <stdio.h>

/*
leitura.h
    Módulo responsável pela leitura do arquivo de entrada .geo e pela criação e
   inserção das formas lidas na árvore .geo: contém informações das formas

*/

typedef void *Arvore;

/// @brief realiza a leitura do arquivo .geo, cria as figuras iniciais e as
/// insere na árvore de formas
/// @param path_geo caminho do arquivo .geo
/// @param a árvore
/// @return true se a operação foi bem-sucedida; false se não
bool leitura_geo(const char *path_geo, Arvore a);

#endif