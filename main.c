#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rota.h"

int main()
{
    printf("Algoritmo de otimiazacao de rota baseado em colonia de Formigas!\n\n");
    srand((unsigned long long)time(NULL));
    init_mapa();
    init_agentes();
    init_best_rota();
    return 0;
}
