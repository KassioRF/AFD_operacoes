#include "headers.h"
#include "utils/argumentos.h"
#include "afd/leitura.h"


int main() {
  printf("\n\t ::: AFD tool ::: \n ");
  setlocale(LC_ALL, "Portuguese");
  
  char *nome = "afd0.txt";
  char *nome_arquivo; 
  nome_arquivo = get_dir_entrada(nome);

  AFD *Afd;

  Afd = afd_ler(nome_arquivo);


  /* free('s) */  
  Afd_destruct(Afd);
  printf("\n\n ");
  free(nome_arquivo);
  return 0;
}
