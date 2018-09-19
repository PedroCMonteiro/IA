#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include < malloc.h>
#include "grafo.h"
 
void main()
{
	int noInicial;
	char fileName[50];
	printf("Forneça o arquivo do problema:\n");
	Grafo* g;
	while (1)
	{
		scanf("%s", &fileName);

		g = grafoLe(fileName);
		if (g != NULL)
		{
			break;
		}
		printf("Forneca um nome de arquivo existente:\n");
	}
	grafoMostra("Grafo dado: ", g);
	while (1) {
		printf("Percurso em profundidade - no inicial (-1 para terminar): ");
		scanf("%d", &noInicial);
		if (noInicial <= -1) break;
		grafoPercorreProfundidade(g, noInicial);
	}

	while (1) {
		printf("Percurso em largura - no inicial (-1 para terminar): ");
		scanf("%d", &noInicial);
		if (noInicial <= -1) break;
		grafoPercorreLargura(g, noInicial);
	}

	while (1) {
		int * menor = (int*)malloc(sizeof(int) * 6);
		int soma = 0;
		printf("Menor caminho - no inicial (-1 para terminar): ");
		scanf("%d", &noInicial);
		if (noInicial <= -1) break;
		menor = menoresCaminhos(g, noInicial);
		for (int i = 0;i < 42;i++)
		{
			printf("No: %.2d total:%d\n", i, menor[i]);
			soma += menor[i];
		}
		printf("%d\n", soma);
		free(menor);
	}

	system("Pause");
}
