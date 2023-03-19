/******************************************************************************
  BIBLIOTECA AUXILIAR : 

  O objetivo princial desta lib é facilitar a manipulação de conjuntos durante
  o processo de minimização de AFDs.

*******************************************************************************/

#include "particoes.h"

/* Método de inicialização com todos os atributos nulos */
Particao* inicializarParticao() {
  Particao* novaParticao = malloc(sizeof(Particao));
  novaParticao->estados = NULL;
  novaParticao->tamanho = 0;
  return novaParticao;
}

/* Método para adicionar um novo elemento */
void adicionarElemento(Particao* part, int novoEstado) {
  /* Caso o estado já exista na partição não podemos adicionar ele novamente*/
  for (int i = 0; i < part->tamanho; i++) {
    if (part->estados[i] == novoEstado) {
      return;
    }
  }
  part->estados = realloc(part->estados, (part->tamanho + 1) * sizeof(int));
  part->estados[part->tamanho] = novoEstado;
  part->tamanho++;
}

/* Remove o primeiro elemento de uma partição*/
int popParticao(Particao* part) {
  int estado_removido;
  if (part->tamanho == 0) {
    printf("Particao Vazia\n");
    return -1;
  }

  estado_removido = part->estados[0];

  for (int i = 1; i < part->tamanho; i++) {
    part->estados[i-1] = part->estados[i];
  }
  part->tamanho--;

  part->estados = realloc(part->estados, part->tamanho * sizeof(int));

  return estado_removido;
}

/* Retorna Uma partição resultante da diferença entre 2 Particoes */
Particao* diffParticoes(Particao *part1, Particao *part2) {
  Particao *resultado = malloc(sizeof(Particao));
  resultado->tamanho = 0;
  resultado->estados = NULL;

  for(int i = 0; i < part1->tamanho; i++) {
    int elemento = part1->estados[i];
    int encontradoNaPart2 = 0;

    for(int j = 0; j < part2->tamanho; j++) {
      if(part2->estados[j] == elemento) {
        encontradoNaPart2 = 1;
        break;
      }
    }

    if(!encontradoNaPart2) {
      adicionarElemento(resultado, elemento);
    }
  }

  return resultado;
}

/* Liberação da memória alocada para a partição */
void liberarParticao(Particao* part) {
  free(part->estados);
  free(part);
}

void print_Particao(Particao* part) {
  for (int k = 0; k < part->tamanho; k++) {
    printf("%d ", part->estados[k]);
  }  
}

/* Método de inicialização com todos os atributos nulos */
VetorParticao* inicializarVetorParticao() {
  
  VetorParticao* novoVetorParticao = malloc(sizeof(VetorParticao));
  novoVetorParticao->particao = NULL;
  novoVetorParticao->tamanho = 0;
  
  return novoVetorParticao;
}


/* Método para adicionar um novo elemento */
void adicionarParticao(VetorParticao* vetPart, Particao novaPart) {
  vetPart->particao = realloc(vetPart->particao, (vetPart->tamanho + 1) * sizeof(Particao));
  vetPart->particao[vetPart->tamanho] = novaPart;
  vetPart->tamanho++;
}


/* Método para liberar a memória */
void liberarVetorParticao(VetorParticao* vetPart) {
  for (int i = 0; i < vetPart->tamanho; i++) {
    free(vetPart->particao[i].estados);
  } 
  free(vetPart->particao);
  /* free(vetPart); */
}

void print_VetorParticao(VetorParticao* vetPart) {
  for (int i = 0; i < vetPart->tamanho; i++) {
    printf("[ ");
    print_Particao(&vetPart->particao[i]);
    printf("] ");
  }
}

/* Método de inicialização com todos os atributos nulos */
VetorEquivalencias* inicializarVetorEquivalencias() {
  VetorEquivalencias* novoVetorEquivalencias = malloc(sizeof(VetorEquivalencias));
  novoVetorEquivalencias->vetorParticao = NULL;
  novoVetorEquivalencias->tamanho = 0;
  return novoVetorEquivalencias;
}

/* Adiciona um subconjunto ao Vetor vetEq */
void adicionarVetorParticao(VetorEquivalencias* vetEq, VetorParticao novoVetorPart) {
  vetEq->vetorParticao = realloc(vetEq->vetorParticao, (vetEq->tamanho + 1) * sizeof(VetorParticao));
  vetEq->vetorParticao[vetEq->tamanho] = novoVetorPart;
  vetEq->tamanho++;
}


/* Método para liberar a memória */
void liberarVetorEquivalencias(VetorEquivalencias* vetEq) {
  for (int i = 0; i < vetEq->tamanho; i++) {
    for (int j = 0; j < vetEq->vetorParticao[i].tamanho; j++) {
      free(vetEq->vetorParticao[i].particao[j].estados);
    }
    free(vetEq->vetorParticao[i].particao);
  }
  free(vetEq->vetorParticao);
  // free(vetEq);
}

void print_VetorEquivalencias(VetorEquivalencias* vetEq) {
  for (int i = 0; i < vetEq->tamanho; i++) {
    printf("[ ");
    print_VetorParticao(&vetEq->vetorParticao[i]);
    printf("]\n");
  }
}


/*******************************************************************************
COPIAS
*******************************************************************************/
/* Método para copiar uma partição */
void copia_Particao(Particao* destino, Particao origem) {
  destino->estados = malloc(origem.tamanho * sizeof(int));
  memcpy(destino->estados, origem.estados, origem.tamanho * sizeof(int));
  destino->tamanho = origem.tamanho;
}

