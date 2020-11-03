#ifndef _ROTA_H
#define _ROTA_H
#include <stdbool.h>

#define LIN 5
#define COL 6

typedef struct {
    int linha;
    int col;
    int dado;
}mapa;



void init_mapa();

void init_rota_agentes();

void teste_init_agentes();




#endif // _ROTA_H
