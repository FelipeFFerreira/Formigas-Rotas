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
    lst_ptr rota;
    dlst_ptr lst_aux ;
}Formiga;

/*****Variaveis Globais******/
mapa inicio_ = {4, 0, 25};
mapa final = {1, 5, 12};
mapa matriz[LIN][COL];
Formiga agentes[QTD_AGENTES];

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
        printf("Total %lf\n", agentes[i].lst_aux->dado.dis);
        dlst_print_cresc(agentes[i].lst_aux);
        printf("Best Rota = %d\n", lst_pop_get(agentes[i].rota)->dado);
        printf("------------------------------------------------------------\n\n");
    }
}


/*********Funcoes Privadas**************/

void distancia(Formiga * f, mapa * pos_atual, mapa * pos_comparacao)
{
    int dado = f->id;
    possibilidades possib_aux;
    unsigned int lin = sqrt(pow((pos_atual->linha - pos_comparacao->linha), 2));
    unsigned int col = sqrt(pow((pos_atual->col - pos_comparacao->col), 2));
    possib_aux.m = pos_comparacao;
    possib_aux.dis =  pow((lin + col) * 1, 1);
    possib_aux.txy = (double)(1.0 / ((double)possib_aux.dis));
    dlst_inserir(f->lst_aux, possib_aux);
}

mapa * best_decisao(Formiga f)
{
    double n = rand() / (double)RAND_MAX;
    dlst_ptr p = f.lst_aux->prox;
    while(p != f.lst_aux) {
        if(n > p->dado.fx_roleta.inf && n < p->dado.fx_roleta.sup) return p->dado.m;
        p = p->prox;
    }
    return NULL;
}

double calc_notas_totais_possibilidades(Formiga * f)
{
    dlst_ptr l = f->lst_aux->prox;
    double nota_total = 0;
     while(l != f->lst_aux) {
        nota_total +=  l->dado.txy;
        l = l->prox;
     }
     return nota_total;
}

void roleta(Formiga * f)
{
    dlst_ptr l_inicio = f->lst_aux->prox;
    double soma_pesos = calc_notas_totais_possibilidades(f);
    while(l_inicio != f->lst_aux) {
        l_inicio->dado.fx_roleta.poc_xy = l_inicio->dado.txy / soma_pesos;
        l_inicio->dado.fx_roleta.inf = l_inicio == f->lst_aux->prox ? 0 : l_inicio->ant->dado.fx_roleta.sup;
        l_inicio->dado.fx_roleta.sup = l_inicio->dado.fx_roleta.inf + l_inicio->dado.fx_roleta.poc_xy;
        l_inicio =  l_inicio->prox;
    }
}

void interacoes()
{
    int i;
    mapa * pos_atual;
    mapa * pos_comparacao = &inicio_;
    bool flag_init = false;
    for(i = 0; i < QTD_AGENTES; i++){
        while(true) {
            pos_atual = lst_pop_get(agentes[i].rota);
            if(!flag_init && pos_atual == &inicio_) {
                pos_comparacao = &final;
                flag_init = true;
            } else if(flag_init && pos_atual == &final)break;

            if(!(pos_atual->linha - 1 < 0))
                distancia(&agentes[i], pos_comparacao, &matriz[pos_atual->linha - 1][pos_atual->col]);
            if(pos_atual->linha != LIN - 1)
                distancia(&agentes[i], pos_comparacao, &matriz[pos_atual->linha + 1][pos_atual->col]);
            if(!(pos_atual->col - 1 < 0))
                distancia(&agentes[i], pos_comparacao, &matriz[pos_atual->linha][pos_atual->col - 1]);
            if(pos_atual->col != COL - 1)
                distancia(&agentes[i], pos_comparacao, &matriz[pos_atual->linha][pos_atual->col + 1]);

            roleta(&agentes[i]);
            lst_ins(&agentes[i].rota, best_decisao(agentes[i]));
            break;
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
            lst_ins(&agentes[cont].rota, &matriz[i][j]);
            cont += 1;
        }
    }
}
