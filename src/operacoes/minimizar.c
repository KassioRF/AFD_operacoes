
/**
* ------------------------------------------------------------------------------
* Funcionalidade 4: Minimização de AFDs
* ------------------------------------------------------------------------------
*/

#include "operacoes.h"


/*******************************************************************************
MINIMIZACAO - AUXILIARES
*******************************************************************************/

/**
 * Remove um estado do AFD, atualizando os dados do AFD.
 **/
void remove_estado(AFD *Afd, int estado_IDX) {
  // atualiza o tamanho dos vetores afetados do AFD
  if (Afd->Estados[estado_IDX].Final == 1 ) {
    Afd->nEstadosFinais --;
  }
  
  Afd->nEstados--;
  Afd->nTransicoes -= Afd->nSimbolos;

  // libera a memória alocada para o estado removido
  free(Afd->Estados[estado_IDX].nome);
  free(Afd->Transicoes[estado_IDX]);

  // desloca os estados e simbolos para trás, sobreescrevendo o estado removido
  for (int e = estado_IDX; e < Afd->nEstados; e++) {
    Afd->Estados[e] = Afd->Estados[e + 1];
    Afd->Transicoes[e] = Afd->Transicoes[e + 1];
  }

  // realoca o vetor temporário de transições
  int **temp_trans = (int **)malloc(sizeof(int *) * Afd->nEstados);
  for (int i = 0; i < Afd->nEstados; i++) {
    temp_trans[i] = (int *)malloc(sizeof(int) * Afd->nSimbolos);
    for (int j = 0; j < Afd->nSimbolos; j++) {
       temp_trans[i][j] = Afd->Transicoes[i][j];
    }
  }
  // libera a matriz original das transições 
  free(Afd->Transicoes);

  // atribui o vetor da matriz das transições para o temporário
  Afd->Transicoes = temp_trans;

  // atualiza os índices das transições baseados no deslocamento dos estados 
  for (int i = 0; i < Afd->nEstados; i++) {
    for (int j = 0; j < Afd->nSimbolos; j++) {
      if (Afd->Transicoes[i][j] > estado_IDX) {
        Afd->Transicoes[i][j]--;
      }
    }
  }
}
/*******************************************************************************/
/**
* Identifica os estados inalcançáveis no afd
* 
* Descrição do método:
* 
* 1) Declara uma lista `Alc` onde cada índice representa um estado.
*   Para cada valor da lista é considerado o seguinte:
*     se o estado é alcançável 1
*     se não -1.
*
* 2) Alc é inicializado com -1 para todos os estados;
* 3) Percorre todas as transições onde, 
    para cada &(e,s): e' marca Alc[e'] como alcançável.

* 4) Percorre Alc para obter os inalcançáveis.
* 5) Remove os inalcançáveis do AFD.
*/
void eliminar_inalcancaveis(AFD *Afd) {
  // inicializa visitados com -1
  int Alc[Afd->nEstados];
  memset(Alc, -1, sizeof(Alc));

  /* Marca os estados visitados em Alc */
  for (int e = 0; e < Afd->nEstados; e++ ) {
    for (int s = 0; s < Afd->nSimbolos; s++) {
      //acessa resultado da transição :: &(e,s): e'
      int e_ = Afd->Transicoes[e][s];
      Alc[e_] = 1;
    }
  }

  /* Remove do AFD os estados em Alc que não foram alcançados */
  for (int e = 0; e < Afd->nEstados; e++) {
    if (Alc[e] == - 1) {
      if (Afd->Estados[e].Inicial != 1) {
        remove_estado(Afd, e);
      }
    }
  }

}

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


// Método de inicialização com todos os atributos nulos
Particao* inicializarParticao() {
    Particao* novaParticao = malloc(sizeof(Particao));
    novaParticao->estados = NULL;
    novaParticao->tamanho = 0;
    return novaParticao;
}

// Método para adicionar um novo elemento
void adicionarElemento(Particao* part, int novoEstado) {
    /* Caso o estado já exista na partição não podemos adicionar ele novamente*/
    for (int i = 0; i < part->tamanho; i++) {
      if (part->estados[i] == novoEstado) {
        return;
      }
    }
    part->estados = realloc(part->estados, (part->tamanho + 1) * sizeof(int));
    part->estados[part->tamanho] = novoEstado;
    part->tamanho++;
}


