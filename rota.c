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
static mapa * pos_acidente;
static mapa hospital_1 = {3, 0, 19};
static mapa hospital_2 = {3, 5, 24};
static mapa matriz[LIN][COL];
static Formiga agentes[QTD_AMBULANCIAS + QTD_HOSPITAIS];

/************* Area de testes *******************/
void print_celula_rota(mapa * m)
{
    printf("%d.[%d,%d]", m->dado, m->linha, m->col);
}

void teste_init_agentes(int qtd_agentes)
{
    int i;
    for(i = 0; i < qtd_agentes; i++) {
        printf("Agente %d", agentes[i].id);
        lst_print(agentes[i].rota);
        printf("pop_get ");
        print_celula_rota(lst_pop_get(agentes[i].rota));
        printf("\n\n");
    }
}

void teste_escolha_rotas_agentes(int qtd_agentes)
{
    int i;
    for(i = 0; i < qtd_agentes; i++) {
        printf("------------------------------------------------------------\n");
        printf("Agente %d\n", agentes[i].id);
        dlst_print_cresc(agentes[i].lst_aux);
        printf("Best Rota = %d\n", lst_pop_get(agentes[i].rota)->dado);
        printf("------------------------------------------------------------\n\n");
    }
}

void print_rota_agentes(int qtd_agentes)
{
    int i;
    for(i = 0; i < qtd_agentes; i++) {
        printf("------------------------------------------------------------\n");
        printf("Agente %d\n", agentes[i].id);
        lst_print(agentes[i].rota);
        printf("Nota: %d\n", lst_size(agentes[i].rota));
        printf("------------------------------------------------------------\n");
    }
}

void print_mapa()
{
    int i, j;
    printf("---------------------- MAPA ATUAL -------------------------------\n");
    for(i = 0; i < LIN; i++) {
        for(j = 0; j < COL; j++)
        printf("%d.[%d][%d], F: %lf\n", matriz[i][j].dado, matriz[i][j].linha, matriz[i][j].col, matriz[i][j].feromonio);
    }
}

void print_result(int qtd_agentes)
{
    printf("---------------------- RESULTADO FINAL -------------------------------\n");
    printf("Pos de acidente: %d.[%d][%d]\n", pos_acidente->dado,
           pos_acidente->linha,
            pos_acidente->col);
    print_rota_agentes(qtd_agentes);
    print_mapa(qtd_agentes);
}
/*****************************Funcoes Privadas****************************************************/

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
    double n = rand() / (RAND_MAX + 1.0);
    dlst_ptr p = f.lst_aux->prox;
    while (p != f.lst_aux) {
        if (n >= p->dado.fx_roleta.inf && n < p->dado.fx_roleta.sup)
            return p->dado.m;
        p = p->prox;
    }
    return NULL;
}

mapa * agente_distict(int qtd_agentes)
{
    int i;
    while(1) {
        mapa * m  = &matriz[rand() % LIN][rand() % COL];
        for (i = 0; i < qtd_agentes; i++) {
            if (m->dado == agentes[i].id
               || m->dado == hospital_1.dado
               || m->dado == hospital_2.dado)
                break;
        }
        if(i == qtd_agentes)
            return m;
    }
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
        l_inicio->dado.fx_roleta.inf = l_inicio == f.lst_aux->prox ? 0.0 : l_inicio->ant->dado.fx_roleta.sup;
        l_inicio->dado.fx_roleta.sup = l_inicio->dado.fx_roleta.inf + l_inicio->dado.fx_roleta.poc_xy;
        l_inicio =  l_inicio->prox;
    }
}

static lst_ptr_cbc best_agente(int qtd_agentes)
{
    int i;
    Formiga best_formiga = agentes[0];
    for(i = 1; i < qtd_agentes; i++) {
        if(best_formiga.rota->size > agentes[i].rota->size)
            best_formiga = agentes[i];
    }
    //printf("\nBest Agente: %d, Nota: %d\n", best_formiga.id, best_formiga.rota->size);
    return best_formiga.rota;
}

static void evaporar_feromonio()
{
    int i, j;
    for(i = 0; i < LIN; i++)
        for(j = 0; j < COL; j++) {
            matriz[i][j].feromonio = (matriz[i][j].feromonio - EVAP_FEROMONIO) <= 0 ?
             FEROMONIO : (matriz[i][j].feromonio - EVAP_FEROMONIO) ;
    }
}

static void kill_rota_agentes(int qtd_agentes)
{
    int i;
    for (i = 0; i < qtd_agentes; i++)
        lst_kill(agentes[i].rota);
}

