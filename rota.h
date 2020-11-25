#ifndef _ROTA_H
#define _ROTA_H
#include <stdbool.h>

#define LIN 5
#define COL 6

#define INTERACOES 2000
#define QTD_AMBULANCIAS 4
#define QTD_HOSPITAIS 2
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

void simulador_rotas();

#endif // _ROTA_H