int popParticao(Particao* part) {
    int estado_removido;
    if (part->tamanho == 0) {
        printf("Particao Vazia\n");
        return -1;
    }

    estado_removido = part->estados[0];

    for (int i = 1; i < part->tamanho; i++) {
        part->estados[i-1] = part->estados[i];
    }
    part->tamanho--;

    part->estados = realloc(part->estados, part->tamanho * sizeof(int));

    return estado_removido;
}

/* Retorna Uma partição resultante da diferença entre 2 Particoes */
Particao* diffParticoes(Particao *part1, Particao *part2) {
  Particao *resultado = malloc(sizeof(Particao));
  resultado->tamanho = 0;
  resultado->estados = NULL;

  for(int i = 0; i < part1->tamanho; i++) {
    int elemento = part1->estados[i];
    int encontradoNaPart2 = 0;

    for(int j = 0; j < part2->tamanho; j++) {
      if(part2->estados[j] == elemento) {
        encontradoNaPart2 = 1;
        break;
      }
    }

    if(!encontradoNaPart2) {
      adicionarElemento(resultado, elemento);
    }
  }

  return resultado;
}

// Método para liberar a memória
void liberarParticao(Particao* part) {
    free(part->estados);
    free(part);
}

void print_Particao(Particao* part) {
    for (int k = 0; k < part->tamanho; k++) {
        printf("%d ", part->estados[k]);
    }  
}

// Método de inicialização com todos os atributos nulos
VetorParticao* inicializarVetorParticao() {
    VetorParticao* novoVetorParticao = malloc(sizeof(VetorParticao));
    novoVetorParticao->particao = NULL;
    novoVetorParticao->tamanho = 0;
    return novoVetorParticao;
}


// Método para adicionar um novo elemento
void adicionarParticao(VetorParticao* vetPart, Particao novaPart) {
    vetPart->particao = realloc(vetPart->particao, (vetPart->tamanho + 1) * sizeof(Particao));
    vetPart->particao[vetPart->tamanho] = novaPart;
    vetPart->tamanho++;
}


// Método para liberar a memória
void liberarVetorParticao(VetorParticao* vetPart) {
     for (int i = 0; i < vetPart->tamanho; i++) {
        free(vetPart->particao[i].estados);
    } 
    free(vetPart->particao);
    // free(vetPart);
}

void print_VetorParticao(VetorParticao* vetPart) {
    for (int i = 0; i < vetPart->tamanho; i++) {
        printf("[ ");
        print_Particao(&vetPart->particao[i]);
        printf("] ");
    }
}

// Método de inicialização com todos os atributos nulos
VetorEquivalencias* inicializarVetorEquivalencias() {
    VetorEquivalencias* novoVetorEquivalencias = malloc(sizeof(VetorEquivalencias));
    novoVetorEquivalencias->vetorParticao = NULL;
    novoVetorEquivalencias->tamanho = 0;
    return novoVetorEquivalencias;
}


// Método para adicionar um novo elemento
void adicionarVetorParticao(VetorEquivalencias* vetEq, VetorParticao novoVetorPart) {
    vetEq->vetorParticao = realloc(vetEq->vetorParticao, (vetEq->tamanho + 1) * sizeof(VetorParticao));
    vetEq->vetorParticao[vetEq->tamanho] = novoVetorPart;
    vetEq->tamanho++;
}


// Método para liberar a memória
void liberarVetorEquivalencias(VetorEquivalencias* vetEq) {
    for (int i = 0; i < vetEq->tamanho; i++) {
        for (int j = 0; j < vetEq->vetorParticao[i].tamanho; j++) {
            free(vetEq->vetorParticao[i].particao[j].estados);
        }
        free(vetEq->vetorParticao[i].particao);
    }
    free(vetEq->vetorParticao);
    // free(vetEq);
}

void print_VetorEquivalencias(VetorEquivalencias* vetEq) {
  for (int i = 0; i < vetEq->tamanho; i++) {
      printf("[ ");
      print_VetorParticao(&vetEq->vetorParticao[i]);
      printf("]\n");
  }
}


