#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "listaprio.h"

int compara (const void* a, const void* b) {
  int *ia = (int*)a;
  int *ib = (int*)b;
  if (*ia>*ib)
    return 1;
  else if (*ib>*ia)
    return -1;
  else return 0;
}

int main (void) {
  int i;
  FILE *f;
  int qtos;
  int *nums1, *nums2;
  clock_t m1, m2;

  f = fopen ("/home/aluno/Downloads/entrada.txt", "r");
  if (!f) { printf("erro de abertura! \n"); exit(1); }

  fscanf (f, "%d", &qtos);

  nums1 = (int*) malloc (qtos*(sizeof(int)));

  for (i=0;i<qtos;i++) {
    fscanf (f, "%d", &nums1[i]);
  }

  m1 = clock();
  nums2 = cria_listaordenada (nums1, qtos); 
  m2 = clock();
  printf ("tempo meu heapsort: %f\n", (double)(m2-m1)/CLOCKS_PER_SEC);
  free (nums2);

  m1 = clock();
  qsort (nums1, qtos, sizeof(int), compara);
  m2 = clock();
  printf ("tempo quicksort: %f\n", (double)(m2-m1)/CLOCKS_PER_SEC);

  return 0;
}

  
