#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>
#include "mapa.h"

#define TAM 12

int main(void) {

  int i;
  int chavedada;

  Mapa *mapa1 = cria();

  printf ("inserção sempre à esquerda:\n");
  for (i=TAM-1;i>=0;i--) {
     mapa1 = insere (mapa1, i, i);
  }
  debug_mostra_mapa(mapa1);

  destroi(mapa1);

  printf("escolhendo onde inserir -------------- \n");
  mapa1 = cria();
  while (1) {
    printf ("inserir em mapa1 (digite -1 para terminar): ");
    scanf ("%d", &chavedada);
    if (chavedada==-1) break;
    mapa1 = insere(mapa1, chavedada, chavedada);
    debug_mostra_mapa(mapa1);
  }

  return 0;
}


