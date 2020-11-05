
/* dlst.h
 * Defini��o do TAD lista ordenada duplamente encadeada circular com n� cabe�a e
 * prot�tipo de suas opera��es
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

/* fun��o que inicializa a lista */
void dlst_init(dlst_ptr *);

/* fun��o que insere um novo n� na lista ordenada */
void dlst_inserir(dlst_ptr, dlst_info);

/* fun��o que remove um n� da lista ordenada */
bool dlst_remover(dlst_ptr, dlst_info);

/* fun��o que imprime a lista em ordem crescente */
void dlst_print_cresc(dlst_ptr);

/* fun��o que imprime a lista em ordem decrescente */
void dlst_printf_dec(dlst_ptr);

#endif // _DLST_H
