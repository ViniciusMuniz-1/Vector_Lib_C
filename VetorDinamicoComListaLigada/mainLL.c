#include "vetorDinamico.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Mostra valor não inserido e sai do programa.*/
void error_at_insertion(linked_list* l, int x) {
  fprintf(stderr, "\033[0;31mErro:\033[0m:\tValor %d não inserido!\n", x);
  fprintf(stderr, "\tA lista possui %d elementos.\n", linked_list_size(l));
  exit(1);
}

/* Imprime a lista na saída padrão. */
void print_vector(linked_list* l) {
  int i, x, erro;
  for (i = 0; i < linked_list_size(l); ++i) {
    x = linked_list_get(l, i, &erro);
    if (!erro) {
      printf("%d ", x);
    }
    else {
      fprintf(stderr, "ERRO: índice %d não é válido!\n", i);
      exit(2);
    }
  }
  printf("\n");
}

int main() {
  time_t inicio, fim;
  int n, i, x;
  linked_list* l01 = linked_list_create();
  scanf("%d", &n);
  for (i = 0; i < n; ++i) {
    scanf("%d", &x);
    if (linked_list_push_back(l01, x) != (i + 1)) {
      error_at_insertion(l01, x);
    }
  }
  int position = 100000000-2;
  inicio = time(0);
  linked_list_remove_from(l01, position);
  fim = time(0);
  fprintf(stderr, "Adicionando %d elementos em %.40lf milissegundos.\n", n, (((double)fim - (double)inicio) / (CLOCKS_PER_SEC * 1000)));
  printf("Tamanho do vetor: %d\n", linked_list_size(l01));

  return 0;
}