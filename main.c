#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rota.h"

int main()
{
    srand((unsigned long long)time(NULL));
    printf("Algoritmo de otimiazacao de rota baseado em colonia de Formigas!\n\n");
    init_mapa();
    init_agentes();
    init_best_rota();
    //print_rota_agentes();
    //print_mapa();
    return 0;
}
