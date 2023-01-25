#ifndef OPERACOES_H
#define OPERACOES_H
#include "../headers.h"
#include "../afd/afd.h"


void operacoes();


/* ===== FUNCIONALIDADE 2: Complemento =====*/
void complemento();

/* ===== FUNCIONALIDADE 3: Intersecao e Uniao =====*/
void produto();
void uniao();
void intersecao();

/* ===== FUNCIONALIDADE 4: Minimizacao =====*/
void minimizar();

/* ===== FUNCIONALIDADE 5: Reconhecer Palavra =====*/
void reconhecer_palavras(AFD *Afd, char *nome_arq_entrada);
int reconhece_palavra(AFD *Afd, char *palavra);

#endif
