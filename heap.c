/* 
 * File:   heap.h
 * Author: Francisco Rosa Dias de Miranda e
 *          Hiago Vinicius Americo
 */
#include "heap.h"

struct fila_prior 
{
    ITEM ** vetor; 
    int fim; // último elemento 
    int TAM_MAX; // tamanho maximo do vetor
};

/* funcoes internas ao tad */
int inserir (FILA_PRIOR *fp, ITEM *item);
void fix_down(FILA_PRIOR *fp);
void fix_up(FILA_PRIOR *fp);
void swap (FILA_PRIOR *fp, int i, int j);

/* criação da fila  
   @param:  recebe um int indicando o tamanho da fila
   @retorno:  retorna o endereço da fila */
FILA_PRIOR *criar(int n) 
{ 
    FILA_PRIOR *fp = (FILA_PRIOR*)malloc(sizeof(FILA_PRIOR));
    if (fp != NULL)
    {
        fp->fim = -1;     
        fp->vetor = (ITEM **)malloc(n*sizeof(ITEM *));
        fp->TAM_MAX = n;

    // inicializa os apontadores
    if (fp->vetor != NULL)
        for (int i = 0; i < n; i++)
            fp->vetor[i] = NULL;
    }
     
    return fp;   
}
/* exclui a fila 
   @param: recebe uma fila */ 
void excluir (FILA_PRIOR ** F)
{
    for (int i = 0; i < (*F)->TAM_MAX; i++)
    {
        if ((*F)->vetor[i] != NULL)
        {
            liberaPalavra(&(*F)->vetor[i]->nome);
            free((*F)->vetor[i]);
        }
    }
    free((*F)->vetor);
    (*F)->vetor = NULL;
    free(*F);
    *F = NULL;
}

/* insere um elemento na fila
   @param: recebe uma fila e um item para inserção */ 
void fila_inserir (FILA_PRIOR * f, ITEM item)
{
    if(buscar(f,item)==FALSE)
    {
        ITEM * i = (ITEM *) malloc (sizeof(ITEM));
        i->chave = 1;
        i->nome = alocaPalavra(item.nome);
        inserir(f,i);
    }
}

/* busca um elemento na fila e incrementa a chave do elemento se o encontrar
    @param: recebe uma fila e um item para busca
    @retorno: retorna 1 caso exista ou 0 caso contrário */
bool buscar(FILA_PRIOR * f, ITEM item)
{
    for(int i = 0; i <= f->fim; i++)
        if( strcmp(f->vetor[i]->nome, item.nome) == 0)
        {      
            f->vetor[i]->chave++;
            swap(f, i, f->fim);
            fix_up(f);
            return TRUE;
        }
    return FALSE;
}

/* verifica se a fila está cheia
   @param: recebe uma fila  
   @retorno: 1 se todas as posicoes estao ocupadas, 0 caso contrario */ 
int cheia(FILA_PRIOR *fp) 
{
    return (fp->fim == fp->TAM_MAX - 1);   
} 

/* verifica se a fila está vazia
   @param: recebe uma fila
   @retorno: 1 se esta vazia, 0 caso contrario */ 
int vazia(FILA_PRIOR *fp) 
{
    return (fp->fim == -1);   
}

/* inserção de um elemento na fila
   @param: recebe uma fila e um item 
   @retorno: retorna 1 caso não esteja cheia para inserção ou retorna 0 caso contrário */
int inserir (FILA_PRIOR *fp, ITEM *item) 
{ 
    if (!cheia(fp)) 
    { 
        fp->fim++; 
        fp->vetor[fp->fim] = item;
        fp->vetor[fp->fim]->chave = 1;
        fix_up(fp); 
        return 1;     
    } 
    return 0;  
}
/* ordena os itens a partir do nó de inserção, subindo pela árvore um item de maior prioridade */
void fix_up(FILA_PRIOR *fp) 
{
     // função interna 
    int pos = fp->fim; 
    int pai = (pos - 1) / 2; 
    // para heap máximo
    while (pos > 0 && compara(fp->vetor[pos], fp->vetor[pai]) < 0)//fp->vetor[pos]->chave > fp->vetor[pai]->chave)                   
    {      
        swap(fp, pos, pai);
        pos = pai;        
        pai = (pai - 1) / 2;    
    }  
}
/* troca duas variaveis substituindo seus apontadores */
void swap (FILA_PRIOR *fp, int i, int j) 
{
    // função interna    
    ITEM *tmp = fp->vetor[i]; 
    fp->vetor[i] = fp->vetor[j];
    fp->vetor[j] = tmp;
}
/* remove um item da fila
   @param: recebe uma fila 
   @retorno: retorna o primeiro item se a lista não estiver vazia, caso contrário retorna falso */
ITEM *remover (FILA_PRIOR *fp) 
{
    if (fp!= NULL && !vazia(fp)) 
    {         
        ITEM *item = fp->vetor[0]; 
        fp->vetor[0] = fp->vetor[fp->fim]; 
        fp->fim--; 
        fix_down(fp); 
        return item;     
    }
    return NULL; 
}
/* ordena os itens, descendo para os filhos os nós de menor prioridade */
void fix_down(FILA_PRIOR *fp)
{ // função interna
    int fesq, fdir, maior, pos = 0;
    while(pos <= fp->fim / 2)
    { 
        fesq = 2 * pos + 1; 
        fdir = 2 * pos + 2; 
        if (fdir <= fp->fim && compara(fp->vetor[fesq], fp->vetor[fdir]) > 0) //fp->vetor[fesq]->chave < fp->vetor[fdir]->chave) 
            maior = fdir; 
        else 
            maior = fesq;   
        if ( compara(fp->vetor[pos], fp->vetor[maior]) <= 0) //fp->vetor[pos]->chave >= fp->vetor[maior]->chave) 
            break;                         
        // para heap máximo
        swap(fp, pos, maior);
        pos = maior;   
    } 
}

/* imprime a fila
   @param: recebe uma fila para imprimir e n termos que serão impressos*/ 
void imprimir (FILA_PRIOR * f, int n)
{
 // se n > TAM_MAX, fique com o ultimo   
    int q = ((n > f->TAM_MAX) ? f->TAM_MAX : n);
    qsort(f->vetor, f->fim +1, sizeof(ITEM *), compar); 
    for(int i = 0; i< q; i++)
        if (f->vetor[i] != NULL)
            printf("%s %d\n", f->vetor[i]->nome, f->vetor[i]->chave);
    
}