#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <float.h>
#include "grafo.h"
#include "listaprio2.h"

typedef struct _viz Viz;
struct _viz {
	int noj;
	float peso;
	Viz*  prox;
};

struct _grafo {
	int nv;           /* numero de nos ou vertices */
	int na;           /* numero de arestas */
	Viz** viz;         /* viz[i] aponta para a lista de arestas vizinhas do no i */
};

/* aux para fila */
typedef struct _sq SQ;
struct _sq {
	int info;
	SQ* prox;
};

/* funções auxiliares para percurso em largura - ignore inicialmente*/

static Viz* criaViz(Viz* head, int noj, float peso)
{
	/* insere vizinho no inicio da lista */
	Viz* no = (Viz*)malloc(sizeof(Viz));
	assert(no);

	if (head != NULL && (peso > head->peso))
	{
		no = criaViz(head->prox, noj, peso);
		head->prox = no;
		return head;
	}
	else
	{
		no->noj = noj;
		no->peso = peso;
		no->prox = head;
		return no;
	}
}
//static Viz* criaViz(Viz* head, int noj, float peso) {
//	/* insere vizinho no inicio da lista */
//	Viz* no = (Viz*)malloc(sizeof(Viz));
//	assert(no);
//	no->noj = noj;
//	no->peso = peso;
//	no->prox = head;
//	return no;
//}

static Grafo* grafoCria(int nv, int na) {

	int i;
	Grafo* g = (Grafo *)malloc(sizeof(Grafo));
	g->nv = nv;
	g->na = na;
	g->viz = (Viz **)malloc(sizeof(Viz *) * nv);
	for (i = 0; i < nv; i++)
		g->viz[i] = NULL;
	return g;
}


Grafo* grafoLe(char* filename) {
	/* cria grafo não orientado - supõe que arquivo está correto! */

	FILE *arq = fopen(filename, "rt");
	int nv, na, no1, no2 = 0;
	float peso;
	Grafo* novo;

	fscanf(arq, "%d %d", &nv, &na);
	novo = grafoCria(nv, na);
	assert(novo);
	while (fscanf(arq, "%d %d %f", &no1, &no2, &peso) == 3) {
		novo->viz[no1] = criaViz(novo->viz[no1], no2, peso);
		novo->viz[no2] = criaViz(novo->viz[no2], no1, peso);
	}
	return novo;
}

Grafo* grafoLibera(Grafo* grafo) {
	if (grafo) {
		int i = 0;
		Viz* no, *aux;
		for (i = 0; i < grafo->nv; i++) {
			no = grafo->viz[i];
			while (no) {
				aux = no->prox;
				free(no);
				no = aux;
			}
		}
		free(grafo->viz);
		free(grafo);
	}
	return NULL;
}

void grafoMostra(char* title, Grafo * grafo) {
	int i;
	if (title)
		printf("%s", title);
	if (grafo) {
		printf("NV: %d, NA: %d\n", grafo->nv, grafo->na);
		for (i = 0; i < grafo->nv; i++) {
			Viz* viz = grafo->viz[i];
			printf("[%d]->", i);
			while (viz) {
				printf("{%d, %g}->", viz->noj, viz->peso);
				viz = viz->prox;
			}
			printf("NULL\n");
		}
	}
}

static void profundidade2(Grafo* g, int no, int* check) {
	Viz* l = g->viz[no];
	if (!check[no]) {
		printf("%d  ", no);
		check[no] = 1;
		while (l) {
			profundidade2(g, l->noj, check);
			l = l->prox;
		}
	}
}

void grafoPercorreProfundidade(Grafo *grafo, int no_inicial) {
	/* dica: use uma função interna para implementar o percurso em profundidade */
	if (no_inicial < grafo->nv) {
		int j, *check = malloc(sizeof(int)*(grafo->nv));
		for (j = 0;j < grafo->nv;j++) check[j] = 0;
		profundidade2(grafo, no_inicial, check);
		printf("\n");
	}
	else
		printf("No nao encontrado\n");
}

static SQ* enqueue(SQ* queue, int info) {
	SQ* novo = (SQ*)malloc(sizeof(SQ));
	SQ* aux = queue;
	assert(novo);
	novo->info = info;
	novo->prox = NULL;
	if (!queue) {
		return novo;
	}
	while (aux->prox) {
		aux = aux->prox;
	}
	aux->prox = novo;
	return queue;
}

static SQ* dequeue(SQ* queue, int* info) {
	SQ* libera;
	if (!queue) {
		*info = -1;
		return NULL;
	}
	*info = queue->info;
	libera = queue;
	queue = queue->prox;
	free(libera);
	return queue;
}

void grafoPercorreLargura(Grafo *grafo, int no_inicial) {
	/* essa função deve ser implementada sem recusão */
	if (no_inicial < grafo->nv) {
		int a, j;
		int* check = (int*)malloc((grafo->nv) * sizeof(int));
		for (j = 0;j < grafo->nv;j++)   check[j] = 0;
		SQ* sq = NULL;
		sq = enqueue(sq, no_inicial);
		check[no_inicial] = 1;
		Viz* l = NULL;
		while (sq) {
			sq = dequeue(sq, &a);
			printf("%d  ", a);
			l = grafo->viz[a];
			while (l != NULL) {
				if (!check[l->noj]) {
					check[l->noj] = 1;
					sq = enqueue(sq, l->noj);
				}
				l = l->prox;
			}
		}
		free(l);
		printf("\n");
	}
	else
		printf("No nao encontrado\n");
}

int* menoresCaminhos(Grafo *grafo, int no_inicial) {
	if (no_inicial >= grafo->nv)
		return NULL;
	int *MenorCaminho = (int*)malloc((grafo->nv + 1) * sizeof(int));
	ListaP *l = listap_cria(grafo->nv);
	Viz *arestas;
	int *check = (int*)malloc(grafo->nv * sizeof(int));
	float *TamanhoMenor = (float*)malloc((grafo->nv) * sizeof(float));
	int j, temp;
	float menor;
	for (j = 0;j < grafo->nv;j++) {
		listap_insere(l, INT_MAX, j);
		TamanhoMenor[j] = FLT_MAX;
		MenorCaminho[j] = -1;
		check[j] = 0;
	}
	MenorCaminho[j] = -1;
	listap_corrige(l, 1, no_inicial);
	MenorCaminho[no_inicial] = no_inicial;
	TamanhoMenor[no_inicial] = 0;
	while (j != -1) {
		j = listap_remove(l);
		if (j != -1) {
			check[j] = 1;
			for (j = 0;j < grafo->nv;j++)
				if (!check[j])
					for (arestas = grafo->viz[j];arestas;arestas = arestas->prox)
						if (check[arestas->noj]) {
							for (menor = arestas->peso, temp = arestas->noj;temp != no_inicial;menor += TamanhoMenor[temp], temp = MenorCaminho[temp]);
							if (TamanhoMenor[j] > menor) {
								listap_corrige(l, menor, j);
								TamanhoMenor[j] = menor;
								MenorCaminho[j] = arestas->noj;
							}
						}
		}
	}
	return MenorCaminho;
}

Grafo* arvoreCustoMinimo(Grafo *grafo);
