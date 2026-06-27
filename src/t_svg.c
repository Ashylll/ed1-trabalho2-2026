#include "circulo.h"
#include "forma.h"
#include "linha.h"
#include "retangulo.h"
#include "svg.h"
#include "texto.h"
#include "unity.h"

void setUp(void) {}
void tearDown(void) {}

void teste_escreve_forma_deslocada(void) {
  FILE *fp_svg = fopen("teste.svg", "w");
  Forma fl = cria_forma('l', cria_linha(1, 10.0, 40.0, 40.0, 20.0, "green"));

  double dx, dy;
  get_correcao_ancora(fl, &dx, &dy);

  escreve_forma_deslocada_svg(fp_svg, fl, 100 + dx, 100 + dy);
}

void teste_escreve_frame(void) {
  Forma vet_selecionados[20];

  Forma fc = cria_forma('c', cria_circulo(2, 30.0, 50.0, 10.0, "red", "blue"));
  Forma fr = cria_forma(
      'r', cria_retangulo(3, 90.0, 40.0, 45.0, 15.0, "black", "yellow"));
  Forma fl = cria_forma('l', cria_linha(1, 10.0, 10.0, 40.0, 40.0, "green"));
  Forma ft = cria_forma(
      't', cria_texto(10, 10.0, 100.0, "red", "blue", 'i', "maionese"));

  vet_selecionados[0] = fl;
  vet_selecionados[1] = ft;
  vet_selecionados[2] = fc;
  vet_selecionados[3] = fr;

  escreve_frame("geo-qry.svg", 1, 100.0, 100.0, 10.0, vet_selecionados, 4);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(teste_escreve_frame);
  RUN_TEST(teste_escreve_forma_deslocada);
  return UNITY_END();
}
