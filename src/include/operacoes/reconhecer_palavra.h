#ifndef RECONHECER_PALAVRA_H
#define RECONHECER_PALAVRA_H

#include "../headers.h"
#include "../afd/afd.h"
#include "../utils/str_utils.h"

void reconhecer_palavras(AFD *Afd, char *inputFile, char *outputFile);
int reconhece_palavra(AFD *Afd, char *palavra);

#endif
