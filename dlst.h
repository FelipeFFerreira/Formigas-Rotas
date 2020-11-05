
/* dlst.h
 * Definição do TAD lista ordenada duplamente encadeada circular com nó cabeça e
 * protótipo de suas operações
 */

#ifndef _DLST_H
#define _DLST_H
#include <stdbool.h>
#include "rota.h"

typedef possibilidades dlst_info;
typedef struct dlst_no * dlst_ptr;
struct dlst_no {
    dlst_ptr ant;
    dlst_info dado;
    dlst_ptr prox;
};

/* função que inicializa a lista */
void dlst_init(dlst_ptr *);

/* função que insere um novo nó na lista ordenada */
void dlst_inserir(dlst_ptr, dlst_info);

/* função que remove um nó da lista ordenada */
bool dlst_remover(dlst_ptr, dlst_info);

/* função que imprime a lista em ordem crescente */
void dlst_print_cresc(dlst_ptr);

/* função que imprime a lista em ordem decrescente */
void dlst_printf_dec(dlst_ptr);

#endif // _DLST_H
