#ifndef PARTICOES_H
#define PARTICOES_H

/******************************************************************************
  BIBLIOTECA AUXILIAR : 

  O objetivo princial desta lib é facilitar a manipulação de conjuntos durante
  o processo de minimização de AFDs.

*******************************************************************************/
#include "../headers.h"

/*******************************************************************************
  STRUCT PARTICOES
*******************************************************************************/
typedef struct {
  int* estados;
  int tamanho;
} Particao;

typedef struct {
  Particao* particao;
  int tamanho;
} VetorParticao;

typedef struct {
  VetorParticao* vetorParticao;
  int tamanho;
} VetorEquivalencias;

/*******************************************************************************
  FUNCOES
*******************************************************************************/
/* Particoes */
Particao* inicializarParticao();
void adicionarElemento(Particao* part, int novoEstado);
int popParticao(Particao* part);
Particao* diffParticoes(Particao *part1, Particao *part2);
void liberarParticao(Particao* part);
void print_Particao(Particao* part);

/* VetorParticao */
VetorParticao* inicializarVetorParticao();
void adicionarParticao(VetorParticao* vetPart, Particao novaPart);
void liberarVetorParticao(VetorParticao* vetPart);
void print_VetorParticao(VetorParticao* vetPart);

/* VetorEquivalencias */
VetorEquivalencias* inicializarVetorEquivalencias();
void adicionarVetorParticao(VetorEquivalencias* vetEq, VetorParticao novoVetorPart);
void liberarVetorEquivalencias(VetorEquivalencias* vetEq);
void print_VetorEquivalencias(VetorEquivalencias* vetEq);

/* Métodos de Copia */
void copia_Particao(Particao* destino, Particao origem);


#endif

