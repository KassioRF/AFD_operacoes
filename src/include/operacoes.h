#ifndef OPERACOES_H
#define OPERACOES_H

#include "headers.h"
#include "utils/str_utils.h"
#include "afd/afd.h"

#include "afd/leitura.h"
#include "afd/exportar.h"
#include "afd/escrever.h"

#include "operacoes/reconhecer_palavra.h"
#include "operacoes/minimizar.h"
#include "operacoes/complemento.h"


void op_exportarDOT(char* inputFile, char* outputFile);
void op_complemento(char* inputFile, char* outputFile);
void op_minimizar(char* inputFile, char* outputFile);
void op_reconhecer_palavra(char* inputAFD, char* inputFile, char* outputFile);

#endif
