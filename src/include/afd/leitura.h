#ifndef LEITURA_H
#define LEITURA_H


#include "../headers.h"
#include "afd.h"
#include "../utils/argumentos.h"
#include "../utils/str_utils.h"

AFD *Afd_ler(char *nome_arquivo);
void ler_estados(AFD *Afd, char *linha, FILE *arquivo);
void ler_simbolos(AFD *Afd, char *linha, FILE *arquivo);
void ler_transicoes(AFD *Afd, char *linha, FILE *arquivo);
void ler_estado_inicial(AFD *Afd, char *linha, FILE *arquivo);
void ler_estados_final(AFD *Afd, char *linha, FILE *arquivo);

#endif
