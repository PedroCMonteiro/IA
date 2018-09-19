#include <stdio.h>
#include <stdlib.h>
#include "mapa.h"

int main(void) {

  int chavedada;

  Mapa *mapa1 = cria();

  debug_mostra_mapa(mapa1);

  mapa1 = cria();
  while(1){
    printf ("inserir em mapa1 (digite -1 para terminar): "); 
    scanf ("%d", &chavedada);
    if (chavedada==-1) break;
    mapa1 = insere(mapa1, chavedada, chavedada);
    debug_mostra_mapa(mapa1);
    printf("\n");
  }
  while (1) {
    printf ("buscar em mapa1 (digite -1 para terminar): ");
    scanf ("%d", &chavedada);
    if (chavedada==-1) break;
    printf("resultado da busca por %d: %d\n", chavedada, busca(mapa1, chavedada));
  }
  
  destroi(mapa1);

  return 0;
}


