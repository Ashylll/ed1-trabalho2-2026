#ifndef PROCESSA_QRY
#define PROCESSA_QRY
#endif

#include <stdbool.h>
#include <stdio.h>

/*
    processa_qry.h
    Módulo responsável pela leitura e pelo processamento do arquivo de entrada .qry
    Gera uma "animação" dos algoritmos de ordenação criando arquivos .svg numerados em sequência e escrevendo no log
    O estado final das formas do programa é armazenado nas ávores
*/

typedef void* Arvore;

/// @brief realiza a leitura e o processamento dos comandos no arquivo .qry, gerando animação (arquivos .svg) e escrita no arquivo log
/// @param path_qry caminho do arquivo de entrada .qry
/// @param path_log caminho do arquivo de log .txt
/// @param comb_out nome combinado dos arquivos de entrada .geo e .qry
/// @param formas árvore de formas lidas do .geo
/// @param formas_marcadores árvore auxiliar para receber marcadores (quadrado e retângulo de seleção criados por comandos)
/// @pre nenhum dos parâmetros deve ser NULL
/// @return true se a operação foi bem-sucedida; false se não
bool processa_qry(const char* path_qry, const char* path_log, const char* comb_out, Arvore formas, Arvore formas_marcadores);