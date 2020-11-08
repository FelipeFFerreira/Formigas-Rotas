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
    interacoes();
    teste_escolha_rotas_agentes();
    exit(1);
    return 0;
}
