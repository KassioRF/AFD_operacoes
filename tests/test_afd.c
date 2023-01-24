#include "headers.h"
#include "utils/argumentos.h"
#include "afd/leitura.h"


int main() {
  setlocale(LC_ALL, "Portuguese");
  printf("\n\t <<<::: Testes afd.c  :::>>> \n\n");

  char *nome = "afd0.txt";
  char *nome_arquivo; 
  nome_arquivo = get_dir_entrada(nome);

  AFD *Afd;

  Afd = afd_ler(nome_arquivo);


  /* free('s) */  
  Afd_destruct(Afd);
  printf("\n\n ");
  free(nome_arquivo);
  return 0;
}


