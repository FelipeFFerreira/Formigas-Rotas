/*
* Implementação das operações sobre o TAD lista encadeada e duplamente encadeada.
*/

#include "lista.h"
#include <stdlib.h>
#include <stdio.h>

void lst_init(lst_ptr_cbc * l)
{
    if((*l = (lst_ptr_cbc) malloc(sizeof(struct lst_no_cabeca))) == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria!\n");
        exit(1);
    }
    (*l)->size = 0;
    (*l)->prox = (*l)->ant = (lst_ptr)*l;
}

void lst_ins(lst_ptr_cbc l, lst_info val)
{
    lst_ptr n;
    if ((n = (lst_ptr) malloc(sizeof(struct lst_no))) == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria!\n");
        exit(1);
    }
    n->dado = val;
    l->size++;
    if (l->prox == (lst_ptr)l) {
       l->prox = n;
       n->ant = (lst_ptr)l;
    }
    else {
        l->ant->prox = n;
        n->ant = l->ant;
    }
     n->prox = (lst_ptr)l;
     l->ant = n;
}

void lst_print(lst_ptr_cbc l)
{
    lst_ptr p = l->prox;
    while (p != (lst_ptr)l) {
        if(p->dado->dado != 25 && p->dado->dado != 12) {
            printf("%d.[%d,%d],",
                p->dado->dado,
                p->dado-> linha,
                p->dado->col);
            p = p->prox;
            printf("\n");
        }else {
             printf("[%d].[%d,%d],",
                p->dado->dado,
                p->dado-> linha,
                p->dado->col);
                p = p->prox;
                printf("\n");
        }
    }
}

void lst_kill(lst_ptr_cbc l)
{
	lst_ptr p, q = l->prox;
	while (q != (lst_ptr)l) {
		p = q;
		q = q->prox;
		free(p);
	}
}

int lst_occurs(lst_ptr_cbc l, lst_info x)
{
    lst_ptr p = l->prox;
	int cont = 0;
	while (p != (lst_ptr)l) {
		if(p->dado->dado == x->dado)
            cont++;
		p = p->prox;
	}

	return cont > 0;
}

lst_ptr_cbc lst_distinct(lst_ptr_cbc l)
{
    lst_ptr p = l->prox;
    lst_ptr_cbc lst_aux;
    lst_init(&lst_aux);
    while(p != (lst_ptr)l) {
        if(!lst_occurs(lst_aux, p->dado))
            lst_ins(lst_aux, p->dado);
        p = p->prox;
    }

    return lst_aux;
}

int lst_size(lst_ptr_cbc l)
{
	return l->size;
}

lst_info lst_pop_get(lst_ptr_cbc l)
{
    return l->ant->dado;
}