/*******************************************************************************
COPIAS
*******************************************************************************/
/* Método para copiar uma partição */
void copia_Particao(Particao* destino, Particao origem) {
    destino->estados = malloc(origem.tamanho * sizeof(int));
    memcpy(destino->estados, origem.estados, origem.tamanho * sizeof(int));
    destino->tamanho = origem.tamanho;
}
/*******************************************************************************
Trata as equivalencias
*******************************************************************************/
void aloca_proxima_equivalencia(VetorEquivalencias* S) {
  Particao p = *inicializarParticao();
  VetorParticao vp = *inicializarVetorParticao();

  adicionarParticao(&vp, p);
  adicionarVetorParticao(S, vp);

}

void obtem_primeira_equivalencia(AFD *Afd, VetorEquivalencias* S, int *ref_eP) {
  Particao pF = *inicializarParticao();
  Particao pNF = *inicializarParticao();
  VetorParticao vp = *inicializarVetorParticao();

  for (int e = 0; e < Afd->nEstados; e++) {
    if (Afd->Estados[e].Final == 1) {
      adicionarElemento( ( Afd->Estados[e].Final == 1 ? &pF : &pNF ), e);
      ref_eP[e] = 1; // referencia do endereco da particao para o estado "e"
    
    }else {
      adicionarElemento( ( Afd->Estados[e].Final == 1 ? &pF : &pNF ), e);
      ref_eP[e] = 0; // referencia do endereco da particao para o estado "e";
    }    
    // adicionarElemento( ( Afd->Estados[e].Final == 1 ? &pF : &pNF ), e);
  }
  
  adicionarParticao(&vp, pNF);
  adicionarParticao(&vp, pF);
  adicionarVetorParticao(S, vp);

}

/* Endereça para cada estado a partição a qual ele dado um vetor de partições */
int *ref_EstadosParticoes(AFD *Afd, VetorParticao *Particoes) {
  int *ref_EP = malloc(Afd->nEstados * sizeof(int*));
  memset(ref_EP, -1, Afd->nEstados * sizeof(int));

  for (int i = 0; i < Particoes->tamanho; i++) {
    for (int e = 0; e < Particoes->particao[i].tamanho; e++) {
      ref_EP[Particoes->particao[i].estados[e]] = i;
    }
  }

  return ref_EP;

}
/* Dado um estado verifica se as transicoes são equivalentes com a particao em X

  int *ref_EP: Faz referencia a qual particao cada estado e pertence atualmente.
 */
Particao *particoes_equivalentes(AFD* Afd, Particao* X, int estado, int *ref_EP) {
  // printf("\n Verificar Equivalencia e: %d \n", estado);
  Particao* Y = inicializarParticao();
  adicionarElemento(Y, estado);
  for ( int e = 0; e < X->tamanho; e++ ){
    
    // avalia a transicao de cada simbolo para os estados e, e'.
    int avaliacao = 1; // assume que as equivalencias são iguais
    for (int s = 0; s < Afd->nSimbolos; s++) {
     
      int tr_e0 = Afd->Transicoes[estado][s]; // resultado transicao de e
      int tr_e1 = Afd->Transicoes[X->estados[e]][s]; //resultado transicao de e'

      // printf(" --- &(%d,%d):%d  %d==%d &(%d,%d):%d \n", \
      //   estado, s, Afd->Transicoes[estado][s], ref_EP[tr_e0],\
      //   ref_EP[tr_e1], X->estados[e], s, Afd->Transicoes[X->estados[e]][s]);

      if ( ref_EP[tr_e0] != ref_EP[tr_e1] ) { 
        // se falha para pelo menos 1 simbolo já quebra a equivalencia
        avaliacao = 0; 
        break; 
      }

      // printf(" -- e %d == %d / ei %d == %d \n", \
      //   estado, ref_EP[tr_e0], \
      //   e, ref_EP[tr_e1] );
    }

    // se transicoes de e, e' forem equivalentes Y adiciona e'
    if (avaliacao == 1) {
      // printf("VAMOS ADICIONAR:{%d} %d\n", estado, X->estados[e]);
      adicionarElemento(Y, X->estados[e]);
    }

  }

  return Y;
}

