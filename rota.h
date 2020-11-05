#ifndef _ROTA_H
#define _ROTA_H
#include <stdbool.h>

#define LIN 5
#define COL 6

#define INTERACOES 20000
#define QTD_AGENTES 30
#define FEROMONIO 1;

/********Objetos Publicos*************/

typedef struct {
    int linha;
    int col;
    int dado;
    int feromonio;
}mapa;

typedef struct {
    double inf;
    double sup;
    double porc;
}faixas_roleta;

typedef struct
{
    mapa * m;
    unsigned long long int  dis;
    faixas_roleta fx_roleta;
}possibilidades;

/**********Funcoes Publicas***************/

/*Inicializa mapa, atribui local inicial de cada k-agente*/
void init_mapa();

void init_agentes();



#endif // _ROTA_H
