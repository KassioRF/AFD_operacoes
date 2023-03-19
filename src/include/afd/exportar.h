#ifndef EXPORTAR_H
#define EXPORTAR_H

#include "../headers.h"
#include "../utils/argumentos.h"
#include "../utils/str_utils.h"
#include "afd.h"

void Afd_exportar(AFD *Afd, char* nome_arquivo);
void write_graphiz_format(AFD *Afd, FILE *arquivo);
void exportar_transicoes(AFD *Afd, FILE *arquivo);
void exportar_estados_final(AFD *Afd, FILE *arquivo);


#endif