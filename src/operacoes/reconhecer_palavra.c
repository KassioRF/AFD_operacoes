/**
* ------------------------------------------------------------------------------
* Funcionalidade 5: Reconhecimento de palavra
* ------------------------------------------------------------------------------
*/

#include "../utils/argumentos.h"
#include "reconhecer_palavra.h"


/**
  Recebe um arquivo contendo uma ou mais palavras
  Retorna um arquivo indicando se resultado gerado pelo AFD


  Para cada palavra (linha do arquivo)
  Faz a chamada do método: reconhece_palavra();

  Como especificado na proposta do TP;
    No arquivo de saida, p/ cada cada palavra (linha)
    Aponta o resultado
     0 se a palavra nao foi aceita
     1 se a palavra foi aceita


*/
void reconhecer_palavras(AFD *Afd, char *inputFile, char *outputFile) {
  printf("\n\t :: Reconhecer Palavra %s\n", inputFile);

  FILE *arquivo;
  char *caminho;

  caminho = get_dir_arquivo(inputFile, 2);
  
  if ( (arquivo = fopen(caminho, "r")) == NULL) {
    printf("\n\t :::: ERRO: Arquivo nao encontrado: %s ::::\n", inputFile);
    printf("\n\t :::: Certifique-se de que o arquivo esta no diretorio: %s \
      \n\n", PALAVRAS_DIR );

    exit(EXIT_FAILURE);

  }

  char *caminho_saida = get_dir_arquivo(outputFile,3);
  
  FILE *arq_resultado = fopen(caminho_saida, "w");

  char linha[1024];

  // Para cada linha reconhece uma palavra
  while (fgets(linha, 1024, arquivo)) {
    
    int resultado = 0;    
    resultado = reconhece_palavra(Afd, strtok(linha, "\n"));
    
    fprintf(arq_resultado, "%d\n", resultado);

  }

  fprintf(arq_resultado, "AFD: %s", Afd->nome);

  printf("\n\n\t\t - Arquivo de saida: %s \n", caminho_saida);

  fclose(arq_resultado);
  fclose(arquivo);
  

}

/** @TODO: Analise complexidade   
  Lembretes sobre a complexidade:
  
  no while: O(|palavra| * O(get_transicao()) )
  - Para cada s em |palavra| chama get_transicao
  
  em get_transicao(): O(|Estados|+|Simbolos|)
  - 1 ) percorre os Estados do AFD p encontrar id no vetor de estados
  - 2 ) percorre os Simbolos do Alfabeto p encontrar o id no vetor de simbolos
    OBS* 1) e 2) nao sao aninhados
    
  Neste caso temos:
  O(|palavra|*(|E|+|S|))
 */

int reconhece_palavra(AFD *Afd, char *palavra) {
  
  Estado EstadoAtual = get_estado_inicial(Afd);  
  
  char *simbolo = palavra;

  // Caminha pelas transicoes a cada simbolo lido
  while ( *simbolo ) {
    
    /* trata o caso de palavra/simbolo vazio */
    if  (simbolo[0] == ' ')  { 
      simbolo++;
      continue;     
    }
    
    EstadoAtual = get_transicao(Afd, &EstadoAtual, simbolo++); 
  }

  printf("\n");


  printf("\n\t\t - %s (%d)", palavra, EstadoAtual.Final);

  return EstadoAtual.Final;

}