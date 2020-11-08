
/* dlst.c
 * Implementa as operações sobre o TAD lista ordenada ducplamente encadeada com nó cabeça
 */

#include "dlst.h"
#include <stdio.h>
#include <stdlib.h>

void dlst_init(dlst_ptr * l)
{
    if((*l = (dlst_ptr) malloc(sizeof(struct dlst_no))) == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria!\n");
        exit(1);
    }
    (*l)->prox = (*l)->ant = *l;
}

void dlst_inserir(dlst_ptr l, dlst_info x)
{
    dlst_ptr n, p;
    if ((n = (dlst_ptr) malloc(sizeof(struct dlst_no))) == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria!\n");
        exit(1);
    }
    n->dado = x;
    p = l;
    while (p->prox != l && x.dis > p->prox->dado.dis) {
        p = p->prox;
    }
    n->prox = p->prox;
    n->ant = p;
    p->prox->ant = n;
    p->prox = n;
}

void dlst_print_cresc(dlst_ptr l)
{
    dlst_ptr p = l->prox;
    while (p != l) {
        /*printf("[%d. %d,%d] ,",
                p->dado.m->dado,
                p->dado.m->linha,
                p->dado.m->col);*/
                printf("R: %d\nDis: %llu\nPorc: %g\nLimInf: %g\nLimSup: %g\n",
                p->dado.m->dado,
                p->dado.dis,
                p->dado.fx_roleta.porc,
                p->dado.fx_roleta.inf,
                p->dado.fx_roleta.sup);
                printf("--------------\n");
        p = p->prox;
    }
    printf("\n");
}

