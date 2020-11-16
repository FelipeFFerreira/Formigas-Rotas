
/* listaord.h
 * Definição do TAD para representar uma lista implementada
 * de forma encadeada e protótipo das operações sobre esse TAD.
 */

#ifndef _LISTAORD_H
#define _LISTAORD_H
#include <stdbool.h>
#include "rota.h"

typedef mapa * lst_info;
typedef struct lst_no * lst_ptr;
struct lst_no {
    lst_info dado;
    lst_ptr prox;
    lst_ptr ant;
};

typedef struct lst_no_cabeca * lst_ptr_cbc;
struct lst_no_cabeca {
    int size;
    lst_ptr prox;
    lst_ptr ant;
};


/* inicializa a lista*/
void lst_init(lst_ptr_cbc *);

/* insere um novo elemento na lista*/
void lst_ins(lst_ptr_cbc, lst_info);

/* imprime os elementos da lista*/
void lst_print(lst_ptr_cbc);

/* destrói uma lista*/
void lst_kill(lst_ptr_cbc);

lst_info lst_pop_get(lst_ptr_cbc);

int lst_size(lst_ptr_cbc l);

lst_ptr_cbc lst_distinct(lst_ptr_cbc l);


#endif
