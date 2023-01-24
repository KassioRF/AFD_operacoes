#include "headers.h"
#include "utils/argumentos.h"
#include "afd/leitura.h"
#include "afd/exportar.h"

int main() {
  setlocale(LC_ALL, "Portuguese");
  printf("\n\t <<<::: Testes afd.c  :::>>> \n\n");

  char *nome_arquivo = "afd0.txt";
  AFD *Afd;
  
  /*--------------------------------------------------*/
  // LER AFD
  Afd = Afd_ler(nome_arquivo);
  // Exportar .dot
  Afd_exportar(Afd);

  /*---------------------------------------------------*/
  // OPERACOES

  /* free('s) */  
  Afd_destruct(Afd);
  printf("\n\n ");
  

  return 0;

}