void refina_equivalencia(AFD* Afd, VetorEquivalencias* S, int n ) {
  printf("\n Refinar Equivalencia: S: %d \n", S->tamanho);

  VetorParticao* novaEQ = inicializarVetorParticao();
  int *ref_EP = ref_EstadosParticoes(Afd, &S->vetorParticao[n-1]);

  for (int i = 0; i < S->vetorParticao[n-1].tamanho; i++) {
    
    // Copia a partição i para X
    Particao* X = inicializarParticao();
    copia_Particao(X, S->vetorParticao[n-1].particao[i]);
    
    // selecione um estado e \in X
    while(X->tamanho > 0) {
      
      int estado = popParticao(X);      
      
      Particao* Y = particoes_equivalentes(Afd, X, estado, ref_EP);      
      
      X = diffParticoes(X, Y); /* X = X - Y*/
      
      adicionarParticao(novaEQ, *Y);
      
    }

    liberarParticao(X);
    
  }  

  // Atribui à S a equivalencia n Refinada;
  S->vetorParticao[n] = *novaEQ;
  
  free(ref_EP);

}

int compara_vetor_particao(VetorParticao* vp1, VetorParticao* vp2){
  //verifica se os vetores tem o mesmo tamanho
  if(vp1->tamanho != vp2->tamanho){ 
    return -1;
  }

  //verifica se a partição tem o mesmo tamanho
  for(int i=0; i < vp1->tamanho; i++){
    if(vp1->particao[i].tamanho != vp2->particao[i].tamanho){ 
      return -1;
    }    
  
    //comparando os estados
    for(int j=0; j < vp1->particao[i].tamanho; j++){ 
      if(vp1->particao[i].estados[j] != vp2->particao[i].estados[j]){
        return -1;
      }
    }
  }

  return 1;
}

int compara_equivalencias(VetorEquivalencias* S, int n ) {
  printf("\nCompara equivalencias\n");
  if (n < 1) 
    { return -1; }

  if ( S->vetorParticao[n].tamanho != S->vetorParticao[n - 1].tamanho)
    { return -1; }



  return compara_vetor_particao(&S->vetorParticao[n], &S->vetorParticao[n-1]);
}

/*******************************************************************************
MINIMIZACAO
*******************************************************************************/
/* Converte um vetor de inteiros em string
  Ex: int: [1,2,3,4]
    retorna  str: 1,2,3,4
*/

char* vInt_ToStr(int vetor[], int tam) {
  char* str = malloc(10*tam*sizeof(char)); 
  int pos_str = 0; 
  int i;

  // percorre todos os elementos do vetor menos o último
  for (i = 0; i < tam-1; i++) {     
    pos_str += sprintf(&str[pos_str], "%d,", vetor[i]); 
  }
  //imprimir o ultimo elemento sem virgula
  sprintf(&str[pos_str], "%d", vetor[tam-1]); 

  return str;
}

