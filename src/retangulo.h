#ifndef RETANGULO_H
#define RETANGULO_H

#include <stdbool.h>

/*
    retangulo.h
    Módulo responsável pela implementação do retângulo e operações relacionadas
    
    -   O retângulo é um conjunto de quatro pontos no plano cartesiano, dos quais é possível traçar dois pares de segmentos paralelos,
        formando a figura geométrica;
    -   Possui identificador de número inteiro;
    -   Possui coloração para a borda (segmentos) e o seu preenchimento (dentro dos limites do retângulo) de acordo com o padrão SVG.

    Convenções:
   -    Sistema de coordenadas no domínio dos números reais com (0,0) no canto superior esquerdo;
   -    x cresce para a direita; y cresce para baixo;
   -    A âncora do retângulo é o ponto no canto superior esquerdo.

*/

typedef void* RETANGULO;

/// @brief cria um retângulo com identificador, cor de borda e de preenchimento e coordenadas âncora
/// @param id identificador numérico do retângulo
/// @param x coordenada x da âncora 
/// @param y coordenada y da âncora 
/// @param w largura > 0
/// @param h altura > 0
/// @param corb cor da borda (string)
/// @param corp cor de preenchimento (string)
/// @pre corb != NULL && corp != NULL && w > 0 && h > 0
/// @return ponteiro para o retângulo; NULL se parâmetros inválidos ou falha de memória
RETANGULO cria_retangulo(int id, double x, double y, double w, double h, const char* corb, const char* corp);

/// @brief retorna a área do retângulo    
/// @param r retângulo
/// @pre r != NULL
/// @return área
double area_retangulo(RETANGULO r);

/// @brief libera a memória do retângulo
/// @param r ponteiro para handle do retângulo
/// @pre r != NULL
void libera_retangulo(RETANGULO *r);

/* === Operações get === */

/// @brief retorna o identificador do retângulo
/// @param r retângulo
/// @pre r != NULL
/// @return identificador
int getId_retangulo(RETANGULO r);

/// @brief retorna a coordenada x da âncora do retângulo 
/// @param r retângulo  
/// @pre r != NULL
/// @return coordenada x 
double getX_retangulo(RETANGULO r);

/// @brief retorna a coordenada y da âncora do retângulo
/// @param r retângulo   
/// @pre r != NULL
/// @return coordenada y 
double getY_retangulo(RETANGULO r);

/// @brief retorna a largura do retângulo
/// @param r retângulo
/// @pre r != NULL
/// @return largura
double getW_retangulo(RETANGULO r);

/// @brief retorna a altura do retângulo
/// @param r retângulo
/// @pre r != NULL
/// @return altura
double getH_retangulo(RETANGULO r);

/// @brief retorna a cor da borda do retângulo
/// @param r retângulo
/// @pre r != NULL
/// @return ponteiro para string com a cor da borda (apenas leitura)
char* getCORB_retangulo(RETANGULO r);

/// @brief retorna a cor de preenchimento do retângulo
/// @param r retângulo
/// @pre r != NULL
/// @return ponteiro para string com a cor de preenchimento (apenas leitura)
char* getCORP_retangulo(RETANGULO r);

/* ===================== */


/* === Operações set === */

/// @brief atribui um identificador ao retângulo
/// @param r retângulo
/// @param id identificador 
/// @pre r != NULL
/// @return true se a operação foi bem sucedida; false se r == NULL
bool setId_retangulo(RETANGULO r, int id);

/// @brief atribui uma coordenada x à âncora do retângulo
/// @param r retângulo
/// @param x coordenada x
/// @pre r != NULL
/// @return true se a operação foi bem sucedida; false se r == NULL
bool setX_retangulo(RETANGULO r, double x);

/// @brief atribui uma coordenada y à âncora do retângulo
/// @param r retângulo
/// @param y coordenada y
/// @pre r != NULL
/// @return true se a operação foi bem sucedida; false se r == NULL
bool setY_retangulo(RETANGULO r, double y);

/// @brief atribui uma largura ao retângulo
/// @param r retângulo
/// @param w largura > 0
/// @pre r != NULL && w > 0
/// @return true se a operação foi bem sucedida; false se r == NULL || w <= 0
bool setW_retangulo(RETANGULO r, double w);

/// @brief atribui uma altura ao retângulo
/// @param r retângulo
/// @param h altura > 0
/// @pre r != NULL && h > 0
/// @return true se a operação foi bem sucedida; false se r == NULL || h <= 0
bool setH_retangulo(RETANGULO r, double h);

/// @brief atribui uma cor de borda ao retângulo
/// @param r retângulo
/// @param corb cor de borda 
/// @pre r != NULL && corb != NULL
/// @return true se a operação foi bem sucedida; false se r == NULL || corb == NULL
bool setCORB_retangulo(RETANGULO r, const char* corb);

/// @brief atribui uma cor de preenchimento ao retângulo
/// @param r retângulo
/// @param corp cor de preenchimento
/// @pre r != NULL && corp != NULL
/// @return true se a operação foi bem sucedida; false se r == NULL || corp == NULL
bool setCORP_retangulo(RETANGULO r, const char* corp);

/* ===================== */

#endif