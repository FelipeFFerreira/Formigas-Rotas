#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rota.h"

int main()
{
    printf("Algoritmo de otimiazacao de rota baseado em colonia de Formigas!\n\n");
    srand((unsigned long long)time(NULL));
    simulador_rotas();
    return 0;
}
