#ifndef FORMA_H
#define FORMA_H
#endif

#include <stdbool.h>
#include <stdio.h>

/*
    forma.h
    Forma é um contâiner (wrapper) que carrega um ponteiro para uma figura e o seu tipo.

*/

typedef void* FORMA;

/// @brief cria uma forma
/// @param tipo tipo da forma (círculo, retângulo, texto, linha)
/// @param handle handle para a forma (ponteiro para a forma)
/// @return ponteiro para a forma
FORMA cria_forma(char tipo, void* handle);

/// @brief libera a forma
/// @param f ponteiro para handle FORMA
void libera_forma(FORMA *f);

/// @brief escreve a forma em um arquivo SVG aberto em modo escrita
/// @param fp arquivo SVG
/// @param f forma
/// @pre fp != NULL && f != NULL
void escreve_forma_svg(FILE *fp, FORMA f);

/// @brief troca a posição espacial de duas formas na coordenada x
/// @param f1 forma 1
/// @param f2 forma 2
/// @param distancia menor distância entre as formas
/// @pre f1 != NULL && f2 != NULL && distancia >= 0
void troca_posicaoX_formas(FORMA f1, FORMA f2, double distancia);

/// @brief clona a forma (copia valores) com id específico para clone
/// @param f forma original
/// @pre f != NULL
/// @return clone criado
FORMA clona_forma(FORMA f);

/// @brief troca as cores de borda e de preenchimento da forma
/// @pre f != NULL
/// @param f forma
void troca_cores(FORMA f);

/* === Operações get === */

/// @brief retorna o identificador da forma
/// @param f forma
/// @pre f != NULL
/// @return identificador
int getId_forma(FORMA f);

/// @brief retorna o tipo da forma
/// @param f forma
/// @pre f != NULL
/// @return caractere para o tipo ('c', 'r', 't', 'l')
char getTipo_forma(FORMA f);

/// @brief retorna o handle da forma
/// @param f forma
/// @return handle
void* getHandle_forma(FORMA f);

/// @brief lê as coordenadas (x,y) da âncora da forma
/// @param f forma
/// @param x ponteiro para saída da coordenada x
/// @param y ponteiro para saída da coordenada y
/// @return true se a operação foi bem sucedida; false se f == NULL
bool getAncora_forma(FORMA f, double* x, double* y);

/// @brief retorna a coordenada x da âncora da forma
/// @param f forma
/// @pre f != NULL
/// @return coordenada x
double getX_forma(FORMA f);

/// @brief retorna a coordenada y da âncora da forma
/// @param f forma
/// @pre f != NULL
/// @return coordenada y
double getY_forma(FORMA f);

/// @brief retorna a área da forma
/// @param f forma
/// @pre f != NULL
/// @return área
double getArea_forma(FORMA f);

/// @brief retorna a largura da forma
/// @param f forma
/// @pre f != NULL
/// @return largura
double getLargura_forma(FORMA f);

/// @brief retorna a altura da forma
/// @param f forma
/// @pre f != NULL
/// @return altura
double getAltura_forma(FORMA f);

/// @brief retorna a cor de borda da forma
/// @param f forma
/// @pre f != NULL
/// @return cor de borda
char* getCORB_forma(FORMA f);

/// @brief retorna a cor de preenchimento da forma
/// @param f forma
/// @pre f != NULL
/// @return cor de preenchimento
char* getCORP_forma(FORMA f);

/* ===================== */


/* === Operações set === */


/// @brief atribui coordenadas (x,y) da forma
/// @param f forma
/// @param x coordenada x
/// @param y coordenada y
/// @return true se a operação foi bem sucedida; false se f == NULL
bool setAncora_forma(FORMA f, double x, double y);

/// @brief seta um valor à coordenada x da âncora da forma
/// @param f forma
/// @pre f != NULL
/// @param x coordenada x
void setX_forma(FORMA f, double x);

/// @brief seta um valor à coordenada y da âncora da forma
/// @param f forma
/// @pre f != NULL
/// @param x coordenada y
void setY_forma(FORMA f, double y);

/// @brief atribui uma cor de borda à forma (atribui cor se for tipo linha)
/// @param f forma
/// @param corb cor de borda
/// @pre f != NULL && corp != NULL
void setCORB_forma(FORMA f, char* corb);

/// @brief atribui uma cor de preenchimento à forma (não muda se for tipo linha)
/// @param f forma
/// @param corp cor de preenchimento
/// @pre f != NULL && corp != NULL
void setCORP_forma(FORMA f, char* corp);

/// @brief desloca a forma nas coordenadas (x,y)
/// @param f forma
/// @param dx deslocamento no eixo x
/// @param dy deslocamento no eixo y
/// @return true se a operação foi bem sucedida; false se f == NULL
bool desloca_forma(FORMA f, double dx, double dy);

