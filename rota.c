#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include "lista.h"
#include "dlst.h"

/******Objetos Privados****/
typedef struct
{
    int id;
    lst_ptr_cbc rota;
    dlst_ptr lst_aux ;
}Formiga;

/*****Variaveis Privadas******/
static mapa inicio_ = {4, 0, 25};
static mapa final = {1, 5, 12};
static mapa matriz[LIN][COL];
static Formiga agentes[QTD_AGENTES];

/************* Area de testes *******************/
void print_celula_rota(mapa * m)
{
    printf("%d.[%d,%d]", m->dado, m->linha, m->col);
}

void teste_init_agentes()
{
    int i;
    for(i = 0; i < QTD_AGENTES; i++) {
        printf("Agente %d", agentes[i].id);
        lst_print(agentes[i].rota);
        printf("pop_get ");
        print_celula_rota(lst_pop_get(agentes[i].rota));
        printf("\n\n");
    }
}

void teste_escolha_rotas_agentes()
{
    int i;
    for(i = 0; i < QTD_AGENTES; i++) {
        printf("------------------------------------------------------------\n");
        printf("Agente %d\n", agentes[i].id);
        dlst_print_cresc(agentes[i].lst_aux);
        printf("Best Rota = %d\n", lst_pop_get(agentes[i].rota)->dado);
        printf("------------------------------------------------------------\n\n");
    }
}

void print_rota_agentes()
{
    int i;
    for(i = 0; i < QTD_AGENTES; i++) {
        printf("------------------------------------------------------------\n");
        printf("Agente %d\n", agentes[i].id);
        lst_print(agentes[i].rota);
        printf("Nota: %d\n", lst_size(agentes[i].rota));
        printf("------------------------------------------------------------\n");
    }
}

/*********Funcoes Privadas**************/

static void distancia(Formiga f, mapa * pos_atual, mapa * pos_comparacao)
{
    possibilidades possib_aux;
    unsigned int lin = sqrt(pow((pos_atual->linha - pos_comparacao->linha), 2));
    unsigned int col = sqrt(pow((pos_atual->col - pos_comparacao->col), 2));
    possib_aux.m = pos_comparacao;
    possib_aux.dis = (double)pow((lin + col) * 1, 1) + 1;
    possib_aux.txy = 1.0 / possib_aux.dis * pos_comparacao->feromonio;
    dlst_inserir(f.lst_aux, possib_aux);
}

static mapa * best_decisao(Formiga f)
{
    double n = rand() / (double)RAND_MAX;
    dlst_ptr p = f.lst_aux->prox;
    while(p != f.lst_aux) {
        if(n > p->dado.fx_roleta.inf && n <= p->dado.fx_roleta.sup) return p->dado.m;
        p = p->prox;
    }
    return NULL;
}

static double calc_notas_totais_possibilidades(Formiga f)
{
    dlst_ptr l = f.lst_aux->prox;
    double nota_total = 0;
     while(l != f.lst_aux) {
        nota_total +=  l->dado.txy;
        l = l->prox;
     }
     return nota_total;
}

static void roleta(Formiga f)
{
    dlst_ptr l_inicio = f.lst_aux->prox;
    double soma_pesos = calc_notas_totais_possibilidades(f);
    while(l_inicio != f.lst_aux) {
        l_inicio->dado.fx_roleta.poc_xy = l_inicio->dado.txy / soma_pesos;
        l_inicio->dado.fx_roleta.inf = l_inicio == f.lst_aux->prox ? 0 : l_inicio->ant->dado.fx_roleta.sup;
        l_inicio->dado.fx_roleta.sup = l_inicio->dado.fx_roleta.inf + l_inicio->dado.fx_roleta.poc_xy;
        l_inicio =  l_inicio->prox;
    }
}

static void interacoes()
{
    int i;
    for(i = 0; i < QTD_AGENTES; i++){
        bool flag_init = false;
        mapa * pos_atual;
        mapa * pos_comparacao = &inicio_;
        while(true) {
            pos_atual = lst_pop_get(agentes[i].rota);
            if(!flag_init && pos_atual->dado == inicio_.dado) {
                pos_comparacao = &final;
                flag_init = true;
            } else if(flag_init && pos_atual->dado == final.dado)break;

            if(!(pos_atual->linha - 1 < 0))
                distancia(agentes[i], pos_comparacao, &matriz[pos_atual->linha - 1][pos_atual->col]);
            if(pos_atual->linha != LIN - 1)
                distancia(agentes[i], pos_comparacao, &matriz[pos_atual->linha + 1][pos_atual->col]);
            if(!(pos_atual->col - 1 < 0))
                distancia(agentes[i], pos_comparacao, &matriz[pos_atual->linha][pos_atual->col - 1]);
            if(pos_atual->col != COL - 1)
                distancia(agentes[i], pos_comparacao, &matriz[pos_atual->linha][pos_atual->col + 1]);

            roleta(agentes[i]);
            lst_ins(agentes[i].rota, best_decisao(agentes[i]));
            dlst_kill(agentes[i].lst_aux);
            //break;
        }
    }
}

/*******Funcoes Publicas***********/

void init_agentes()
{
    int i;
    for(i = 0; i < QTD_AGENTES; i++){
        agentes[i].id = i + 1;
        lst_init(&agentes[i].rota);
        dlst_init(&agentes[i].lst_aux);
    }
}

void init_mapa()
{
    int i, j, cont = 0;
    for(i = 0; i < LIN; i++) {
        for(j = 0; j < COL; j++) {
            matriz[i][j].dado = cont + 1;
            matriz[i][j].linha = i;
            matriz[i][j].col = j;
            matriz[i][j].feromonio = FEROMONIO;
            lst_ins(agentes[cont].rota, &matriz[i][j]);
            cont += 1;
        }
    }
}

void init_best_rota()
{
    interacoes();
}
