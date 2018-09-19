typedef struct _grafo Grafo;

Grafo* grafoLe( char* filename );
Grafo* grafoLibera(Grafo* grafo);
void grafoMostra(char* title, Grafo* grafo);
void grafoPercorreProfundidade(Grafo * grafo, int no_inicial);
Grafo* criaArvoreGeradora (Grafo *grafo, int no_inicial);
void grafoPercorreLargura(Grafo * grafo, int no_inicial);
int* menoresCaminhos (Grafo *grafo, int no_inicial);
Grafo* arvoreCustoMinimo (Grafo *grafo);
void fullMatrix(FILE * arq, Grafo* grafo);
			     
void upperCol    (FILE * arq, Grafo* grafo);
			     						   ;
void upperRow    (FILE * arq, Grafo* grafo);
										   ;
void upperDiagRow(FILE * arq, Grafo* grafo);
										   ;
void upperDiagCol(FILE * arq, Grafo* grafo);
										   ;
void lowerDiagCol(FILE * arq, Grafo* grafo);
							  			   ;
void lowerDiagRow(FILE * arq, Grafo* grafo);
										   ;
void lowerCol    (FILE * arq, Grafo* grafo);
										   ;
void lowerRow    (FILE * arq, Grafo* grafo);

/* formato do arquivo de teste.  grafo
6       ! numero de nos
5       ! numero de arestas
0 1 20  ! aresta:  noi noj peso
1 2 30
1 3 25
3 4 15
4 5 10
*/
