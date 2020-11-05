/*
* Implementação das operações sobre o TAD lista encadeada e duplamente encadeada.
*/

#include "lista.h"
#include <stdlib.h>
#include <stdio.h>

void lst_init(lst_ptr * l)
{
    *l = NULL;
}

void lst_ins(lst_ptr * l, lst_info val)
{
    lst_ptr n;
    if ((n = (lst_ptr) malloc(sizeof(struct lst_no))) == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria!\n");
        exit(1);
    }
    n->dado = val;
    if (*l == NULL) {
       n->prox = *l;
       *l = n;
    }
    else {
        lst_ptr p = *l;
        while (p->prox != NULL) {
            p = p->prox;
        }
        n->prox = p->prox;
        p->prox = n;
    }
}

void lst_print(lst_ptr l)
{
    printf("[ ");
    while (l != NULL) {
        printf("%d.[%d,%d],", l->dado->dado,
               l->dado-> linha,
               l->dado->col);
        l = l->prox;
    }
    printf("\b ]\n");
}

void lst_kill(lst_ptr * l)
{
	lst_ptr p;
	while (*l != NULL) {
		p = *l;
		*l = (*l)->prox;
		free(p);
	}
}

int lst_occurs(lst_ptr l, lst_info x)
{
	int cont = 0;
	while (l != NULL && l->dado < x) {
		l = l->prox;
	}
	while (l != NULL && l->dado == x) {
		cont++;
		l = l->prox;
	}
	return cont;
}

int lst_size(lst_ptr l)
{
	int cont = 0;
	while (l != NULL) {
		cont++;
		l = l->prox;
	}
	return cont;
}

lst_info lst_pop_get(lst_ptr l)
{
    while(l->prox != NULL) {
        l = l->prox;
    }
    return l->dado;
}
