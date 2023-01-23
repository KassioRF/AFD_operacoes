#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "constants.h"


/** 
* Implementa os metodos auxiliares para leitura e escrita arquivos.
*/

/* ========================================================================== */

/** Concatena o diretorio dos afds de entrada com o
* nome do arquivo que contem o afd  
*/
char *get_dir_entrada(char *nome_arquivo) {
  char *caminho_arquivo = (char*)malloc(MAXCHAR*sizeof(char));
  strcat(caminho_arquivo,INPUT_DIR);
  strcat(caminho_arquivo, nome_arquivo);
  return caminho_arquivo;

}
