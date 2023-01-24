#include <stdio.h>
#include "afd.h"
#include "operacoes.h"
#include "./utils/entrada_saida.h"



int main() {
  printf("\n\t ::: AFD tool ::: \n ");
  setlocale(LC_ALL, "Portuguese");
  
  printf("\n\t <<<::: Testes afd.c  :::>>> \n\n");
  char *nome = "afd0.txt";
  char *nome_arquivo; 
  nome_arquivo = get_dir_entrada(nome);

  afd_ler(nome_arquivo);


  
  printf("\n\n ");
  free(nome_arquivo);
  return 0;
}


