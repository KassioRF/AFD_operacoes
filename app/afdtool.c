#include "headers.h"
#include "utils/argumentos.h"
#include "afd/leitura.h"
#include "afd/exportar.h"


int main() {
  printf("\n\t ::: AFD tool ::: \n ");
  setlocale(LC_ALL, "Portuguese");
  
  char *nome_arquivo = "afd1.txt";
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
