
/**
* ------------------------------------------------------------------------------
* Implementa a escrita de AFD no formato .dot aceito pelo Graphiz
* ------------------------------------------------------------------------------
*/

#include "../headers.h"
#include "../utils/argumentos.h"
#include "exportar.h"

/** Exporta um arquivo .dot  no formato graphiz a partir de um AFD de entrada. */

void Afd_exportar(AFD *Afd) {
  
  printf("\n\t :: Exportar AFD.dot ::\n");
  
  char *caminho;
  caminho = get_dir_arquivo(Afd->nome, 1);

  FILE *arquivo;

  if ( (arquivo = fopen(caminho, "w")) == NULL ) {
    printf("\t :::: ERRO: Arquivo ao criar arquivo de saida: %s ::::\n", caminho);
    exit(EXIT_FAILURE);
  }


  write_graphiz_format(Afd, arquivo);


  fclose(arquivo);
  printf("\t\t - Arquivo de saida:  %s \n", caminho);

}

/* Auxiliares: ---------------------------------------------------------------*/

/** Escreve no arquivo os parâmetros do afd.dot. */

void write_graphiz_format(AFD *Afd, FILE *arquivo) {
  /* Abre o bloco da estrutura digraph: */
  fprintf( arquivo, "digraph AFD { \n" );
  
  /* parâmetro para a direção das arestas/vértices.*/
  fprintf( arquivo, "\trankdir=LR; \n" );

  /* vértice genérico p/ marcar a seta do estado inicial*/
  fprintf( arquivo, "\tnode [ shape = point ]; _qi;\n" );
  /* define o shape para os demais estados ( oval ) */
  fprintf( arquivo, "\tnode [ shape = oval ];\n" );
  
  /* define as transições no diagrama */
  escrever_transicoes(Afd, arquivo);

  /* define os estaods finais */
  escrever_estados_final(Afd, arquivo);
  
  /* Fecha o bloco da estrutura digraph: */
  fprintf( arquivo, "}" );

}

void escrever_transicoes(AFD *Afd, FILE *arquivo) {
  
  fprintf( arquivo, "\t// transicoes \n" );  
  
  /* especifica seta para o estdo inicial */
  fprintf( arquivo, "\t_qi -> %s;\n", get_estado_inicial(Afd).nome );
    
  /* Transições: */
  for ( int estado = 0; estado < Afd->nEstados; estado++ ) {
    for ( int simbolo = 0; simbolo < Afd->nSimbolos; simbolo++ ) {
      
      if ( Afd->Transicoes[estado][simbolo] != -1 ) { 

        fprintf( arquivo, "\t%s -> %s [ label = \"%s\" ];\n", \
          Afd->Estados[estado].nome, \
          Afd->Estados[Afd->Transicoes[estado][simbolo]].nome, \
          Afd->Simbolos[simbolo] );
      }  
    }    
  }

}


void escrever_estados_final(AFD *Afd, FILE *arquivo) {
  fprintf( arquivo, "\t// Estados Finais \n" );
  
  Estado *EstadosFinais = get_estados_final(Afd);
  
  for (int i = 0; i < Afd->nEstadosFinais; i++ ) {
    fprintf( arquivo, "\t%s [ shape = \"doublecircle\"]; \n", \
      EstadosFinais[i].nome );
  }

  free(EstadosFinais);

}
