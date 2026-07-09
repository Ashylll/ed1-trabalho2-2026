#ifndef FORMA_H
#define FORMA_H
#endif

#include <stdbool.h>
#include <stdio.h>

/*
   forma.h
   Forma é um contâiner (wrapper) que carrega um ponteiro para uma figura e o
   seu tipo

*/

typedef void *Forma;

/// @brief cria uma forma
/// @param tipo tipo da forma (círculo, retângulo, texto, linha)
/// @param handle handle para a forma (ponteiro para a forma)
/// @return ponteiro para a forma
Forma cria_forma(char tipo, void *handle);

/// @brief libera a forma
/// @param f ponteiro para handle Forma
void libera_forma(Forma *f);

/// @brief escreve a forma em um arquivo SVG aberto em modo escrita
/// @param fp arquivo SVG
/// @param f forma
/// @pre fp != NULL && f != NULL
void escreve_forma_svg(FILE *fp, Forma f);

/// @brief clona a forma (copia valores) com id específico para clone
/// @param f forma original
/// @pre f != NULL
/// @return clone criado
Forma clona_forma(Forma f);

/// @brief troca as cores de borda e de preenchimento da forma
/// @pre f != NULL
/// @param f forma
void troca_cores_forma(Forma f);

/// @brief retorna o tipo da forma em extenso
/// @param tipo tipo
/// @param maiusculo se a primeira letra é maiúscula ou não 
/// @return tipo traduzido
char *traduz_tipo_forma(const char tipo, bool maiusculo);

/// @brief reporta os dados relevantes para ordenação da forma em um arquivo .txt
/// @param fp_txt arquivo .txt
/// @param f forma
/// @param criterio_ordenacao critério de ordenação ('d': default, 'a': área, 'w': largura, 'h': altura, 'c': cor) 
void reporta_forma(FILE *fp_txt, Forma f, char criterio_ordenacao);

/// @brief corrige a posição da âncora da forma para considerar o extremo da figura como âncora
/// @param f forma
/// @param dx variável receptora do deslocamento x
/// @param dy variável receptora do deslocamento y
/// @pre f != NULL
void get_correcao_ancora(Forma f, double *dx, double *dy);

/* === Operações get === */

/// @brief retorna o identificador da forma
/// @param f forma
/// @pre f != NULL
/// @return identificador
int get_id_forma(Forma f);

/// @brief retorna o tipo da forma
/// @param f forma
/// @pre f != NULL
/// @return caractere para o tipo ('c', 'r', 't', 'l')
char get_tipo_forma(Forma f);

/// @brief retorna o handle da forma
/// @param f forma
/// @return handle
void *get_handle_forma(Forma f);

/// @brief lê as coordenadas (x,y) da âncora da forma
/// @param f forma
/// @param x ponteiro para saída da coordenada x
/// @param y ponteiro para saída da coordenada y
/// @return true se a operação foi bem sucedida; false se f == NULL
bool get_ancora_forma(Forma f, double *x, double *y);

/// @brief retorna a coordenada x da âncora da forma
/// @param f forma
/// @pre f != NULL
/// @return coordenada x
double get_x_forma(Forma f);

/// @brief retorna a coordenada y da âncora da forma
/// @param f forma
/// @pre f != NULL
/// @return coordenada y
double get_y_forma(Forma f);

/// @brief retorna a área da forma
/// @param f forma
/// @pre f != NULL
/// @return área
double get_area_forma(Forma f);

/// @brief retorna a largura da forma (texto: 1.0 * número de caracteres)
/// @param f forma
/// @pre f != NULL
/// @return largura
double get_largura_forma(Forma f);

/// @brief retorna a largura real no eixo x da forma
/// @param f forma
/// @pre f != NULL
/// @return largura
double get_largura_x_forma(Forma f);

/// @brief retorna a altura da forma
/// @param f forma
/// @pre f != NULL
/// @return altura
double get_altura_forma(Forma f);

/// @brief retorna a cor de borda da forma
/// @param f forma
/// @pre f != NULL
/// @return cor de borda
char *get_corb_forma(Forma f);

/// @brief retorna a cor de preenchimento da forma. Se for linha, retorna a cor
/// de borda
/// @param f forma
/// @pre f != NULL
/// @return cor de preenchimento
char *get_corp_forma(Forma f);

/* ===================== */

/* === Operações set === */

/// @brief atribui coordenadas (x,y) da forma
/// @param f forma
/// @param x coordenada x
/// @param y coordenada y
/// @return true se a operação foi bem sucedida; false se f == NULL
bool set_ancora_forma(Forma f, double x, double y);

/// @brief seta um valor à coordenada x da âncora da forma
/// @param f forma
/// @pre f != NULL
/// @param x coordenada x
void set_x_forma(Forma f, double x);

/// @brief seta um valor à coordenada y da âncora da forma
/// @param f forma
/// @pre f != NULL
/// @param x coordenada y
void set_y_forma(Forma f, double y);

/// @brief atribui uma cor de borda à forma (atribui cor se for tipo linha)
/// @param f forma
/// @param corb cor de borda
/// @pre f != NULL && corp != NULL
void set_corb_forma(Forma f, char *corb);

/// @brief atribui uma cor de preenchimento à forma (não muda se for tipo linha)
/// @param f forma
/// @param corp cor de preenchimento
/// @pre f != NULL && corp != NULL
void set_corp_forma(Forma f, char *corp);

/// @brief desloca a forma nas coordenadas (x,y)
/// @param f forma
/// @param dx deslocamento no eixo x
/// @param dy deslocamento no eixo y
/// @return true se a operação foi bem sucedida; false se f == NULL
bool desloca_forma(Forma f, double dx, double dy);
