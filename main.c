#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rota.h"

int main()
{
    srand((unsigned long long)time(NULL));
    printf("Algoritmo de otimiazacao de rota baseado em colonia de Formigas!\n\n");
    init_agentes();
    init_mapa();
    init_best_rota();
    //teste_escolha_rotas_agentes();
    print_rota_agentes();
    return 0;
}
