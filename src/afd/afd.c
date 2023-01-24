#include "../headers.h"
#include "afd.h"



/* 1. ESTADOS ------------------------------------------------------- */

int get_estadoID(AFD *Afd, char *estado_nome) {

  for ( int i = 0; i < Afd->nEstados; i++ ) {

    if (strcmp(Afd->Estados[i].nome, estado_nome) == 0) { return i; }

  }
  
  printf("\n\t :::: ERRO: <get_estadoID()> Estado não encontrado ::::\n");
  exit(EXIT_FAILURE);

};

/* 2. SIMBOLOS ------------------------------------------------------- */

int get_simboloID(AFD *Afd, char *simbolo_nome) {

  for ( int i = 0; i < Afd->nSimbolos; i++ ) {

    if (strcmp(Afd->Simbolos[i], simbolo_nome) == 0) { return i; }

  }
  
  printf("\n\t :::: ERRO: <get_simboloID()> Simbolo não encontrado ::::\n");
  exit(EXIT_FAILURE);

}

/* 3. TRANSICOES ------------------------------------------------------- */


/* 4. ESTADO INICIAL ------------------------------------------------------- */

Estado get_estado_inicial(AFD *Afd) {
  
  for ( int i = 0; i < Afd->nEstados; i++ ) {
  
    if ( Afd->Estados[i].Inicial == 1 ) { return Afd->Estados[i]; }
  
  }

  printf("\n\t :::: ERRO: <get_estado_inicial()> Não definido ::::\n");
  exit(EXIT_FAILURE);

}

/* 5. ESTADO FINAL ------------------------------------------------------- */

Estado *get_estados_final(AFD *Afd) {
  
  Estado *EstadosFinais = malloc(Afd->nEstadosFinais * sizeof(Estado));

  int cont = 0;
  
  for ( int i = 0; i < Afd->nEstados; i++ ) {
  
    if ( Afd->Estados[i].Final == 1 ) { 

      EstadosFinais[cont] = Afd->Estados[i];
      cont ++;

    }
  
  }

  return EstadosFinais;
  
}

/* Exportar .dot ------------------------------------------------------- */

/* OUTROS ------------------------------------------------------- */

AFD *inicializar_AFD() {
  
  AFD *Afd = malloc(sizeof(AFD));  

  return Afd;
  
}

void Afd_destruct(AFD *Afd) {
  // free todo mundo
  for ( int i = 0; i < Afd->nEstados; i++ ) 
    { free(Afd->Estados[i].nome); }

  for ( int i = 0; i < Afd->nSimbolos; i++ ) 
    { free(Afd->Simbolos[i]); }

  for ( int i = 0; i < Afd->nEstados; i++ ) 
    { free(Afd->Transicoes[i]); }

  free(Afd->Estados);
  free(Afd->Simbolos);
  free(Afd->Transicoes);
  free(Afd);

}

void Afd_toString(AFD *Afd) {
  
  printf("\n\t :: AFD ::\n");
  
  printf("-> %d Estados\n", Afd->nEstados);
  
  for (int i=0; i < Afd->nEstados; i++ ) {    
    printf("\t[%d] %s\n", Afd->Estados[i].ID, Afd->Estados[i].nome ); }

  printf("-> %d Simbolos\n", Afd->nSimbolos);
  
  for (int i=0; i < Afd->nSimbolos; i++ ) {    
    printf("\t[%d] %s\n", i, Afd->Simbolos[i] ); }

  printf("-> %d Transicoes\n", Afd->nTransicoes);
  
  for (int i=0; i < Afd->nEstados; i++) {
    for (int j=0; j< Afd->nSimbolos; j++) {
      printf("\t(%d,%d): %d\n", i, j, Afd->Transicoes[i][j]); }
  }

  printf("-> EstadoInicial \n\t %s \n", get_estado_inicial(Afd).nome );

  printf("-> %d EstadosFinais\n", Afd->nEstadosFinais);
  Estado *EstadosFinais = get_estados_final(Afd);
  for (int i = 0; i < Afd->nEstadosFinais; i++) {
    printf("\t[%d] %s\n", EstadosFinais[i].ID, EstadosFinais[i].nome ); }

  free(EstadosFinais);

}
