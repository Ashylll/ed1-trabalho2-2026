#ifndef CIRCULO_H
#define CIRCULO_H

#include <stdbool.h>

/*
    circulo.h
    Módulo responsável pela implementação do círculo e operações relacionadas

    -   O círculo é formado por um ponto central no plano cartesiano e um raio
   que determina o limite da função (borda);
    -   Possui identificador de número inteiro;
    -   Possui coloração para a borda e o seu preenchimento (dentro dos limites
   do círculo) de acordo com o padrão SVG.

    Convenções:
    -   Sistema de coordenadas no domínio dos números reais com (0,0) no canto
   superior esquerdo;
    -   x cresce para a direita; y cresce para baixo;
    -   A âncora do círculo é seu centro.

*/

#define PI 3.141592653589793
typedef void *Circulo;

/// @brief cria um círculo com identificador, cor de borda e de preenchimento e
/// coordenadas
/// @param id identificador numérico do círculo
/// @param x coordenada x da âncora
/// @param y coordenada y da âncora
/// @param r raio
/// @param corb cor da borda (string)
/// @param corp cor de preenchimento (string)
/// @pre corb != NULL && corp != NULL && r > 0
/// @return ponteiro para o círculo; NULL se parâmetros inválidos ou falha de
/// memória
Circulo cria_circulo(int id, double x, double y, double r, const char *corb,
                     const char *corp);

/// @brief retorna a área do círculo
/// @param c círculo
/// @pre c != NULL
/// @return área
double get_area_circulo(Circulo c);

/// @brief libera a memória do círculo
/// @pre c != NULL
/// @param c ponteiro para o handle do círculo
void libera_circulo(Circulo *c);

/* Funções get */

/// @brief retorna o identificador do círculo
/// @param c círculo
/// @pre c != NULL
/// @return identificador
int get_id_circulo(Circulo c);

/// @brief retorna a coordenada x da âncora do círculo
/// @param c círculo
/// @pre c != NULL
/// @return coordenada x
double get_x_circulo(Circulo c);

/// @brief retorna a coordenada y da âncora do círculo
/// @param c círculo
/// @pre c != NULL
/// @return coordenada y
double get_y_circulo(Circulo c);

/// @brief retorna o raio do círculo
/// @param c círculo
/// @pre c != NULL
/// @return raio
double get_raio_circulo(Circulo c);

/// @brief retorna a cor da borda do círculo
/// @param c círculo
/// @pre c != NULL
/// @return ponteiro para string com a cor da borda (apenas leitura)
char *get_corb_circulo(Circulo c);

/// @brief retorna a cor de preenchimento do círculo
/// @param c círculo
/// @pre c != NULL
/// @return ponteiro para string com a cor de preenchimento (apenas leitura)
char *get_corp_circulo(Circulo c);

/* Funções set */

/// @brief atribui um identificador ao círculo
/// @param c círculo
/// @param id identificador
/// @pre c != NULL
/// @return true se a operação foi bem sucedida; false se c == NULL
bool set_id_circulo(Circulo c, int id);

/// @brief atribui uma coordenada x ao círculo
/// @param c círculo
/// @param x coordenada x
/// @pre c != NULL
/// @return true se a operação foi bem sucedida; false se c == NULL
bool set_x_circulo(Circulo c, double x);

/// @brief atribui uma coordenada y ao círculo
/// @param c círculo
/// @param y coordenada y
/// @pre c != NULL
/// @return true se a operação foi bem sucedida; false se c == NULL
bool set_y_circulo(Circulo c, double y);

/// @brief atribui um raio ao círculo
/// @param c círculo
/// @param r raio
/// @pre c != NULL && r > 0
/// @return true se a operação foi bem sucedida; false se c == NULL || r <= 0
bool set_raio_circulo(Circulo c, double r);

/// @brief atribui uma cor de borda ao círculo
/// @param c círculo
/// @param corb cor de borda
/// @pre c != NULL && corb != NULL
/// @return true se a operação foi bem sucedida; false se c == NULL || corb ==
/// NULL
bool set_corb_circulo(Circulo c, const char *corb);

/// @brief atribui uma cor de preenchimento ao círculo
/// @param c círculo
/// @param corp cor de preenchimento
/// @pre c != NULL && corp != NULL
/// @return true se a operação foi bem sucedida; false se c == NULL || corp ==
/// NULL
bool set_corp_circulo(Circulo c, const char *corp);

/* =========== */

#endif
