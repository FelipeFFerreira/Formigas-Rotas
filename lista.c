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

void lst_init_aux(lst_ptr_aux * l)
{
    if((*l = (lst_ptr) malloc(sizeof(struct lst_no))) == NULL) {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }
    (*l)->prox = (*l)->ant = *l;
    (*l)->dado = 0;
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

void lst_ins_aux(lst_ptr_aux l, lst_info_aux val) {
	lst_ptr_aux n, p;
	if ((n = (lst_ptr_aux) malloc(sizeof(struct lst_no_aux))) == NULL) {
		printf("Error ao inserir na Lista [Alocacao de memoria]");
		exit(1);;
	}
	n->dado = val;
    p = l;
    while (p->prox != l && val > p->prox->dado) {
        p = p->prox;
    }
    n->prox = p->prox;
    n->ant = p;
    p->prox->ant = n;
    p->prox = n;
    ++l->dado;
}
/*
bool lst_rem(lst_ptr * l, lst_info x)
{
    if (*l == NULL) {
        return false;
    }
    else {
        lst_ptr p = *l;
        if (x == (*l)->dado) {
            *l = p->prox;
            free(p);
            return true;
        }
        else {
            while (p->prox != NULL) {
                p = p->prox;
            }
            if (p->prox != NULL && x == p->prox->dado) {
                lst_ptr n = p->prox;
                p->prox = n->prox;
                free(n);
                return true;
            }
        }
        return false;
    }
}
*/

lst_ptr lst_find(lst_ptr l, lst_info x)
{
    while (l != NULL && x > l->dado) {
        l = l->prox;
    }
    if (l != NULL && x == l->dado) {
        return l;
    }
    return NULL;
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

int lst_rem_all(lst_ptr * l, lst_info x)
{
	int cont = 0;
	lst_ptr p;
	if (*l != NULL && x == (*l)->dado) {
		while (*l != NULL && x == (*l)->dado) {
			p = *l;
			*l = (*l)->prox;
			free(p);
			cont++;
		}
	}
	else {
		lst_ptr q;
		p = *l;
		while (p->prox != NULL && p->prox->dado < x) {
			p = p->prox;
		}
		while (p->prox != NULL && p->prox->dado == x) {
			q = p->prox;
			p->prox = q->prox;
			free(q);
			cont++;
		}
	}
	return cont;
}

lst_ptr lst_merge(lst_ptr x, lst_ptr y)
{
	lst_ptr z, p, n;
	lst_init(&z);
	if (x != NULL && y != NULL) {
		if ((z = (lst_ptr) malloc(sizeof(struct lst_no))) == NULL) {
			fprintf(stderr, "Erro de alocacao de memoria!\n");
			exit(1);
		}
		if(x->dado < y->dado) {
			z->dado = x->dado;
			x = x->prox;
		}
		else {
			z->dado = y->dado;
			y = y->prox;
		}
		z->prox = NULL;
	}
	else {
		if (x != NULL || y != NULL) {
			if ((z = (lst_ptr) malloc(sizeof(struct lst_no))) == NULL) {
				fprintf(stderr, "Erro de alocacao de memoria!\n");
				exit(1);
			}
			if (x != NULL) {
				z->dado = x->dado;
				x = x->prox;
			}
			else {
				z->dado = y->dado;
				y = y->prox;
			}
			z->prox = NULL;
		}
	}
	p = z;
	while (x != NULL && y != NULL) {
		if ((n = (lst_ptr) malloc(sizeof(struct lst_no))) == NULL) {
			fprintf(stderr, "Erro de alocacao de memoria!\n");
			exit(1);
		}
		if (x->dado < y->dado) {
			n->dado = x->dado;
			n->prox = NULL;
			x = x->prox;
		}
		else {
			n->dado = y->dado;
			n->prox = NULL;
			y = y->prox;
		}
		p->prox = n;
		p = n;
	}
	while (x != NULL) {
		if ((n = (lst_ptr) malloc(sizeof(struct lst_no))) == NULL) {
			fprintf(stderr, "Erro de alocacao de memoria!\n");
			exit(1);
		}
		n->dado = x->dado;
		n->prox = NULL;
		x = x->prox;
		p->prox = n;
		p = n;
	}
	while (y != NULL) {
		if ((n = (lst_ptr) malloc(sizeof(struct lst_no))) == NULL) {
			fprintf(stderr, "Erro de alocacao de memoria!\n");
			exit(1);
		}
		n->dado = y->dado;
		n->prox = NULL;
		y = y->prox;
		p->prox = n;
		p = n;
	}
	return z;
}

bool lst_equals(lst_ptr x, lst_ptr y)
{
	while (x != NULL && y != NULL) {
		if (x->dado != y->dado)
			break;
		x = x->prox;
		y = y->prox;
	}
	return x == NULL && y == NULL;
}

lst_info lst_pop_get(lst_ptr l)
{
    while(l->prox != NULL) {
        l = l->prox;
    }
    return l->dado;
}
