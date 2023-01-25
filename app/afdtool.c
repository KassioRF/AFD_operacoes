#include "headers.h"
#include "utils/argumentos.h"
#include "afd/leitura.h"
#include "afd/exportar.h"
#include "operacoes/operacoes.h"

/** @TODO: Adicionar paramentros na compilacao 
    Validar parametros e direcionar as chamadas 
    de acordo com cada parametro passado
*/

int main() {
  printf("\n ::: AFD tool ::: \n ");
  setlocale(LC_ALL, "Portuguese");
  
  char *nome_afd = "afd0.txt";
  AFD *Afd;
  
  // Funcionalidade 1:
  // LER AFD
  Afd = Afd_ler(nome_afd);
  //Afd_toString(Afd);
  // Exportar .dot
  Afd_exportar(Afd);


  /*---------------------------------------------------*/
  // OPERACOES:

  // Funcionalidade 2:
  complemento();

  // Funcionalidade 3:
  uniao();
  intersecao();
  // Funcionalidade 4:
  

  // Funcionalidade 5:
  reconhecer_palavras(Afd, "palavras0.txt");

  /* free('s) */  
  Afd_destruct(Afd);
  printf("\n\n ");
  return 0;

}
