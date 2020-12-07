/* 
 * File:   avl.h
 * Author: Francisco Rosa Dias de Miranda e
 *          Hiago Vinicius Americo
 */

#ifndef avl_H
#define avl_H

#define bool int /*Define tipo booleano*/
#define TRUE 1
#define FALSE 0
#define ERRO -32000

#define FILHO_ESQ 0 
#define FILHO_DIR 1


typedef         /*Tipo ITEM da avl*/
struct item_ 
{
    char nome[20];
    int chave;
}
ITEM;


/* TAD arvore binaria de busca */
typedef struct arv_ ARV;

/* Funções deste TAD */

ARV * avl_criar (void); /*Criacao da avl e retorno do seu ponteiro*/

void avl_apagar (ARV **T); /*Apaga todo o conteudo da lista e libera o bloco de memoria*/

bool avl_inserir (ARV **T, ITEM item); /*Insere o ITEM na avl*/

bool avl_remover (ARV **T, ITEM chave); /* REMOVE um item da arvore */

ITEM * avl_buscar (ARV *T, ITEM chave); /*Busca a chave na lista e e a retorna. se nao existir, retorna ERRO*/

void avl_imprimir (ARV * T); /*Imprime os elementos na arvore ordenadamente*/

int avl_altura (ARV * T); /* retorna a altura de uma arvore */

bool avl_vazia (ARV * T); /* retorna 1 se a arv está vazia, 0 caso contrario, ERRO caso nao tenha sido alocada */

#endif /* avl_H */