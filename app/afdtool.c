#include "headers.h"
#include "operacoes.h"

/* 

  Script de inicialização do programa afdtool

  main():
    Faz a chamada da funcionalidade de acordo com o argumento passado 
    como parâmetro de compilação

  src/operacoes.c é o script que implementa a chamada para cada funcionalidade
  implementada.


  Foram implementadas as seguintes funcionalidades:

  1) Exportar como dot;
  2) Gerar complemento de um AFD;
  3) Minimizar um AFD;
  4) Reconhecer um conjunto de palavras para um AFD de entrada;
  
 */

int main( int argc, char *argv[]) {
  printf("\n ::: AFD tool ::: \n");
  setlocale(LC_ALL, "Portuguese");
  
  char *opt_exportar_dot = "--dot";
  char *opt_complemento = "--complemento";
  char *opt_minimizar = "--minimizacao";
  char *opt_reconhecer_palavra = "--reconhecer";


  if (argc < 4) {
    printf("Erro: Argumentos insuficientes\n");
    return 1;
  }
  
  
  if (strcmp(argv[1], opt_exportar_dot) == 0) {
    // opção --dot selecionada
    if (argc != 5) {
      printf("Erro: Argumentos insuficientes para a opção --dot\n");
      return 1;
    }
    
    char *inputFile = argv[2];
    char *outputFile = argv[4];
    op_exportarDOT(inputFile,outputFile);

  }
  else if (strcmp(argv[1], opt_complemento) == 0) {
    // opção --complemento selecionada
    if (argc != 5) {
      printf("Erro: Argumentos insuficientes para a opção --complemento\n");
      return 1;
    }
    
    char *inputFile = argv[2];
    char *outputFile = argv[4];
    op_complemento(inputFile,outputFile);
  
  }
  else if (strcmp(argv[1], opt_minimizar) == 0) {
    // opção --minimizacao selecionada
    if (argc != 5) {
      printf("Erro: Argumentos insuficientes para a opção --minimizacao\n");
      return 1;
    }
    
    char *inputFile = argv[2];
    char *outputFile = argv[4];
    op_minimizar(inputFile,outputFile);
  }
  else if (strcmp(argv[1], opt_reconhecer_palavra) == 0) {
    // opção --reconhecer selecionada
    if (argc != 6) {
      printf("Erro: Argumentos insuficientes para a opção --reconhecer\n");
      return 1;
    }
    
    char *inputAFD = argv[2];
    char *inputFile = argv[3];
    char *outputFile = argv[5];
    op_reconhecer_palavra(inputAFD, inputFile, outputFile);
    
    // call opt
  
  } else {
    
    printf("Erro: Opção desconhecida\n");
    return 1;
  }


  printf("\n\n\n Resultado da Execução: \n");
  if (!strcmp(argv[1], opt_reconhecer_palavra) == 0) {
    printf("\t Opção selecionada: %s\n", argv[1]);
    printf("\t Arquivo de entrada: %s\n", argv[2]);
    printf("\t Arquivo de saída: %s\n", argv[4]);

  } else {
    printf("\t Opção selecionada: %s\n", argv[1]);
    printf("\t Arquivo de entrada AFD: %s\n", argv[2]);
    printf("\t Arquivo de entrada Palavras: %s\n", argv[3]);
    printf("\t Arquivo de saída: %s\n", argv[5]);

  }
  printf("\n\n ");
  return 0;

}
