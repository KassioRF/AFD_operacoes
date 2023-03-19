#ifndef AFD_H
#define AFD_H

/** Estrutura para o AFD */
typedef struct Estado_struct {
  char *nome;
  int ID;
  int Inicial;
  int Final;
  // Marca como o estado de erro do AFD
  int Erro; 
  
} Estado;


typedef struct AFD_struct {
  char *nome;
  Estado *Estados;
  char **Simbolos;
  int **Transicoes;

  int nEstados;
  int nSimbolos;
  int nTransicoes;
  int nEstadosFinais;

} AFD;

/** Metodos: */
AFD *inicializar_AFD();
int get_estado_IDX(AFD *Afd, char *estado_nome);
int get_simboloIDX(AFD *Afd, char *simbolo_nome);
Estado get_estado_inicial(AFD *Afd);
Estado *get_estados_final(AFD *Afd);

Estado get_transicao( AFD *Afd, Estado *estado, char *simbolo );

void set_transicao(AFD *Afd, char *estadoOrigem, \
                    char *simbolo, char *estadoDestino);

Estado transicao_EstadoERRO();
void Afd_destruct(AFD *Afd);
void Afd_toString(AFD *Afd);

#endif
