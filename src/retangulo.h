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

typedef void* Retangulo;

#define ID_RETANGULO_SEL -1
#define CORB_RETANGULO_SEL "red"
#define CORP_RETANGULO_SEL "none"
#define ID_QUADRADO_MARCA -2
#define LADO_QUADRADO_MARCA 5.0
#define CORB_QUADRADO_MARCA "red"
#define CORP_QUADRADO_MARCA "none"

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
Retangulo cria_retangulo(int id, double x, double y, double w, double h, const char* corb, const char* corp);

/// @brief retorna a área do retângulo    
/// @param r retângulo
/// @pre r != NULL
/// @return área
double get_area_retangulo(Retangulo r);

/// @brief libera a memória do retângulo
/// @param r ponteiro para handle do retângulo
/// @pre r != NULL
void libera_retangulo(Retangulo *r);

/* === Operações get === */

/// @brief retorna o identificador do retângulo
/// @param r retângulo
/// @pre r != NULL
/// @return identificador
int get_id_retangulo(Retangulo r);

/// @brief retorna a coordenada x da âncora do retângulo 
/// @param r retângulo  
/// @pre r != NULL
/// @return coordenada x 
double get_x_retangulo(Retangulo r);

/// @brief retorna a coordenada y da âncora do retângulo
/// @param r retângulo   
/// @pre r != NULL
/// @return coordenada y 
double get_y_retangulo(Retangulo r);

/// @brief retorna a largura do retângulo
/// @param r retângulo
/// @pre r != NULL
/// @return largura
double get_w_retangulo(Retangulo r);

/// @brief retorna a altura do retângulo
/// @param r retângulo
/// @pre r != NULL
/// @return altura
double get_h_retangulo(Retangulo r);

/// @brief retorna a cor da borda do retângulo
/// @param r retângulo
/// @pre r != NULL
/// @return ponteiro para string com a cor da borda (apenas leitura)
char* get_corb_retangulo(Retangulo r);

/// @brief retorna a cor de preenchimento do retângulo
/// @param r retângulo
/// @pre r != NULL
/// @return ponteiro para string com a cor de preenchimento (apenas leitura)
char* get_corp_retangulo(Retangulo r);

/* ===================== */


/* === Operações set === */

/// @brief atribui um identificador ao retângulo
/// @param r retângulo
/// @param id identificador 
/// @pre r != NULL
/// @return true se a operação foi bem sucedida; false se r == NULL
bool set_id_retangulo(Retangulo r, int id);

/// @brief atribui uma coordenada x à âncora do retângulo
/// @param r retângulo
/// @param x coordenada x
/// @pre r != NULL
/// @return true se a operação foi bem sucedida; false se r == NULL
bool set_x_retangulo(Retangulo r, double x);

/// @brief atribui uma coordenada y à âncora do retângulo
/// @param r retângulo
/// @param y coordenada y
/// @pre r != NULL
/// @return true se a operação foi bem sucedida; false se r == NULL
bool set_y_retangulo(Retangulo r, double y);

/// @brief atribui uma largura ao retângulo
/// @param r retângulo
/// @param w largura > 0
/// @pre r != NULL && w > 0
/// @return true se a operação foi bem sucedida; false se r == NULL || w <= 0
bool set_w_retangulo(Retangulo r, double w);

/// @brief atribui uma altura ao retângulo
/// @param r retângulo
/// @param h altura > 0
/// @pre r != NULL && h > 0
/// @return true se a operação foi bem sucedida; false se r == NULL || h <= 0
bool set_h_retangulo(Retangulo r, double h);

/// @brief atribui uma cor de borda ao retângulo
/// @param r retângulo
/// @param corb cor de borda 
/// @pre r != NULL && corb != NULL
/// @return true se a operação foi bem sucedida; false se r == NULL || corb == NULL
bool set_corb_retangulo(Retangulo r, const char* corb);

/// @brief atribui uma cor de preenchimento ao retângulo
/// @param r retângulo
/// @param corp cor de preenchimento
/// @pre r != NULL && corp != NULL
/// @return true se a operação foi bem sucedida; false se r == NULL || corp == NULL
bool set_corp_retangulo(Retangulo r, const char* corp);

/* ===================== */

#endif