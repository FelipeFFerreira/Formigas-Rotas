#include <stdlib.h>
#include "lista.h"
#define INTERACOES 20000
#define QTD_AGENTES 30

typedef struct
{
    mapa * m;
    unsigned long long int  dis;

}possibilities;

typedef struct
{
    int id;
    lst_ptr rota;
    possibilities p[5] ;
}Formiga;



mapa matriz[LIN][COL];
Formiga agentes[QTD_AGENTES];


/* ******** Area de testes *******************/
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

/* **************************************/


void init_agentes()
{
    int i;
    for(i = 0; i < QTD_AGENTES; i++){
        agentes[i].id = i + 1;
        lst_init(&agentes[i].rota);
    }
}


void interacoes()
{
    int i, cont = 0;
    mapa * m;
    for(i = 0; i < QTD_AGENTES; i++){
        m = lst_pop_get(agentes[i].rota);
        if(!(m->linha - 1 < 0)) distancia(m, &matriz[m->linha - 1][m->col], agentes.p, cont);
        if(m->linha != LIN - 1) distancia(m, &matriz[m->linha + 1][m->col], &possibilities[cont++]);
        if(!(m->col - 1 < 0)) distancia(m, &matriz[m->linha][m->col - 1], &possibilities[cont++]);
        if(m->col != COL - 1) distancia(m, &matriz[m->linha][m->col + 1], &possibilities[cont++]);

}

void avalia()
{
    if(!(m->linha - 1 < 0)) distancia(m, &matriz[m->linha - 1][m->col], &possibilities[cont++]);
    if(m->linha != LIN - 1) distancia(m, &matriz[m->linha][m->col + 1], &possibilities[cont++]);
    if(!(m->col - 1 < 0)) distancia(m, &matriz[m->linha][m->col - 1], &possibilities[cont++]);
    if(m->col != COL - 1) distancia(m, &matriz[m->linha][m->col + 1], &possibilities[cont++]);

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

void dis(mapa * inicio, mapa * atual, possibilities * p)
{
    unsigned int lin = sqrt(pow((inicio->linha - atual->linha), 2));
    unsigned int col = sqrt(pow((inicio->col - atual->col), 2));
     p->dis =  pow((lin + col) * 20, 2);
     p->m = atual;
}
