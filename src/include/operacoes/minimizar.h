#ifndef MINIMIZAR_H
#define MINIMIZAR_H

#include "../headers.h"
#include "../afd/afd.h"
#include "../utils/particoes.h"
#include "../utils/str_utils.h"


AFD *minimizar_AFD(AFD *Afd);

/* Trata equivalencias */
void aloca_proxima_equivalencia(VetorEquivalencias* S);
void obtem_primeira_equivalencia(AFD *Afd, VetorEquivalencias* S, int *ref_eP);
int *ref_EstadosParticoes(AFD *Afd, VetorParticao *Particoes);
Particao *particoes_equivalentes(AFD* Afd, Particao* X, int estado, int *ref_EP);
void refina_equivalencia(AFD* Afd, VetorEquivalencias* S, int n );
int compara_vetor_particao(VetorParticao* vp1, VetorParticao* vp2);
int compara_equivalencias(VetorEquivalencias* S, int n );

/* Gera um AFD a partir dos estados agrupados no processode de minimização */
AFD* gerar_AFD_minimizado(AFD *Afd, VetorParticao *S, int *ref_EP );
/* Auxiliares */
void remove_estado(AFD *Afd, int estado_IDX);
void eliminar_inalcancaveis(AFD *Afd);

#endif
