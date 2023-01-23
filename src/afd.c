
#include "constants.h"
#include "afd.h"


void afd_ler(char *nome_arquivo) {  
  
  FILE *arquivo;

  if ( (arquivo = fopen(nome_arquivo, "r")) == NULL) {
    printf("\t ERRO: Arquivo não encontrado: %s\n\n", nome_arquivo);
    return;
  }

  AFD *Afd = inicializar_AFD();
  char linha[MAXCHAR];
  
  /* 1. ESTADOS */
  set_estados(Afd, linha, arquivo);
  /* 2. ALFABETO DE ENTRADA */
  set_simbolos(Afd, linha, arquivo);
  /* 3. TRANSICOES */
  set_transicoes(Afd, linha, arquivo);
  /* 4. ESTADO INICIAL */
  set_estado_inicial(Afd, linha, arquivo);
  /* 5. ESTADO FINAL */
  set_estados_final(Afd, linha, arquivo);

  // teste
  Afd_toString(Afd);

  fclose(arquivo);
  Afd_destruct(Afd); // return afd

}

/* 1. ESTADOS ------------------------------------------------------- */

void set_estados(AFD *Afd, char *linha, FILE *arquivo) {
  
  Afd->nEstados = atoi(fgets(linha, MAXCHAR, arquivo));  

  Afd->Estados = malloc(Afd->nEstados * sizeof(Estado));

  for (int i = 0; i < Afd->nEstados; i++) {

    Estado *estado = malloc(sizeof(Estado));

    char *nome = strtok(fgets(linha, MAXCHAR, arquivo), "\n");

    estado->nome = malloc(MAXCHAR *sizeof(char));
    strcpy(estado->nome, nome);

    estado->ID = i;
    estado->Inicial = 0;
    estado->Final = 0;
    Afd->Estados[i] = *estado;

  }

}

int get_estadoID(AFD *Afd, char *estado_nome) {

  for ( int i = 0; i < Afd->nEstados; i++ ) {

    if (strcmp(Afd->Estados[i].nome, estado_nome) == 0) { return i; }

  }
  
  printf("\n\t :::: ERRO: <get_estadoID()> Estado não encontrado ::::\n");
  exit(EXIT_FAILURE);

};

/* 2. SIMBOLOS ------------------------------------------------------- */

void set_simbolos(AFD *Afd, char *linha, FILE *arquivo) {
  
  Afd->nSimbolos = atoi(fgets(linha, MAXCHAR, arquivo));
  Afd->Simbolos = malloc(Afd->nSimbolos * sizeof(char*));

  for ( int i = 0; i < Afd->nSimbolos; i++ ) {

    char *simbolo = strtok(fgets(linha, MAXCHAR, arquivo), "\n");
    Afd->Simbolos[i] = malloc((strlen(simbolo) + 1) * sizeof(char));

    strcpy(Afd->Simbolos[i], simbolo);
  
  }

}

int get_simboloID(AFD *Afd, char *simbolo_nome) {

  for ( int i = 0; i < Afd->nSimbolos; i++ ) {

    if (strcmp(Afd->Simbolos[i], simbolo_nome) == 0) { return i; }

  }
  
  printf("\n\t :::: ERRO: <get_simboloID()> Simbolo não encontrado ::::\n");
  exit(EXIT_FAILURE);
}

/* 3. TRANSICOES ------------------------------------------------------- */

