#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "lista.h"

/******Objetos Privados****/
typedef struct
{
    int id;
    lst_ptr rota;
    lst_ptr_aux lst_aux ;
    bool flag_init;
    bool flag_final;
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

/*********Funcoes Privadas**************/

void distancia(Formiga * f, mapa * pos_atual, mapa * pos_comparacao)
{
    possibilidades possib_aux;
    unsigned int lin = sqrt(pow((pos_atual->linha - pos_comparacao->linha), 2));
    unsigned int col = sqrt(pow((pos_atual->col - pos_comparacao->col), 2));
    possib_aux.dis =  pow((lin + col) * 20, 2);
    possib_aux.m = pos_comparacao;
    lst_ins_aux(&(f->lst_aux), possib_aux);
    if(pos_atual->dado == inicio_.dado)f->flag_init = true;
    if(pos_atual->dado == final.dado)f->flag_final = true;
}

//go do
mapa * best_decisao(Formiga * f)
{

}

int calc_notas_totais_possibilidades(Formiga * f)
{
    lst_ptr_aux l = f->lst_aux;
    int nota_total;
     while(l != NULL) {
        nota_total +=  l->dado.dis;
     }
     return nota_total;
}

//go do
void roleta(Formiga * f)
{
    lst_ptr_aux l_inicio = f->lst_aux;
    lst_ptr_aux l_final = f->lst_aux->ant;
    int soma_pesos = calc_notas_totais_possibilidades(f);
    while(l_inicio != NULL) {
        l_inicio->dado.fx_roleta.porc = (double)l_final->dado.dis / soma_pesos;
        l_inicio->dado.fx_roleta.inf = l_inicio == f->lst_aux ? 0 : l_inicio->ant->dado.fx_roleta.sup;
        l_inicio->dado.fx_roleta.sup = l_inicio->dado.fx_roleta.sup + l_inicio->dado.fx_roleta.porc;
        l_inicio =  l_inicio->prox;
        l_final = l_final->prox;
    }
}

void interacoes()
{
    int i;
    mapa * pos_atual;
    for(i = 0; i < QTD_AGENTES; i++){
        while(true){
            pos_atual = lst_pop_get(agentes[i].rota);
            if(!(pos_atual->linha - 1 < 0)) distancia(&agentes[i], pos_atual, &matriz[pos_atual->linha - 1][pos_atual->col]);
            if(!(agentes[i].flag_init && agentes[i].flag_final))break;
            if(pos_atual->linha != LIN - 1) distancia(&agentes[i], pos_atual, &matriz[pos_atual->linha + 1][pos_atual->col]);
            if(!(pos_atual->col - 1 < 0)) distancia(&agentes[i], pos_atual, &matriz[pos_atual->linha][pos_atual->col - 1]);
            if(pos_atual->col != COL - 1) distancia(&agentes[i], pos_atual, &matriz[pos_atual->linha][pos_atual->col + 1]);
            roleta(&agentes[i]);
            lst_ins(&agentes[i].rota, best_decisao(&agentes[i]));
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
    }
}

/*Inicializa mapa, atribui local inicial de cada agente*/
void init_mapa()
{
    int i, j, cont = 0;
    for(i = 0; i < LIN; i++) {
        for(j = 0; j < COL; j++) {
            matriz[i][j].dado = cont + 1;
            matriz[i][j].linha = i;
            matriz[i][j].col = j;
            lst_ins(&agentes[cont].rota, &matriz[i][j]);
            cont += 1;
        }
    }
}
