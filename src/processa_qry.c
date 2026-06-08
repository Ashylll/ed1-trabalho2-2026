#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "processa_qry.h"
#include "arvore.h"
#include "sorting.h"
#include "forma.h"
#include "retangulo.h"

static int n_selecionadas = 0; 

static void clona_move_forma(ARVORE formas, FORMA vet_sel[], double dx, double dy){
    for (int i = 0; i < n_selecionadas; i++){
        FORMA clone = clona_forma(vet_sel[i]);
        insere_arvore(formas, clone);

        desloca_forma(clone, dx, dy);
        vet_sel[i] = clone;
    }
}


static void cm(double x, double y, double w, double h, double dx, double dy, ARVORE formas, ARVORE formas_marcadores, FORMA vet_sel[], int* n_selecionadas){
    FORMA retangulo_sel = cria_forma('r', cria_retangulo(-1, x, y, w, h, "red", "none"));
    insere_arvore(formas_marcadores, retangulo_sel);
    
    n_selecionadas = 0;
    formas_selecionadas_para_vetor(formas, retangulo_sel, vet_sel, &n_selecionadas);
    
    clona_move_forma(formas, vet_sel, dx, dy);

    for(int i = 0; i < n_selecionadas; i++){
        insere_arvore(formas, vet_sel[i]);
    }
}

static void comando_cm(const char* linha, FILE* fp_qry, FILE* fp_log, ARVORE formas, ARVORE formas_marcadores, FORMA vet_sel[]){
    double x, y, w, h, dx, dy;
    
    sscanf(linha, "%*s %lf %lf %lf %lf %lf %lf", &x, &y, &w, &h, &dx, &dy) != 6) return;
    fprintf(fp_log, "[*] cm %lf %lf %lf %lf %lf %lf\n", x, y, w, h, dx, dy);
    
    cm(x, y, w, h, dx, dy, formas, formas_marcadores, vet_sel, n_selecionadas);
}

static void sel(double x, double y, double w, double h, ARVORE formas, ARVORE formas_marcadores, FORMA vet_sel[], int* n_selecionadas){
    FORMA retangulo_sel = cria_forma('r', cria_retangulo(-1, x, y, w, h, "red", "none"));
    insere_arvore(formas_marcadores, retangulo_sel);
    
    n_selecionadas = 0;
    formas_selecionadas_para_vetor(formas, retangulo_sel, vet_sel, &n_selecionadas);
}

static void comando_sel(const char* linha, FILE* fp_qry, FILE* fp_log, ARVORE formas, ARVORE formas_marcadores, FORMA vet_sel[]){
    double x, y, w, h;
    
    sscanf(linha, "%*s %lf %lf %lf %lf", &x, &y, &w, &h) != 4) return;
    fprintf(fp_log, "[*] sel %lf %lf %lf %lf\n", x, y, w, h);    

    sel(x, y, w, h, formas, formas_marcadores, vet_sel, &n_selecionadas);

    if (n_selecionadas > 0) fprintf(fp_log, "Formas selecionadas:\n\n");
    else fprintf(fp_log, "Nenhuma forma selecionada\n\n");

    for(int i = 0; i < n_selecionadas; i++){
        int id = getId_forma(vet_sel[i]);
        char tipo = getTipo_forma(vet_sel[i]);

        fprintf(fp_log, "Id: %d\nTipo: %s\n\n", id, traduz_tipo_forma(tipo, false));
    }
}

static void cria_quadrados_marcadores(FORMA vet_sel[], ARVORE formas_marcadores, int k){
    for(int i = 0; i < k; i++){
        double x, y;

        getAncora_forma(vet_sel[i], &x, &y);
        FORMA quadrado_ancora = cria_forma('r', cria_retangulo(-2, x, y, 10, 10, "red", "none"));

        insere_arvore(formas_marcadores, quadrado_ancora);
    }
}

static void remove_formas_maiores(ARVORE formas, FORMA vet_sel[], int k){
    for (int i = k; i < n_selecionadas; i++){
        remove_arvore(formas, vet_sel[i]);
        vet_sel[i] = NULL;
    }
}

