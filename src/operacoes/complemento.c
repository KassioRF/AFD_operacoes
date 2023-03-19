/*******************************************************************************
  GERAR UM NOVO AFD A PARTIR DO COMPLEMENTO DE UM AFD DE ENTRADA
*******************************************************************************/
#include "complemento.h"

/* Este método altera o Afd de entrada
  Invertendo a descrição dos Estados finais e nao finais
 */
AFD *complemento(AFD *Afd) {
  printf("\n\t ----  COMPLEMENTO ---- \n");
  AFD *AfdComp = Afd;

  /* Atualiza o nome do AFD */
  char *sufix = "_comp";
  strcat(AfdComp->nome, sufix);

  /* reseta numero de estados finais */
  AfdComp->nEstadosFinais = 0;

  /* Inverte estados Finais e nao Finais*/
  for (int e = 0; e < AfdComp->nEstados; e++ ) {

    if ( AfdComp->Estados[e].Final == 1) {
      
      AfdComp->Estados[e].Final = 0;
    
    }else {      
      
      AfdComp->Estados[e].Final = 1;      
      AfdComp->nEstadosFinais ++;

    }
  }

  return AfdComp;

}