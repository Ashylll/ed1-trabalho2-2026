#ifndef LINHA_H
#define LINHA_H

#include <stdbool.h>

/*
    linha.h
    Módulo responsável pela implementação da linha e operações relaciondas

    -   A linha é formada por dois pontos no plano cartesiano, sendo traçado um
   segmento de reta;
    -   Possui identificador de número inteiro;
    -   O segmento gerado possui coloração de acordo com o padrão SVG.

    Convenções:
    -   Sistema de coordenadas no domínio dos número reais com (0,0) no canto
   superior esquerdo;
    -   x cresce para a direita; y cresce para baixo;
    -   A linha possui duas âncoras (nas extremidades), sendo elas o pares
   (x1,y1) e (x2,y2).
    -   (x1,y1) é a âncora de menor x. Em caso de empate, (x1,y1) é a âncora de
   menor y.

*/

typedef void *Linha;

/// @brief cria uma linha com identificador e cor
/// @param id identificador 'i'
/// @param x1 coordenada x da extremidade 1 (x1)
/// @param y1 coordenada y da extremidade 1 (y1)
/// @param x2 coordenada x da extremidade 2 (x2)
/// @param y2 coordenada y da extremidade 2 (y2)
/// @param cor cor da linha
/// @pre cor != NULL && [(x1 == y1 && x1 == x2 && x1 == y2) != 1]
/// @return retorna ponteiro para a linha
Linha cria_linha(int id, double x1, double y1, double x2, double y2,
                 const char *cor);

/// @brief calcula o comprimento da linha
/// @param l linha
/// @pre l != NULL
/// @return comprimento da linha; -1 se l == NULL
double get_comprimento_linha(Linha l);

/// @brief libera a memória da linha
/// @pre l != NULL
/// @param l ponteiro para o handle da linha
void libera_linha(Linha *l);

/* === Operações get === */

/// @brief retorna o identificador da linha
/// @param l linha
/// @pre l != NULL
/// @return identificador
int get_id_linha(Linha l);

/// @brief retorna a coordenada x1 da linha
/// @param l linha
/// @pre l != NULL
/// @return coordenada x1
double get_x1_linha(Linha l);

/// @brief retorna a coordenada y1 da linha
/// @param l linha
/// @pre l != NULL
/// @return coordenada y1
double get_y1_linha(Linha l);

/// @brief retorna a coordenada x2 da linha
/// @param l linha
/// @pre l != NULL
/// @return coordenada x2
double get_x2_linha(Linha l);

/// @brief retorna a coordenada y2 da linha
/// @param l linha
/// @pre l != NULL
/// @return coordenada y2
double get_y2_linha(Linha l);

/// @brief retorna a cor da linha
/// @param l linha
/// @pre l != NULL
/// @return ponteiro para string com a cor da linha (apenas leitura)
char *get_cor_linha(Linha l);

/// @brief retorna a área da linha
/// @param l linha
/// @pre l != NULL
/// @return área
double get_area_linha(Linha l);

/* ===================== */

/* === Operações set === */

/// @brief atribui um identificador à linha
/// @param l linha
/// @param id identificador
/// @pre l != NULL
/// @return true se a operação foi bem sucedida; false se não
bool set_id_linha(Linha l, int id);

/// @brief atribui uma coordenada x1 à linha
/// @param l linha
/// @param x1 coordenada x1
/// @pre l != NULL
/// @return true se a operação foi bem sucedida; false se não
bool set_x1_linha(Linha l, double x1);

/// @brief atribui ua coordenada y1 à linha
/// @param l linha
/// @param y1 coordenada y1
/// @pre l != NULL
/// @return true se a operação foi bem sucedida; false se não
bool set_y1_linha(Linha l, double y1);

/// @brief atribui uma coordenada x2 à linha
/// @param l linha
/// @param x2 coordenada x2
/// @pre l != NULL
/// @return true se a operação foi bem sucedida; false se não
bool set_x2_linha(Linha l, double x2);

/// @brief atribui uma coordenada y2 à linha
/// @param l linha
/// @param y2 coordenada y2
/// @pre l != NULL
/// @return true se a operação foi bem sucedida; false se não
bool set_y2_linha(Linha l, double y2);

/// @brief atribui uma coordenada (x,y) à âncora da linha e o segundo ponto
/// acompanha o mesmo deslocamento (+dx, +dy)
/// @param l linha
/// @param x coordenada x da âncora
/// @param y coordenada y da âncora
/// @return true se a operação foi bem sucedidaç false se não
bool set_ancora_linha(Linha l, double x, double y);

/// @brief atribui uma cor à linha
/// @param l linha
/// @param cor cor
/// @pre l != NULL && cor != NULL
/// @return true se a operação foi bem sucedida; false se não
bool set_cor(Linha l, const char *cor);

/* ===================== */

#endif
