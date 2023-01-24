#ifndef AFD_H
#define AFD_H

/** Estrutura para o AFD */
typedef struct Estado_struct {
  char *nome;
  int ID;
  int Inicial;
  int Final;

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
int get_estadoID(AFD *Afd, char *estado_nome);
int get_simboloID(AFD *Afd, char *simbolo_nome);
Estado get_estado_inicial(AFD *Afd);
Estado *get_estados_final(AFD *Afd);

void Afd_destruct(AFD *Afd);
void Afd_toString(AFD *Afd);

#endif
