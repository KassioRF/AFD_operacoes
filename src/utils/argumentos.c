
#include "../headers.h"
#include "argumentos.h"


// /* ========================================================================== */
// /** 
// * Implementa os metodos auxiliares para leitura e escrita arquivos.
// */

// /** Concatena a string do diretorio de entrada com o nome do arquivo de entrada.
// * O inteiro "tipo" especifica qual diretorio deve ser adicionado 
// * antes do nome do arquivo:
// *
// * @param tipo:
// *         0 : Para AFD de entrada
// *         1 : Para AFD de saida
// *         2 : Para Palavra de entrada 
// *         3 : Para Palavra de saida
// */

// char *get_dir_arquivo(char *nome_arquivo, int tipo) {
//   char *caminho_arquivo = (char*)malloc(MAXCHAR*sizeof(char));
//   char *copia_nome_arquivo = strdup(nome_arquivo); 
  
//   if (tipo == 0) 
//     { strcpy(caminho_arquivo, AFD_INPUT_DIR); }

//   else if (tipo == 1) { 
//     strcat(copia_nome_arquivo, ".dot");  
//     strcpy(caminho_arquivo, AFD_OUTPUT_DIR);     
//   } 

//   else if (tipo == 2)
//     { strcpy(caminho_arquivo, PALAVRAS_DIR); }
    
//   else if (tipo == 3) {
//     copia_nome_arquivo = remover_extensao_string(copia_nome_arquivo);    
//     strcat(copia_nome_arquivo, "_result.txt");
//     strcpy(caminho_arquivo, PALAVRAS_DIR);
//   }
  
//   else {
//     printf("\n\t :::: ERRO: get_dir_arquivo(); \
//     \n\t o tipo especificado é inválido ::::\n");
//     exit(EXIT_FAILURE);
//   }
    
//   strcat(caminho_arquivo, copia_nome_arquivo);

//   free(copia_nome_arquivo); 
  
//   return caminho_arquivo;
// }

// /**
// * 
// * remover extensao de uma string 
// * Ex: 
// * entrada: afd0.txt 
// * retorna: afd0
// * ref: https://stackoverflow.com/questions/2736753/how-to-remove-extension-from-file-name
// */
// char *remover_extensao_string(char* str) {
//   char *retStr;
//   char *lastExt;
//   if (str == NULL) return NULL;
//   if ((retStr = malloc (strlen (str) + 1)) == NULL) return NULL;
//   strcpy (retStr, str);
//   lastExt = strrchr (retStr, '.');
//   if (lastExt != NULL)
//     *lastExt = '\0';
//   return retStr;
// }