static void atualiza_feromonio(lst_ptr_cbc l)
{
    lst_ptr_cbc q = lst_distinct(l);
    lst_ptr p = q->prox;
    evaporar_feromonio();
    while(p != (lst_ptr)q) {
        p->dado->feromonio += FEROMONIO;
        p = p->prox;
    }
}

static mapa * drawAcidente(int qtd_agentes)
{
    return agente_distict(qtd_agentes);
}

static lst_ptr_cbc interacoes(int qtd_agentes)
{
    int i, k;
    lst_ptr_cbc lst_best_rota = NULL;
    for (k = 0; k < INTERACOES; k++) {
        for (i = 0; i < qtd_agentes; i++) {
            mapa * pos_atual;
            while (true) {
                pos_atual = lst_pop_get(agentes[i].rota);
                if (pos_atual->dado == pos_acidente->dado)
                    break;

                if (!(pos_atual->linha - 1 < 0))
                    if (!lst_occurs(agentes[i].rota, &matriz[pos_atual->linha - 1][pos_atual->col]))
                        distancia(agentes[i], pos_acidente, &matriz[pos_atual->linha - 1][pos_atual->col]);
                if (pos_atual->linha != LIN - 1)
                    if (!lst_occurs(agentes[i].rota, &matriz[pos_atual->linha + 1][pos_atual->col]))
                        distancia(agentes[i], pos_acidente, &matriz[pos_atual->linha + 1][pos_atual->col]);
                if (!(pos_atual->col - 1 < 0))
                    if (!lst_occurs(agentes[i].rota, &matriz[pos_atual->linha][pos_atual->col - 1]))
                        distancia(agentes[i], pos_acidente, &matriz[pos_atual->linha][pos_atual->col - 1]);
                if (pos_atual->col != COL - 1)
                    if (!lst_occurs(agentes[i].rota, &matriz[pos_atual->linha][pos_atual->col + 1]));
                        distancia(agentes[i], pos_acidente, &matriz[pos_atual->linha][pos_atual->col + 1]);

                roleta(agentes[i]);
                lst_ins(agentes[i].rota, best_decisao(agentes[i]));
                dlst_kill(agentes[i].lst_aux);
            }
        }

        atualiza_feromonio(best_agente(qtd_agentes));

        if (k == INTERACOES - 1)
            lst_best_rota = best_agente(qtd_agentes);
        else
            kill_rota_agentes(qtd_agentes);
    }

    return lst_best_rota;
}

/*******Funcoes Publicas***********/

void init_agentes()
{
    int i;
    for (i = 0; i < QTD_AMBULANCIAS; i++) {
        lst_init(&agentes[i].rota);
        dlst_init(&agentes[i].lst_aux);
        lst_ins(agentes[i].rota, agente_distict(QTD_AMBULANCIAS));
        agentes[i].id = lst_pop_get(agentes[i].rota)->dado;
    }
}

void init_mapa()
{
    int i, j, cont = 0;
    for (i = 0; i < LIN; i++) {
        for (j = 0; j < COL; j++) {
            matriz[i][j].dado = cont + 1;
            matriz[i][j].linha = i;
            matriz[i][j].col = j;
            matriz[i][j].feromonio = FEROMONIO;
            cont += 1;
        }
    }
}

lst_ptr_cbc best_rota_acidente()
{
    lst_ptr_cbc l;
    lst_init(&l);
    init_mapa();
    init_agentes();
    pos_acidente = drawAcidente(QTD_AMBULANCIAS);
    return interacoes(QTD_AMBULANCIAS);
}

lst_ptr_cbc best_rota_hospital()
{
    init_mapa();
    lst_init(&agentes[QTD_AMBULANCIAS].rota);
    lst_init(&agentes[QTD_AMBULANCIAS + 1].rota);
    dlst_init(&agentes[QTD_AMBULANCIAS].lst_aux);
    dlst_init(&agentes[QTD_AMBULANCIAS + 1].lst_aux);
    lst_ins(agentes[0].rota, &matriz[3][0]);
    lst_ins(agentes[1].rota, &matriz[3][5]);
    agentes[0].id = lst_pop_get(agentes[0].rota)->dado;
    agentes[1].id = lst_pop_get(agentes[1].rota)->dado;
    return interacoes(QTD_HOSPITAIS);
}

void simulador_rotas()
{
    lst_ptr_cbc l1;
    lst_ptr_cbc l2;
    lst_init(&l1);
    lst_init(&l2);
    l1 = best_rota_acidente();
    l2 = best_rota_hospital();
}
