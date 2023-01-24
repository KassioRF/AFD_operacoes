
#include "../headers.h"
#include "argumentos.h"

/** 
* Implementa os metodos auxiliares para leitura e escrita arquivos.
*/

/* ========================================================================== */

/** Concatena o diretorio dos afds de entrada com o
* nome do arquivo que contem o afd  
*/
char *get_dir_arquivo(char *nome_arquivo, int tipo) {
  char *caminho_arquivo = (char*)malloc(MAXCHAR*sizeof(char));
  if (tipo == 0) 
    { strcpy(caminho_arquivo,INPUT_DIR); }
  else { 
    strcat(nome_arquivo, ".dot" );  
    strcpy(caminho_arquivo,OUTPUT_DIR); 
  }
  
  
  strcat(caminho_arquivo, nome_arquivo);
  return caminho_arquivo;

}

/**
* 
* remover extensao de uma string 
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