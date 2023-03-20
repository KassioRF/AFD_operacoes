/******************************************************************************
  MODULO RESPONSAVEL POR CHAMAR AS FUNCIONALIDADES DO PROGRAMA


  Funcionalidades implementadas:
  
  1) Exportar como dot;
  2) Gerar complemento de um AFD;
  3) Minimizar um AFD;
  4) Reconhecer um conjunto de palavras para um AFD de entrada;

*******************************************************************************/

#include "operacoes.h"

void op_exportarDOT(char* inputFile, char* outputFile) {
  printf("\n\t  -- OP Exportar .dot -- \n");

  AFD *Afd;
  Afd = Afd_ler(inputFile);

  Afd_exportar(Afd, outputFile);

  Afd_destruct(Afd);

}


void op_complemento(char* inputFile, char* outputFile) {
  printf("\n\t  -- OP complemento -- \n");
  
  AFD *Afd;
  Afd = Afd_ler(inputFile);
  
  AFD *AfdComp;
  AfdComp = complemento(Afd);
  
  Afd_escrever(AfdComp, outputFile);

  Afd_destruct(Afd);
}

void op_minimizar(char* inputFile, char* outputFile) {
  printf("\n\t  -- OP MINIMIZAR -- \n");

  AFD *Afd;
  Afd = Afd_ler(inputFile);
  
  AFD *AfdMin;
  AfdMin = minimizar_AFD(Afd);
  
  Afd_escrever(AfdMin,outputFile);

  Afd_destruct(Afd);
  Afd_destruct(AfdMin);

}


void op_reconhecer_palavra(char* inputAFD, char* inputFile, char* outputFile) {
  printf("\n\t  -- OP RECONHECER PALAVRA -- \n");

  AFD *Afd;
  Afd = Afd_ler(inputAFD);
  
  reconhecer_palavras(Afd, inputFile, outputFile);
  Afd_destruct(Afd);

}
