#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvore.h"
#include "svg.h"
#include "sorting.h"
#include "leitura_geo.h"
#include "processa_qry.h"

void nome_base(const char *path, char *dest) {
    const char *p = strrchr(path, '/');
    if (!p) p = path;
    else p++;
    
    strcpy(dest, p);
    char *ponto = strrchr(dest, '.'); 
    if (ponto) *ponto = '\0';
}

int main(int argc, char *argv[]){
    char *dir_entrada = "./"; 
    char *nome_arq_geo = NULL;
    char *nome_arq_qry = NULL;
    char *dir_saida = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0) dir_entrada = argv[++i];
        else if (strcmp(argv[i], "-f") == 0) nome_arq_geo = argv[++i];
        else if (strcmp(argv[i], "-q") == 0) nome_arq_qry = argv[++i];
        else if (strcmp(argv[i], "-o") == 0) dir_saida = argv[++i];
    }

    if (!nome_arq_geo || !dir_saida) {
        printf("Parametros obrigatorios -f e -o nao informados\n");
        return 1;
    }

    // Constrói caminho de ENTRADA
    char path_geo[1024];
    sprintf(path_geo, "%s/%s", dir_entrada, nome_arq_geo);

    // Monta nomes de SAÍDA
    char base_geo[256], base_qry[256];
    nome_base(nome_arq_geo, base_geo);
    
    char out_svg_geo[1024];
    sprintf(out_svg_geo, "%s/%s.svg", dir_saida, base_geo);

    char out_svg_comb[1024] = "", out_txt_comb[1024] = "";
    if (nome_arq_qry) {
        nome_base(nome_arq_qry, base_qry);
        sprintf(out_svg_comb, "%s/%s-%s.svg", dir_saida, base_geo, base_qry);
        sprintf(out_txt_comb, "%s/%s-%s.txt", dir_saida, base_geo, base_qry);
    }

    ARVORE formas = cria_arvore(compara_default);
    ARVORE formas_marcadores = cria_arvore(compara_default);
    leitura_geo(path_geo, formas);
    gera_svg_inicial(out_svg_geo, formas); // Gera SVG do .geo

     if (nome_arq_qry) {
        char path_qry[1024];
        sprintf(path_qry, "%s/%s", dir_entrada, nome_arq_qry);

        processa_qry(path_qry, out_txt_comb, out_svg_comb, formas, formas_marcadores);
        gera_svg_final(out_svg_comb, formas, formas_marcadores);
    }

    libera_arvore(&formas);
    libera_arvore(&formas_marcadores);
    
    printf("Arquivos salvos em: %s\n", dir_saida);
    return 0;
}