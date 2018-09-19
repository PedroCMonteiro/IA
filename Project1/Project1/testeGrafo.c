#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include "grafo.h"
 
void main()
{	
	clock_t start, end;
	double total;
	char fileName[50];
	int times = 10000;
	Grafo* grafo;
	while (1)
	{
		printf("Forneca o arquivo do problema (ou '-1' para acabar):\n");
		scanf("%s", &fileName);

		if (strstr(fileName, "-1"))
		{
			break;
		}

		grafo = grafoLe(fileName);
		if (grafo == NULL)
		{
			printf("Forneca um nome de arquivo existente (ou '-1' para acabar):\n");
			continue;
		}

		//grafoMostra("Grafo dado: ", g);
		printf("Percurso em profundidade - no inicial 0: ");
		start = clock();
		for (int i = 0; i < times; i++)
		{
			grafoPercorreProfundidade(grafo, 0);
		}
		end = clock();
		total = difftime(end,start)/ CLOCKS_PER_SEC/times;
		printf("Time: %f\n",total);
	}
	
	system("Pause");
}
