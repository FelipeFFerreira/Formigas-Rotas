#ifndef _ROTA_H
#define _ROTA_H
#include <stdbool.h>

#define LIN 5
#define COL 6

#define INTERACOES 200
#define QTD_AGENTES 5
#define FEROMONIO 0.1
#define EVAP_FEROMONIO 0.1

/********Objetos Publicos*************/

typedef struct {
    int linha;
    int col;
    int dado;
    double feromonio;
}mapa;

typedef struct {
    double inf;
    double sup;
    double poc_xy;
}faixas_roleta;

typedef struct
{
    mapa * m;
    double txy;
    unsigned long long int  dis;
    faixas_roleta fx_roleta;
}possibilidades;

/**********Funcoes Publicas***************/

/*Inicializa mapa, atribui local inicial de cada k-agente*/
void init_mapa();

void init_agentes();

void init_best_rota();


#endif // _ROTA_H
