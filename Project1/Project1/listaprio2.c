#include <stdio.h>
#include <stdlib.h>
#include "listaprio2.h"
typedef struct _prio{
  int prio;
  int dado;
}Prio;
struct _listaprio {
  int max; /* tamanho maximo do heap */
  int pos; /* proxima posicao disponivel no vetor */ 
  Prio* prioridade; /* vetor das prioridades */
}; 

static void troca(int a, int b, Prio* v) {
  Prio f = v[a];
  v[a] = v[b];
  v[b] = f;
}

static void corrige_abaixo(Prio* prios, int atual, int tam){
  int pai=atual;
  int filho_esq, filho_dir, filho;
  while (2*pai+1 < tam){
    filho_esq=2*pai+1;
    filho_dir=2*pai+2;
    if (filho_dir >= tam) filho_dir=filho_esq;
    if (prios[filho_esq].prio < prios[filho_dir].prio)
        filho=filho_esq;
    else
        filho=filho_dir;
    if (prios[pai].prio > prios[filho].prio)
            troca(pai,filho,prios);
    else
            break;
    pai=filho;
  }
}

ListaP* listap_cria(int max){
  ListaP* heap=(ListaP*)malloc(sizeof(struct _listaprio)); 
  heap->max=max;
  heap->pos=0;
  heap->prioridade=(Prio*)malloc(max*sizeof(Prio)); 
  return heap;
}

static void corrige_acima(ListaP* heap, int pos) {
  int pai;
  while (pos > 0){
    pai = (pos-1)/2;
    if (heap->prioridade[pai].prio > heap->prioridade[pos].prio)
      troca(pos,pai,heap->prioridade);
    else 
      break;
    pos=pai;
  }
}

void listap_insere(ListaP* heap, int prioridade, int dado) {
  if ( heap->pos < heap->max ) {
    heap->prioridade[heap->pos].prio = prioridade;
    heap->prioridade[heap->pos].dado = dado;
    corrige_acima(heap,heap->pos);
    heap->pos++;
    }
    else {
      printf("Heap CHEIO!\n");
      exit(1);
    }
}

int listap_remove(ListaP* heap) {
  if (heap->pos>0) {
    int topo=heap->prioridade[0].dado;
    heap->prioridade[0]=heap->prioridade[heap->pos-1];
    heap->pos--;
    corrige_abaixo(heap->prioridade, 0, heap->pos);
    return topo;
  }
  else {
     printf("Heap VAZIO!\n");
     return -1;
  }
}

void listap_corrige(ListaP *l, int novaprio, int dado){
  int i;
  for(i=0;i < l->pos;i++)
    if(l->prioridade[i].dado == dado){
      l->prioridade[i].prio = novaprio;
      corrige_acima(l,i);
    }
}

void listap_libera (ListaP * h) {
  free(h->prioridade);
  free(h);
}

void debug_listap_show (ListaP *h, char* title){
  int i;
  printf("%s={",title);
  for (i=0; i<(h->pos); i++)
    printf("[%d:%d],",h->prioridade[i].dado,h->prioridade[i].prio);
  printf("}\n");

}