/* Recebe um vetor com as partições que agrupa os Estados do processo de minimização
  Retorna uma Struc AFD com o AFD minimizado
*/
AFD* _gerar_AFD_minimizado(AFD *Afd, VetorParticao *S, int *ref_EP ) {
  printf("\n 4 - Gerar AFD Minimizado TESTE\n");
  AFD *AfdMin = inicializar_AFD();
  print_VetorParticao(S);
  return AfdMin;

}
AFD* gerar_AFD_minimizado(AFD *Afd, VetorParticao *S, int *ref_EP ) {
  printf("\n 4 - Gerar AFD Minimizado \n");
  AFD *AfdMin = inicializar_AFD();

  
  /* Atribui um nome com sufixo _min para o AFD minimizado*/
  AfdMin->nome = malloc(50*sizeof(char));
  strcpy(AfdMin->nome, Afd->nome);
  char *sufix = "_min";
  strcat(AfdMin->nome, sufix);

  /* 1. Definir os estados */
  AfdMin->nEstados = S->tamanho;
  AfdMin->Estados = malloc(AfdMin->nEstados * sizeof(Estado));

  for (int i=0; i<AfdMin->nEstados; i++) {
    Estado *estado = malloc(sizeof(Estado));
    char *eNome = vInt_ToStr(S->particao[i].estados, S->particao[i].tamanho );
    estado->nome = malloc(MAXCHAR *sizeof(char));
    strcpy(estado->nome, eNome);

    estado->ID = i;
    estado->Inicial = 0;
    estado->Final = 0;
    AfdMin->Estados[i] = *estado;

  }

  /* 2. Definir os simbolos */
  
  AfdMin->nSimbolos = Afd->nSimbolos;
  AfdMin->Simbolos = malloc(AfdMin->nSimbolos * sizeof(char*));
  
  for ( int i = 0; i < AfdMin->nSimbolos; i++ ) {
    char *simbolo = Afd->Simbolos[i];
    AfdMin->Simbolos[i] = malloc(sizeof(char));
    strcpy(AfdMin->Simbolos[i], simbolo);  
  }
  
  /* 3. Definir Transições */
  /* Aloca uma matriz de transicoes */
  /* Os enderecos sao acessados pelos ids dos estados e simbolos */
  /* Ex: transicao[estadoid][simbolo] = estado_destino */
  AfdMin->nTransicoes = AfdMin->nEstados * AfdMin->nSimbolos;
  AfdMin->Transicoes = malloc(AfdMin->nEstados * sizeof(int*));  
  

  /* inicializa transicoes[estado][simbolo] com destino -1 ( vazio )  */
  for( int estado = 0; estado < AfdMin->nEstados; estado++ ) {
    
    AfdMin->Transicoes[estado] = malloc(sizeof(int));
    
    for ( int simbolo = 0; simbolo < AfdMin->nSimbolos; simbolo++ ) 
      {  AfdMin->Transicoes[estado][simbolo] = -2; }

  }
  printf(" - Partições: \n");
  /* Preenche as transições
    Note que é utilizado ref_EP que endereça para cada estado
    do AFD original seu respectivo estado (agrupado) no AFD minimizado
  */

  for (int e = 0; e < Afd->nEstados; e++ ) {
    for (int s = 0; s < Afd->nSimbolos; s++) {      
      /* Para cada transicao no AFD orignal 
        Adiciona a respectiva transicao para o AFD minimizado
      */
      int destino = Afd->Transicoes[e][s];
      AfdMin->Transicoes[ref_EP[e]][s] = ref_EP[destino];    
    }
  }

  /* 4. Definir Estado inicial */
  for (int i = 0; i < S->tamanho; i++) {
    for (int e = 0; e < S->particao[i].tamanho; e++) {
      // printf("%d \n", S->particao[i].estados[e]);
      
      int estado_ = S->particao[i].estados[e];
      /* Verifica se algum estado dentro da partição S é inicial
        Se sim atribui o estado incial para o estado i de AfdMin
      */
      if (Afd->Estados[estado_].Inicial == 1) {
        AfdMin->Estados[i].Inicial = 1;        
      }
    
    }
  }

  /* 5. Definir Estados Finais */
  for (int i = 0; i < S->tamanho; i++) {
    int encontrou_final = 0;
    for (int e = 0; e < S->particao[i].tamanho; e++) {
      // printf("%d \n", S->particao[i].estados[e]);
      
      int estado_ = S->particao[i].estados[e];
      /* Verifica se algum estado dentro da partição S é inicial
        Se sim atribui o estado incial para o estado i de AfdMin
      */
      if (Afd->Estados[estado_].Final == 1) {
        AfdMin->Estados[i].Final = 1;
        encontrou_final = 1;
      }
    
    }
    if (encontrou_final == 1) {
      AfdMin->nEstadosFinais++;
    }
  }

  return AfdMin;
  // Afd_toString(AfdMin);
  // Afd_destruct(AfdMin);
}

AFD *minimizar_AFD(AFD *Afd) {
  
  printf("\n\t ----  MINIMIZACAO ---- \n");
  printf("\n 1 - Elimina inalcancaveis \n");
  eliminar_inalcancaveis(Afd);

  printf("\n 2 - Inicializa classes equivalencia \n");
  
  // guarda o endereço da particao para cada estado
  // inicialmentente não estão relacionados com nenhuma partição
  int ref_estado_part[Afd->nEstados];
  memset(ref_estado_part, -1, Afd->nEstados * sizeof(int)); 
  
  // inicializao do vetor de equivalencias
  VetorEquivalencias S = *inicializarVetorEquivalencias();
  obtem_primeira_equivalencia(Afd, &S, ref_estado_part);
  
  printf("\n 3 - Looping de Refinamento \n");
  print_VetorEquivalencias(&S);
  /**************************************************/
  /* Procedimento princial: Refinado as equivalencias */
  int n = 0;  
  do {
      
    n++;
    aloca_proxima_equivalencia(&S);
    refina_equivalencia(Afd, &S, n);
    
  } while(compara_equivalencias(&S, n) == - 1);
  /**************************************************/

  print_VetorEquivalencias(&S);

  /* Gerar O AFD minimizado */
  int *ref_EP = ref_EstadosParticoes(Afd, &S.vetorParticao[n]);

  return gerar_AFD_minimizado(Afd, &S.vetorParticao[n], ref_EP);

}




