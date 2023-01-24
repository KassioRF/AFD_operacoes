
#include "constants.h"
#include "utils/entrada_saida.h"
#include "afd.h"


#include <unistd.h>
#include <limits.h>


/** Concatena o diretorio dos afds de entrada com o
* nome do arquivo que contem o afd  
*/
// char *get_dir_entrada(char *nome_arquivo) {
//   char *caminho_arquivo = (char*)malloc(MAXCHAR*sizeof(char));
//   strcpy(caminho_arquivo,INPUT_DIR);
//   strcat(caminho_arquivo, nome_arquivo);
//   return caminho_arquivo;

// }


int main() {
  setlocale(LC_ALL, "Portuguese");
  printf("\n\t <<<::: Testes afd.c  :::>>> \n\n");
  char *nome = "afd0.txt";
  char *nome_arquivo; 
  nome_arquivo = get_dir_entrada(nome);

  afd_ler(nome_arquivo);


  
  printf("\n\n ");
  free(nome_arquivo);
  return 0;
}


