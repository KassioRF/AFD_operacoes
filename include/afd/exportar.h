#ifndef EXPORTAR_H
#define EXPORTAR_H

#include "afd.h"

void Afd_exportar(AFD *Afd);
void escrever_estados(AFD *Afd, FILE *arquivo);
void escrever_simbolos(AFD *Afd, FILE *arquivo);
void escrever_transicoes(AFD *Afd, FILE *arquivo);
void escrever_estado_inicial(AFD *Afd, FILE *arquivo);
void escrever_estados_final(AFD *Afd, FILE *arquivo);


#endif