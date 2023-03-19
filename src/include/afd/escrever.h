#ifndef ESCREVER_H
#define ESCREVER_H

#include "../headers.h"
#include "../utils/str_utils.h"
#include "afd.h"

void Afd_escrever(AFD *Afd, char *nome_arquivo);

void escrever_estados(AFD *Afd, FILE *arquivo);
void escrever_simbolos(AFD *Afd, FILE *arquivo);
void escrever_transicoes(AFD *Afd, FILE *arquivo);
void escrever_estado_inicial(AFD *Afd, FILE *arquivo);
void escrever_estados_final(AFD *Afd, FILE *arquivo);

#endif