
/**
* ------------------------------------------------------------------------------
* Implementa a leitura de AFD a partir de um arquivo "".txt"
* ------------------------------------------------------------------------------
*/

#include "../headers.h"
#include "../utils/argumentos.h"
#include "leitura.h"


/**
* Lê um arquivo .txt
* 
* retorna: struct AFD
*
*/
AFD *Afd_ler(char *nome_arquivo) {  
  
  printf("\n\t :: Ler AFD\n");
  
  FILE *arquivo;
  char *caminho;
  caminho = get_dir_arquivo(nome_arquivo, 0);
  

  if ( (arquivo = fopen(caminho, "r")) == NULL) {
    printf("\n\t :::: ERRO: Arquivo nao encontrado: %s ::::\n", nome_arquivo);
    printf("\n\t\t :: Certifique-se de que o arquivo esta no diretorio: %s \
      \n\n", AFD_INPUT_DIR );

    exit(EXIT_FAILURE);

  }
  
  AFD *Afd = inicializar_AFD();
  Afd->nome = remover_extensao_string(nome_arquivo);


  char linha[MAXCHAR];  
  
  
  
  /* 1. ESTADOS */
  ler_estados(Afd, linha, arquivo);

  /* 2. ALFABETO DE ENTRADA */
  ler_simbolos(Afd, linha, arquivo);

  /* 3. TRANSICOES */
  ler_transicoes(Afd, linha, arquivo);

  /* 4. ESTADO INICIAL */
  ler_estado_inicial(Afd, linha, arquivo);
  
  /* 5. ESTADO FINAL */
  ler_estados_final(Afd, linha, arquivo);

  

  fclose(arquivo);
  free(caminho);

  return Afd;

}

/* 1. ESTADOS ------------------------------------------------------- */

void ler_estados(AFD *Afd, char *linha, FILE *arquivo) {
  
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

/* 2. SIMBOLOS ------------------------------------------------------- */

void ler_simbolos(AFD *Afd, char *linha, FILE *arquivo) {
  
  Afd->nSimbolos = atoi(fgets(linha, MAXCHAR, arquivo));
  Afd->Simbolos = malloc(Afd->nSimbolos * sizeof(char*));

  for ( int i = 0; i < Afd->nSimbolos; i++ ) {

    char *simbolo = strtok(fgets(linha, MAXCHAR, arquivo), "\n");
    Afd->Simbolos[i] = malloc(sizeof(char));
    strcpy(Afd->Simbolos[i], simbolo);
  
  }

}

/* 3. TRANSICOES ------------------------------------------------------- */

void ler_transicoes(AFD *Afd, char *linha, FILE *arquivo) {
  

  Afd->nTransicoes = atoi(fgets(linha, MAXCHAR, arquivo));
  
  /* Aloca uma matriz de transicoes */
  /* Os enderecos sao acessados pelos ids dos estados e simbolos */
  /* Ex: transicao[estadoid][simbolo] = estado_destino */
  Afd->Transicoes = malloc(Afd->nEstados * sizeof(int*));  
  
  /* inicializa transicoes[estado][simbolo] com destino -1 ( vazio )  */
  for( int estado = 0; estado < Afd->nEstados; estado++ ) {
    
    Afd->Transicoes[estado] = malloc(sizeof(int));
    
    for ( int simbolo = 0; simbolo < Afd-> nSimbolos; simbolo++ ) 
      {  Afd->Transicoes[estado][simbolo] = -1; }

  }


  for ( int i = 0; i < Afd->nTransicoes; i++ ) {
    /* obtem tupla da transicao: */
    /* t(origem,simbolo,destino) */
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

    /* atribui ao AFD a transicao para o estado_id  quando le o simbolo_id */
    char *estadoOrigem = transicao[0];
    char *simbolo = transicao[1];
    char *estadoDestino = transicao[2];

    set_transicao(Afd, estadoOrigem, simbolo, estadoDestino);    
    
  }
  
}

/* 4. ESTADO INICIAL ------------------------------------------------------- */

void ler_estado_inicial(AFD *Afd, char *linha, FILE *arquivo) {

  char *nome = strtok(fgets(linha, MAXCHAR, arquivo), "\n");
  
  int estadoInicial_ID = get_estado_IDX(Afd, nome);

  Afd->Estados[estadoInicial_ID].Inicial = 1;

}


/* 5. ESTADO FINAL ------------------------------------------------------- */

void ler_estados_final(AFD *Afd, char *linha, FILE *arquivo) {
  
  Afd->nEstadosFinais = atoi(fgets(linha, MAXCHAR, arquivo));

  for ( int i = 0; i < Afd->nEstadosFinais; i++ ) {
    
    char *nome = strtok(fgets(linha, MAXCHAR, arquivo), "\n");
  
    int estadoFinal_ID = get_estado_IDX(Afd, nome);
  
    Afd->Estados[estadoFinal_ID].Final = 1;
  
  }

}
