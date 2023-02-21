#include "../headers.h"
#include "afd.h"





/* 1. ESTADOS ------------------------------------------------------- */

/* Retorna o indice onde se encontra o estado_nome no vetor Afd->Estados[] */
int get_estado_IDX(AFD *Afd, char *estado_nome) {

  for ( int i = 0; i < Afd->nEstados; i++ ) {

    if (strcmp(Afd->Estados[i].nome, estado_nome) == 0) { return i; }

  }
  
  printf("\n\t :::: ERRO: <get_estado_IDX()> Estado não encontrado ::::\n");
  exit(EXIT_FAILURE);

};

/* 2. SIMBOLOS ------------------------------------------------------- */

/* Retorna o indice onde se encontra o simbolo_nome no vetor Afd->Simbolos[] */
int get_simboloIDX(AFD *Afd, char *simbolo_nome) {

  for ( int i = 0; i < Afd->nSimbolos; i++ ) {
    // Obs: Acesso ao simbolo [i][0] para comparar char com char
    // Como simbolos possuem tamanho 1 a comparacao sempre sera valida
    if ( Afd->Simbolos[i][0] == simbolo_nome[0] ) { return i; }
    // if (strcmp(Afd->Simbolos[i], simbolo_nome) == 0) { return i; }
  }
  
  printf("\n\t :::: ERRO: <get_simboloIDX()> Simbolo não encontrado ::::\n");
  exit(EXIT_FAILURE);

}

/* 3. TRANSICOES ------------------------------------------------------- */

/**/
Estado get_transicao( AFD *Afd, Estado *estado, char *simbolo ) {
  
  int estado_IDX = get_estado_IDX(Afd, estado->nome);
  int simbolo_IDX = get_simboloIDX(Afd, simbolo);

  int estado_destino_idx = Afd->Transicoes[estado_IDX][simbolo_IDX];

  if ( estado_destino_idx == - 1 ) {
    return transicao_EstadoERRO();
  }
  
  return Afd->Estados[estado_destino_idx];
  
}


void set_transicao(AFD *Afd, char *estadoOrigem, \
                    char *simbolo, char *estadoDestino) {
  
  int estadoOrigem_IDX = get_estado_IDX(Afd, estadoOrigem);
  int estadoDestino_IDX = get_estado_IDX(Afd, estadoDestino);
  int simbolo_IDX = get_simboloIDX(Afd, simbolo);

  Afd->Transicoes[estadoOrigem_IDX][simbolo_IDX] = estadoDestino_IDX;
}

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

Estado transicao_EstadoERRO() {
  Estado EstadoErro;
  
  EstadoErro.Final = 0;
  EstadoErro.Erro = 1;

  return EstadoErro;
}

void Afd_destruct(AFD *Afd) {
  // free todo mundo
  for ( int i = 0; i < Afd->nEstados; i++ ) 
    { free(Afd->Estados[i].nome); }

  for ( int i = 0; i < Afd->nSimbolos; i++ ) 
    { free(Afd->Simbolos[i]); }

  for ( int estado = 0; estado < Afd->nEstados; estado++ ) 
    { free(Afd->Transicoes[estado]); }

  free(Afd->Estados);
  free(Afd->Simbolos);
  free(Afd->Transicoes);
  free(Afd);

}

void Afd_toString(AFD *Afd) {
  
  printf("\n\t :: AFD: <%s> ::\n", Afd->nome);
  
  printf("-> %d Estados\n", Afd->nEstados);
  
  for ( int i = 0; i < Afd->nEstados; i++ ) {    
    printf("\t[%d] %s\n", Afd->Estados[i].ID, Afd->Estados[i].nome ); }

  printf("-> %d Simbolos\n", Afd->nSimbolos);
  
  for ( int i = 0; i < Afd->nSimbolos; i++ ) {    
    printf("\t[%d] %s\n", i, Afd->Simbolos[i] ); }

  printf("-> %d Transicoes\n", Afd->nTransicoes);
  
  for ( int estado = 0; estado < Afd->nEstados; estado++ ) {
    for (int simbolo = 0; simbolo < Afd->nSimbolos; simbolo++) {
      if ( Afd->Transicoes[estado][simbolo] != -1 ) {
        printf("\t(%s,%s): %s\n", \
          Afd->Estados[estado].nome, \
          Afd->Simbolos[simbolo], \
          Afd->Estados[Afd->Transicoes[estado][simbolo]].nome); }
      }
  }

  printf("-> EstadoInicial \n\t %s \n", get_estado_inicial(Afd).nome );

  printf("-> %d EstadosFinais\n", Afd->nEstadosFinais);
  Estado *EstadosFinais = get_estados_final(Afd);
  for (int i = 0; i < Afd->nEstadosFinais; i++) {
    printf("\t[%d] %s\n", EstadosFinais[i].ID, EstadosFinais[i].nome ); }

  free(EstadosFinais);

}
