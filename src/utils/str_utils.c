/*******************************************************************************
  FERRAMENTAS PARA MANIPULAÇÂO DE STRINGS
*******************************************************************************/

#include "str_utils.h"

/** Converte um vetor de inteiros em string
  Ex: int: [1,2,3,4]
    retorna  str: 1,2,3,4
*/
char* vInt_ToStr(int vetor[], int tam) {
  char* str = malloc(10*tam*sizeof(char)); 
  int pos_str = 0; 
  int i;

  // percorre todos os elementos do vetor menos o último
  for (i = 0; i < tam-1; i++) {     
    pos_str += sprintf(&str[pos_str], "%d.", vetor[i]); 
  }
  //imprimir o ultimo elemento sem virgula
  sprintf(&str[pos_str], "%d", vetor[tam-1]); 

  return str;
}

/** Implementa os metodos auxiliares para leitura e escrita arquivos.*/
/** 
*
* Concatena a string do diretorio de entrada com o nome do arquivo de entrada.
* O inteiro "tipo" especifica qual diretorio deve ser adicionado 
* antes do nome do arquivo:
*
* @param tipo:
*         0 : Para AFD de entrada
*         1 : Para AFD de saida .dot
*         2 : Para Palavra de entrada 
*         3 : Para Palavra de saida
*         4 : Para AFD de saida .txt
*/

char *get_dir_arquivo(char *nome_arquivo, int tipo) {
  char *caminho_arquivo = (char*)malloc(MAXCHAR*sizeof(char));
  char *copia_nome_arquivo = strdup(nome_arquivo); 
  
  if (tipo == 0) 
    { strcpy(caminho_arquivo, AFD_INPUT_DIR); }

  else if (tipo == 1) { 
    // strcat(copia_nome_arquivo, ".dot");  
    strcpy(caminho_arquivo, AFD_OUTPUT_DIR);     
  } 

  else if (tipo == 2)
    { strcpy(caminho_arquivo, PALAVRAS_DIR); }
    
  else if (tipo == 3) {
    // copia_nome_arquivo = remover_extensao_string(copia_nome_arquivo);    
    // strcat(copia_nome_arquivo, "_result.txt");
    strcpy(caminho_arquivo, PALAVRAS_DIR);
  }
  
  else if (tipo == 4) { 
    // strcat(copia_nome_arquivo, ".txt");  
    strcpy(caminho_arquivo, AFD_OUTPUT_DIR);     
  } 

  else {
    printf("\n\t :::: ERRO: get_dir_arquivo(); \
    \n\t o tipo especificado é inválido ::::\n");
    exit(EXIT_FAILURE);
  }
    
  strcat(caminho_arquivo, copia_nome_arquivo);

  free(copia_nome_arquivo); 
  
  return caminho_arquivo;
}

/** 
* remover extensao de uma string 
* 
* Ex: 
* entrada: afd0.txt 
* retorna: afd0
* ref: https://stackoverflow.com/questions/2736753/how-to-remove-extension-from-file-name
*/
char *remover_extensao_string(char* str) {
  char *retStr;
  char *lastExt;
  if (str == NULL) return NULL;
  if ((retStr = malloc (strlen (str) + 1)) == NULL) return NULL;
  strcpy (retStr, str);
  lastExt = strrchr (retStr, '.');
  if (lastExt != NULL)
    *lastExt = '\0';
  return retStr;
}
