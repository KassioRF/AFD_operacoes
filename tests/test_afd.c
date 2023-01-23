#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "constants.h"
#include "afd.h"


char *get_dir_entrada(char *nome_arquivo) {
  char *caminho_arquivo = (char*)malloc(MAXCHAR*sizeof(char));
  strcat(caminho_arquivo,INPUT_DIR);
  strcat(caminho_arquivo, nome_arquivo);
  return caminho_arquivo;

}

int main() {
  printf("\n\t <<<::: Testes afd.c  :::>>> \n\n");

  char *nome = "afd0.txt";
  char *nome_arquivo; 
  nome_arquivo = get_dir_entrada(nome);

  afd_ler(nome_arquivo);
  
  printf("\n\n ");
  free(nome_arquivo);
  return 0;
}


