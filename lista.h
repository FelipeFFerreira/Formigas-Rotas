
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
};

typedef possibilidades lst_info_aux;
typedef struct lst_no_aux * lst_ptr_aux;
struct lst_no_aux {
    lst_info_aux dado;
    lst_ptr_aux prox;
};

/* inicializa a lista ordenada */
void lst_init(lst_ptr *);

void lst_init_aux(lst_ptr_aux * l);

/* insere um novo elemento na lista ordenada */
void lst_ins(lst_ptr *, lst_info);

void lst_ins_aux(lst_ptr_aux * l, lst_info_aux val);

/* remove um elemento da lista ordenada */
bool lst_rem(lst_ptr *, lst_info);

/* procura e devolve o ponteiro para o nó da lista
 * que contém um valor, ou NULL, caso o valor não
 * seja localizado */
lst_ptr lst_find(lst_ptr, lst_info);

/* imprime os elementos da lista ordenada */
void lst_print(lst_ptr);

/* destrói uma lista ordenada */
void lst_kill(lst_ptr *);

lst_info lst_pop_get(lst_ptr);
#endif
