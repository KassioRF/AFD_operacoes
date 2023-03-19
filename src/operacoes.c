/******************************************************************************
  MODULO RESPONSAVEL POR CHAMAR AS OPERACOES DO PROGRAMA
*******************************************************************************/

#include "operacoes.h"



void op_exportarDOT(char* inputFile, char* outputFile) {
  printf("\n\t  -- OP Exportar .dot -- \n");
  printf("\n  --input %s --output %s \n\n", inputFile, outputFile);

  AFD *Afd;
  Afd = Afd_ler(inputFile);

  Afd_exportar(Afd, outputFile);

  Afd_destruct(Afd);

}

void op_complemento(char* inputFile, char* outputFile) {
  printf("\n\t  -- OP complemento -- \n");
  printf("\n  --input %s --output %s \n\n", inputFile, outputFile);
  
  AFD *Afd;
  Afd = Afd_ler(inputFile);
  
  AFD *AfdComp;
  AfdComp = complemento(Afd);
  
  Afd_escrever(AfdComp, outputFile);

  Afd_destruct(Afd);
}

void op_minimizar(char* inputFile, char* outputFile) {
  printf("\n\t  -- OP MINIMIZAR -- \n");
  printf("\n  --input %s --output %s \n\n", inputFile, outputFile);

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
  printf("\n  --AFD: %s --input %s --output %s \n\n", inputAFD, inputFile, outputFile);

  AFD *Afd;
  Afd = Afd_ler(inputAFD);
  
  reconhecer_palavras(Afd, inputFile, outputFile);
  Afd_destruct(Afd);

}