void set_transicoes(AFD *Afd, char *linha, FILE *arquivo) {

  Afd->nTransicoes = atoi(fgets(linha, MAXCHAR, arquivo));
  
  // Aloca uma matriz de transicoes
  // Os enderecos sao acessados pelos ids dos estados e simbolos
  // Ex: transicao[estadoid][simbolo] == estado_destino
  Afd->Transicoes = malloc(Afd->nEstados * sizeof(int*));  
  
  for( int i = 0; i < Afd->nSimbolos; i++ ) {
    
    Afd->Transicoes[i] = malloc(sizeof(int));
  
  }


  for ( int i = 0; i < Afd->nTransicoes; i++ ) {
    // obtem tupla da transicao:
    // t(origem,simbolo,destino)
    char *transicoes = strtok(fgets(linha, MAXCHAR, arquivo), "\n");

    char *splitStr = strtok(transicoes, " ");
    char **transicao = malloc(3 * sizeof(char*));    
    
    int j = 0;
    while( splitStr != NULL ) {      
      
      transicao[j] = malloc(MAXCHAR * sizeof(char));
      strcpy(transicao[j], splitStr);      
    
      splitStr = strtok(NULL, " ");

      j++;    
    
    }

    // atribui ao AFD a transicao para o estado_id  quando le o simbolo_id
    int estadoOrigem_ID = get_estadoID(Afd, transicao[0]);
    int simbolo_ID = get_simboloID(Afd, transicao[1]);
    int estadoDestino_ID = get_estadoID(Afd, transicao[2]);

    Afd->Transicoes[estadoOrigem_ID][simbolo_ID] = estadoDestino_ID;


  }
  
}

/* 4. ESTADO INICIAL ------------------------------------------------------- */

void set_estado_inicial(AFD *Afd, char *linha, FILE *arquivo) {

  char *nome = strtok(fgets(linha, MAXCHAR, arquivo), "\n");
  
  int estadoInicial_ID = get_estadoID(Afd, nome);

  Afd->Estados[estadoInicial_ID].Inicial = 1;

}

Estado get_estado_inicial(AFD *Afd) {
  
  for ( int i = 0; i < Afd->nEstados; i++ ) {
  
    if ( Afd->Estados[i].Inicial == 1 ) { return Afd->Estados[i]; }
  
  }

  printf("\n\t :::: ERRO: <get_estado_inicial()> Não definido ::::\n");
  exit(EXIT_FAILURE);

}

/* 5. ESTADO FINAL ------------------------------------------------------- */

void set_estados_final(AFD *Afd, char *linha, FILE *arquivo) {
  
  Afd->nEstadosFinais = atoi(fgets(linha, MAXCHAR, arquivo));

  for ( int i = 0; i < Afd->nEstadosFinais; i++ ) {
    
    char *nome = strtok(fgets(linha, MAXCHAR, arquivo), "\n");
  
    int estadoFinal_ID = get_estadoID(Afd, nome);
  
    Afd->Estados[estadoFinal_ID].Final = 1;
  
  }

}

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
  for ( int i = 0; i < Afd->nEstados; i++ ) {
    free(Afd->Estados[i].nome);
  }

  free(Afd->Estados);
  free(Afd->Simbolos);
  free(Afd->Transicoes);
  free(Afd);

}

void Afd_toString(AFD *Afd) {
  
  printf("\n\t :: AFD ::\n");
  
  printf("-> %d Estados\n", Afd->nEstados);
  for (int i=0; i < Afd->nEstados; i++ ) {    
    printf("\t[%d] %s\n", Afd->Estados[i].ID, Afd->Estados[i].nome );}

  printf("-> %d Simbolos\n", Afd->nSimbolos);
  for (int i=0; i < Afd->nSimbolos; i++ ) {    
    printf("\t[%d] %s\n", i, Afd->Simbolos[i] );}

  printf("-> %d Transicoes\n", Afd->nTransicoes);
  for (int i=0; i < Afd->nEstados; i++) {
    for (int j=0; j< Afd->nSimbolos; j++) {
      printf("\t(%d,%d): %d\n", i, j, Afd->Transicoes[i][j]);
    }
  }

  printf("-> EstadoInicial \n\t %s \n", get_estado_inicial(Afd).nome );

  printf("-> %d EstadosFinais\n", Afd->nEstadosFinais);
  Estado *EstadosFinais = get_estados_final(Afd);
  for (int i = 0; i < Afd->nEstadosFinais; i++) {
    printf("\t[%d] %s\n", EstadosFinais[i].ID, EstadosFinais[i].nome );}

  free(EstadosFinais);

}


