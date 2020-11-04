#ifndef _ROTA_H
#define _ROTA_H
#include <stdbool.h>

#define LIN 5
#define COL 6
#define INTERACOES 20000
#define QTD_AGENTES 30

typedef struct {
    int linha;
    int col;
    int dado;
}mapa;

typedef struct
{
    mapa * m;
    unsigned long long int  dis;
}possibilidades;

void init_mapa();

void init_agentes();



#endif // _ROTA_H
