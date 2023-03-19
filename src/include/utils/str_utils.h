#ifndef STR_UTILS_H
#define STR_UTILS_H
/*******************************************************************************
  FERRAMENTAS PARA MANIPULAÇÂO DE STRINGS
*******************************************************************************/
#include "../headers.h"

char* vInt_ToStr(int vetor[], int tam);
char* get_dir_arquivo(char *nome_arquivo, int tipo);
char* remover_extensao_string(char* str);

#endif
