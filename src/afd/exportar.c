#include "../headers.h"
#include "../utils/argumentos.h"
#include "exportar.h"

void Afd_exportar(AFD *Afd) {
  printf("\n\t :::: Exportar AFD.dot ::::\n");
  
  char *caminho;
  caminho = get_dir_arquivo(Afd->nome, 1);
  
  FILE * arquivo;
  
  if ( (arquivo = fopen(caminho, "w")) == NULL) {
    printf("\t :::: ERRO: Arquivo ao criar arquivo de saida: %s ::::\n", caminho);
    exit(EXIT_FAILURE);

  }

  escrever_estados(Afd, arquivo);
  escrever_simbolos(Afd, arquivo);
  escrever_transicoes(Afd, arquivo);
  escrever_estado_inicial(Afd, arquivo);
  escrever_estados_final(Afd, arquivo);

  fclose(arquivo);

  printf("\t :::: Arquivo de saida:  %s ::::\n", caminho);


}

void escrever_estados(AFD *Afd, FILE *arquivo) {
  fprintf( arquivo, "%d", Afd->nEstados );
  
  for ( int i = 0; i < Afd->nEstados; i++ ) 
    { fprintf( arquivo, "\n%s", Afd->Estados[i].nome ); }

}

void escrever_simbolos(AFD *Afd, FILE *arquivo) {
  fprintf( arquivo, "\n%d", Afd->nSimbolos );

  for ( int i = 0; i < Afd->nSimbolos; i++ ) 
    { fprintf( arquivo, "\n%s", Afd->Simbolos[i]); }

}

void escrever_transicoes(AFD *Afd, FILE *arquivo) {
  fprintf( arquivo, "\n%d", Afd->nTransicoes );

  for ( int i = 0; i < Afd->nEstados; i++ ) {
    for ( int j = 0; j < Afd->nSimbolos; j++ ) {
      
      if ( Afd->Transicoes[i][j] != -1 ) { 
        fprintf( arquivo, "\n%s %s %s", \
          Afd->Estados[i].nome, \
          Afd->Simbolos[j], \
          Afd->Estados[Afd->Transicoes[i][j]].nome );
        
      }
  
    }  
  }

}

void escrever_estado_inicial(AFD *Afd, FILE *arquivo) {
  fprintf( arquivo, "\n%s", get_estado_inicial(Afd).nome );

}

void escrever_estados_final(AFD *Afd, FILE *arquivo) {
  fprintf( arquivo, "\n%d", Afd->nEstadosFinais );
  
  Estado *EstadosFinais = get_estados_final(Afd);
  
  for (int i = 0; i < Afd->nEstadosFinais; i++ ) {
    fprintf( arquivo, "\n%s", EstadosFinais[i].nome );
  }

  free(EstadosFinais);

}
