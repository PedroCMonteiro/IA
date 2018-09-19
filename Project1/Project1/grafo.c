#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <float.h>
#include <string.h>
#include "grafo.h"
#include "listaprio2.h"
int soma = 0;
int instaciaTotal = 0;
typedef struct _viz Viz;
struct _viz
{
	int noj;
	float peso;
	Viz*  prox;
};

struct _grafo
{
	int nv;           /* numero de nos ou vertices */
	Viz** viz;         /* viz[i] aponta para a lista de arestas vizinhas do no i */
};

/* aux para fila */
typedef struct _sq SQ;
struct _sq
{
	int info;
	SQ* prox;
};

/* funções auxiliares para percurso em largura - ignore inicialmente*/

static Viz* criaViz(Viz* head, int noj, float peso)
{
	/* insere vizinho no inicio da lista */
	Viz* no = (Viz*)malloc(sizeof(Viz));
	assert(no);

	if (head != NULL)
	{
		Viz* l = (Viz*)malloc(sizeof(Viz));
		assert(l);
		Viz* no = (Viz*)malloc(sizeof(Viz));
		assert(no);
		no->peso = -1;
		no->noj  = noj;
		no->prox = NULL;
		for (l = head; l->prox != NULL && l->peso < peso; l = l->prox)
		{
			if (l->prox->peso > peso)
			{
				//no->noj  = l->prox->noj;
				no->peso = peso;
				no->prox = l->prox;
				//l->noj = noj;
				//l->peso = peso;
				l->prox  = no;
				break;
			}
		}
		if (no->peso == -1)
		{ 
			if (l->peso > peso)
			{
				no->noj  = l->noj;
				no->peso = l->peso;
				no->prox = l->prox;
				l->noj   = noj;
				l->peso  = peso;
				l->prox  = no;
			}
			else
			{
				no->peso = peso;
				no->prox = l->prox;
				l->prox  = no;
			}
		}
		//no = criaViz(head->prox, noj, peso);
		return head;
	}
	else
	{
		no->noj  = noj;
		no->peso = peso;
		no->prox = NULL;
		return no;
	}
}

static Grafo* grafoCria(int nv)
{
	Grafo* g = (Grafo *)malloc(sizeof(Grafo));
	g->nv = nv;
	g->viz = (Viz **)malloc(sizeof(Viz *) * nv);
//	assert(g->viz);
	for (int i = 0; i < nv; i++)
		g->viz[i] = NULL;
	return g;
}


Grafo* grafoLe(char* filename)
{
	/* cria grafo não orientado - supõe que arquivo está correto! */

	FILE *arq = fopen(filename, "rt");

	if (arq == NULL)
	{
		printf("Arquivo nao encontrado!!\t");
		return NULL;
	}

	int numCidades;
	char dim[22] = "";
	char format[15] = "";
	Grafo* novo;

	// ler o cabelhaço pegando o formato da matriz e o numero de cidades
	while (1)
	{
		fscanf(arq, "%s", &dim);
		if (strstr(&dim, "DIMENSION:"))
		{
			fscanf_s(arq, "%d", &numCidades);
		}
		if (strstr(&dim, "EDGE_WEIGHT_FORMAT:"))
		{
			fscanf(arq, "%s", &format);
		}
		if (strstr(&dim, "EDGE_WEIGHT_SECTION"))
		{
			break;
		}
	}

	// aloca o vetor de lista de viz para do tamanho do numero de cidades
	novo = grafoCria(numCidades);
	assert(novo);

	// le o arquivo de acordo com o formato pego no cabeçalho e insere os dados no grafo
	if (strstr(&format, "FULL_MATRIX"))
	{
		fullMatrix(arq, novo);
	}
	else if (strstr(&format, "UPPER_COL"))
	{
		upperCol(arq, novo);
	}
	else if (strstr(&format, "UPPER_ROW"))
	{
		upperRow(arq, novo);
	}
	else if (strstr(&format, "UPPER_DIAG_ROW"))
	{
		upperDiagRow(arq, novo);
	}
	else if (strstr(&format, "UPPER_DIAG_COL"))
	{
		upperDiagCol(arq, novo);
	}
	else if (strstr(&format, "LOWER_DIAG_COL"))
	{
		lowerDiagCol(arq, novo);
	}
	else if (strstr(&format, "LOWER_DIAG_ROW"))
	{
		lowerDiagRow(arq, novo);
	}
	else if (strstr(&format, "LOWER_COL"))
	{
		lowerCol(arq, novo);
	}
	else if (strstr(&format, "LOWER_ROW"))
	{
		lowerRow(arq, novo);
	}
	else
	{
		printf("Format unkown");
		return NULL;
	}

	return novo;
}

