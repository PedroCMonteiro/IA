#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "grafo.h"
 
void mostrarec (int i, int *caminhos) {
  if (caminhos[i] != i)  {
    mostrarec (caminhos[i], caminhos);
    printf ("%d ", caminhos[i]);
  }
}

void mostracaminhos (int* caminhos, int i) {
  if (caminhos[i]==-1)
    printf("no %d não é alcançavel\n", i);
  else {
    printf("caminho para %d: ", i);
    mostrarec(i, caminhos);
  }
  printf ("\n");
}

int main() {
  int * caminhos;
  int i, no;

  Grafo * g=grafoLe("grafo2.dat");
  grafoMostra("Grafo dado: ",g);
  
  while (1) {
    printf ("no origem? (-1 para fim) ");
    scanf("%d", &no);
    if (no==-1) break;
    caminhos = menoresCaminhos(g, no);
    if (caminhos == NULL) printf ("no invalido!\n");
    else for (i=0;caminhos[i]!=-1;i++) mostracaminhos(caminhos, i);
    free (caminhos);
   }

  free(g);

  return 0 ;
}