static void find(int k, char* alg, char crit, double x, double y, double dw, char* comb_out, ARVORE formas, ARVORE formas_marcadores, FORMA vet_sel, bool rm){
    
    posiciona_formas(vet_sel, n_selecionadas, x, y, dw);
    
    FCOMPARA_FORMAS criterio_ordenacao;
    
    switch (crit){
        case 'd': 
            cria_quadrados_marcadores(vet_sel, formas_marcadores, k);
            if (rm) remove_formas_maiores(formas, vet_sel, k);
            fprintf(fp_log, "Critério \"default\". Formas já ordenadas\n");
            return;
    
        case 'a': criterio_ordenacao = compara_area; break;
        case 'w': criterio_ordenacao = compara_largura; break;
        case 'h': criterio_ordenacao = compara_altura; break;
        case 'c': criterio_ordenacao = compara_cor_preenchimento; break;
        default:  criterio_ordenacao = NULL; break;
    }

    if (strcmp(alg, "bs") == 0) bubble_sort_animado(comb_out, formas, vet_sel, n_selecionadas, k, criterio_ordenacao);
    /*
    else if (strcmp(alg, "ss") == 0) selection_sort_animado();
    else if (strcmp(alg, "is") == 0) insertion_sort_animado();
    else if (strcmp(alg, "shs") == 0) shell_sort_animado();
    else if (strcmp(alg, "qs") == 0) quick_sort_animado();
    else if (strcmp(alg, "ms") == 0) merge_sort_animado();
    */
    cria_quadrados_marcadores(vet_sel, formas_marcadores, k);
    
    if (rm) remove_formas_maiores(formas, vet_sel, k);
}

static void comando_find(const char* linha, const char* comb_out, FILE* fp_qry, FILE* fp_log, ARVORE formas, ARVORE formas_marcadores, FORMA vet_sel[], bool rm){ 
    int k;
    char alg[8];
    char crit;
    double x, y, dw;
    if(sscanf(linha, "%*s %d %s %c %lf %lf %lf", &k, alg, &crit, &x, &y, &dw) != 6) return;
    
    if (rm) fprintf(fp_log, "[*] findrm %d %s %c %lf %lf %lf\n", k, alg, crit, x, y, dw);
    else fprintf(fp_log, "[*] find %d %s %c %lf %lf %lf\n", k, alg, crit, x, y, dw);
    
    if (n_selecionadas <= 0){
        fprintf(fp_log, "Nenhuma forma selecionada para ordenação\n\n");
        return;
    }

    find(k, alg, crit, x, y, dw, comb_out, formas, formas_marcadores, vet_sel, rm);

    fprintf(fp_log, "Formas selecionadas segundo o critério:\n");
    for(int i = 0; i < n_selecionadas; i++){
        reporta_forma(fp_log, vet_sel[i], crit);
    }
}

static void comando_mc(FORMA vet_sel[]){
    for (int i = 0; i < n_selecionadas; i++){
        troca_cores_forma(vet_sel[i]);
    }
}

bool processa_qry(const char* path_qry, const char* path_log, const char* comb_out, ARVORE formas, ARVORE formas_marcadores){
    FILE* fp_qry = fopen(path_qry, "r");
    FILE* fp_log = fopen(path_log, "w");
    if(!fp_qry || !fp_log) return false;
    
    FORMA vet_sel = malloc(200 * sizeof(FORMA));
    
    char linha[1024], comando[8];

    while (fgets(linha, sizeof linha, fp_qry)){
        if(sscanf(linha, "%7s", comando) != 1) continue;
        
        if(comando[0] == '#') continue;
    
        if (strcmp(comando, "sel") == 0) {
            comando_sel(linha, fp_qry, fp_log, formas, formas_marcadores, vet_sel, false);
        } 
        else if (strcmp(comando, "find") == 0) {
            comando_find(linha, comb_out, fp_qry, fp_log, formas, formas_marcadores, vet_sel, false);
        } 
        else if (strcmp(comando, "cm") == 0) {
            comando_sel(linha, fp_qry, fp_log, formas, formas_marcadores, vet_sel, true);
        } 
        else if (strcmp(comando, "findrm") == 0) {
            comando_find(linha, comb_out, fp_qry, fp_log, formas, formas_marcadores, vet_sel, true);
        } 
        else if (strcmp(comando, "mc") == 0) {
            comando_mc(vet_sel);
        } 
        else {
            return false; 
        }
    }

    free(vet_sel);
    fclose(fp_qry);
    fclose(fp_log);
    return true;
}