Grafo* grafoLibera(Grafo* grafo)
{
	if (grafo) {
		int i = 0;
		Viz* no, *aux;
		for (i = 0; i < grafo->nv; i++)
		{
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

void grafoMostra(char* title, Grafo * grafo)
{
	int i;
	if (title)
		printf("%s", title);
	if (grafo)
	{
		printf("NV: %d\n", grafo->nv);
		for (i = 0; i < grafo->nv; i++)
		{
			Viz* viz = grafo->viz[i];
			printf("[%d]->", i);
			while (viz)
			{
				printf("{%d, %g}->", viz->noj, viz->peso);
				viz = viz->prox;
			}
			printf("NULL\n");
		}
	}
}

static void profundidade2(Grafo* g, int no, int* check,int pesoAnterior)
{
	Viz* l = g->viz[no];
	if (!check[no])
	{
		//printf("{No:%d Peso:%d} ", no,soma);
		soma += pesoAnterior;
		instaciaTotal += soma;
		check[no] = 1;
		while (l)
		{
			profundidade2(g, l->noj, check,l->peso);
			l = l->prox;
		}
	}
}

void grafoPercorreProfundidade(Grafo *grafo, int no_inicial)
{
	/* dica: use uma função interna para implementar o percurso em profundidade */
	float** matriz = (float**)calloc(grafo->nv,sizeof(float*));
	if (matriz == NULL)
	{
		printf("Memoria insufiente para matriz");
		return;
	}
	for (int i = 0; i < grafo->nv; i++)
	{
		matriz[i] = (float*)calloc(grafo->nv, sizeof(float));

		if(matriz[i] == NULL) 
		{
			printf("** Erro: Memoria Insuficiente **");
			return NULL;
		}
	}
	for (int i = 0; i < grafo->nv; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			matriz[i][j] = -1;
			matriz[j][i] = -1;
		}
	}
	for (int i = 0; i < grafo->nv; i++)
	{
		for (int j = 0; j < grafo->nv; j++)
		{
			printf("Matriz[%d][%d]: %d\n", i, j, matriz[i][j]);
		}
	}
	if (no_inicial < grafo->nv)
	{
		soma = 0;
		instaciaTotal = soma;
		int cidade, *check = malloc(sizeof(int)*(grafo->nv));
		for (cidade = 0;cidade < grafo->nv;cidade++) check[cidade] = 0;
		profundidade2(grafo, no_inicial, check,0);
		printf("%d\n",instaciaTotal);
		free(check);
	}
	else
		printf("No nao encontrado\n");
}

static SQ* enqueue(SQ* queue, int info)
{
	SQ* novo = (SQ*)malloc(sizeof(SQ));
	SQ* aux = queue;
	assert(novo);
	novo->info = info;
	novo->prox = NULL;
	if (!queue)
	{
		return novo;
	}
	while (aux->prox)
	{
		aux = aux->prox;
	}
	aux->prox = novo;
	return queue;
}

static SQ* dequeue(SQ* queue, int* info)
{
	SQ* libera;
	if (!queue)
	{
		*info = -1;
		return NULL;
	}
	*info = queue->info;
	libera = queue;
	queue = queue->prox;
	//free(libera);
	return queue;
}

void grafoPercorreLargura(Grafo *grafo, int no_inicial)
{
	/* essa função deve ser implementada sem recusão */
	if (no_inicial < grafo->nv) {
		int a, j;
		int soma = 0;
		int* check = (int*)malloc((grafo->nv) * sizeof(int));
		int *MenorCaminho = (int*)malloc((grafo->nv + 1) * sizeof(int));

		for (j = 0;j < grafo->nv;j++)
		{
			check[j] = 0;
			MenorCaminho[j] = -1;
		}
		SQ* sq = NULL;
		sq = enqueue(sq, no_inicial);
		check[no_inicial] = 1;
		MenorCaminho[no_inicial] = 0;
		Viz* l = NULL;
		while (sq)
		{
			sq = dequeue(sq, &a);
			printf("%d  ", a);
			l = grafo->viz[a];

			while (l != NULL)
			{
				if (!check[l->noj])
				{
					soma += l->peso;
					MenorCaminho[l->noj] = soma;
					check[l->noj] = 1;
					sq = enqueue(sq, l->noj);
				}
				l = l->prox;
			}
		}
		free(l);
		printf("\n");
		soma = 0;
		for (j = 0;j < grafo->nv;j++)
		{
			soma += MenorCaminho[j];
			printf("Path weigth %d to %d : %d\n", no_inicial, j, MenorCaminho[j]);
		}
		printf("Total weigth : %d\n", soma);
		free(check);
		free(MenorCaminho);
	}
	else
	{
		printf("No nao encontrado\n");
	}

}

int* menoresCaminhos(Grafo *grafo, int no_inicial)
{
	if (no_inicial >= grafo->nv)
		return NULL;
	int *MenorCaminho = (int*)malloc((grafo->nv + 1) * sizeof(int));
	ListaP *l = listap_cria(grafo->nv);
	Viz *arestas;
	int *check = (int*)malloc(grafo->nv * sizeof(int));
	int *TamanhoMenor = (int*)malloc((grafo->nv) * sizeof(int));
	int j, temp;
	int menor;
	for (j = 0;j < grafo->nv;j++)
	{
		listap_insere(l, INT_MAX, j);
		TamanhoMenor[j] = INT_MAX;
		MenorCaminho[j] = -1;
		check[j] = 0;
	}
	MenorCaminho[j] = -1;
	listap_corrige(l, 1, no_inicial);
	MenorCaminho[no_inicial] = no_inicial;
	TamanhoMenor[no_inicial] = 0;
	while (j != -1)
	{
		j = listap_remove(l);
		if (j != -1)
		{
			check[j] = 1;
			for (j = 0;j < grafo->nv;j++)
				if (!check[j])
					for (arestas = grafo->viz[j];arestas;arestas = arestas->prox)
						if (check[arestas->noj])
						{
							for (menor = arestas->peso, temp = arestas->noj;temp != no_inicial;menor += TamanhoMenor[temp], temp = MenorCaminho[temp]);
							if (TamanhoMenor[j] > menor)
							{
								listap_corrige(l, menor, j);
								TamanhoMenor[j] = menor;
								MenorCaminho[j] = arestas->noj;
							}
						}
		}
	}
	free(check);
	free(MenorCaminho);
	listap_libera(l);
	return TamanhoMenor;
}

void fullMatrix  (FILE * arq, Grafo* grafo)
{
	float peso = 0;
	for (int i = 0;i < grafo->nv;i++)
	{
		for (int j = 0;j < grafo->nv-1;j++)
		{
			fscanf(arq, "%f", &peso);

			if (j > i)
			{
				grafo->viz[i] = criaViz(grafo->viz[i], j, peso);
				grafo->viz[j] = criaViz(grafo->viz[j], i, peso);
			}
		}
	}
}
			     
void upperCol	 (FILE * arq, Grafo* grafo)
{
	float peso = 0;
	for (int i = 1;i < grafo->nv ;i++)
	{
		for (int j = 0;j < i;j++)
		{
			fscanf(arq, "%f", &peso);
			grafo->viz[i] = criaViz(grafo->viz[i], j, peso);
			grafo->viz[j] = criaViz(grafo->viz[j], i, peso);
		}
	}
}
				    
void upperRow	 (FILE * arq, Grafo* grafo)
{
	float peso = 0;
	for (int i = 0;i < grafo->nv - 1;i++)
	{
		for (int j = i + 1;j < grafo->nv;j++)
		{
			fscanf(arq, "%f", &peso);
			grafo->viz[i] = criaViz(grafo->viz[i], j, peso);
			grafo->viz[j] = criaViz(grafo->viz[j], i, peso);
		}
	}
}

void upperDiagRow(FILE * arq, Grafo* grafo)
{
	float peso = 0;
	for (int i = 0;i < grafo->nv - 1;i++)
	{
		fscanf(arq, "%f", &peso);

		for (int j = i+1;j < grafo->nv;j++)
		{
			fscanf(arq, "%f", &peso);
			grafo->viz[i] = criaViz(grafo->viz[i], j, peso);
			grafo->viz[j] = criaViz(grafo->viz[j], i, peso);
		}
	}
}

void upperDiagCol(FILE * arq, Grafo* grafo)
{
	float peso = 0;
	for (int i = 0;i < grafo->nv;i++)
	{
		for (int j = 0;j < i;j++)
		{
			fscanf(arq, "%f", &peso);
			grafo->viz[i] = criaViz(grafo->viz[i], j, peso);
			grafo->viz[j] = criaViz(grafo->viz[j], i, peso);
		}

		fscanf(arq, "%f", &peso);
	}
}

void lowerDiagCol(FILE * arq, Grafo* grafo)
{
	float peso = 0;
	for (int i = 0;i < grafo->nv;i++)
	{
		fscanf(arq, "%f", &peso);

		for (int j = i+1;j < i;j++)
		{
			fscanf(arq, "%f", &peso);
			grafo->viz[i] = criaViz(grafo->viz[i], j, peso);
			grafo->viz[j] = criaViz(grafo->viz[j], i, peso);
		}
	}
}

void lowerDiagRow(FILE * arq, Grafo* grafo)
	{
		float peso = 0;
		for (int i = 0;i < grafo->nv;i++)
		{		
			if (i == 2)
			{
				int ij = 0;
			}
			for (int j = 0;j < i;j++)
			{				
				fscanf(arq, "%f", &peso);
				grafo->viz[i] = criaViz(grafo->viz[i], j, peso);
				grafo->viz[j] = criaViz(grafo->viz[j], i, peso);
			}

			fscanf(arq, "%f", &peso);
		}
	}

void lowerCol    (FILE * arq, Grafo* grafo)
{
	float peso = 0;
	for (int i = 0;i < grafo->nv;i++)
	{
		for (int j = i + 1;j < i;j++)
		{
			fscanf(arq, "%f", &peso);
			grafo->viz[i] = criaViz(grafo->viz[i], j, peso);
			grafo->viz[j] = criaViz(grafo->viz[j], i, peso);
		}
	}
}

void lowerRow    (FILE * arq, Grafo* grafo)
{
	float peso = 0;
	for (int i = 0;i < grafo->nv;i++)
	{
		for (int j = i+1;j < i;j++)
		{
			fscanf(arq, "%f", &peso);
			grafo->viz[i] = criaViz(grafo->viz[i], j, peso);
			grafo->viz[j] = criaViz(grafo->viz[j], i, peso);
		}

	}
}
