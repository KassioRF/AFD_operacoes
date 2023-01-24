# AFD_operacoes
FTC - Trabalho Prático 2023


## Sobre a estrutura:

  #### OBS: São definições para começar, fiquem à vontade para fazer ajustes.

  Função `main()`: [app/afdtool.c](./app/afdtool.c)

  Modulos: [src/](./src/)

   - [src/afd](./src/afd): Estrutura de dados para AFD e metodos de leitura e escrita.

   - [src/operacoes](./src/operacoes): Operações sobre AFD's: União, Interseção, Complemento e Minimização.
    
   - [src/utils](./src/utils): Funções/Bilbiotecas auxiliares.
    


  Headers: [include/](./include)
    
   - Segue a mesma estrutura de pastas dos modulos, mas não quer dizer que um .c tenha que ter obrigatóriamente um .h.
    
    - Ex: Mesmo que tenha um modulo.c para cada operação acredito que eles possam compartilhar o mesmo .h.


  ### Arquivos de entrada e saída:

   A princípio optei por diretórios específicos para leitura e escrita dos arquivos externos.

   - Afds de entrada devem estar em [afds_entrada/](./afds_entrada/)
   - Afds de saída  vão para [afds_saida/](./afds_saida/)

## Compilar com Makefile

### Linux:
  
  1. Gerar binários:
    
    $ make

  2. Executar:
    
    $ make run
    
    ou
    
    $ ./afdtool

  3. Remover binários: ( As vezes resolve bug tbm xD )

    $ make clean

### Windows:

  Em breve descobriremos kkkk

  links uteis que ainda não tive tempo de testar:

   - Instalar gcc no windows: https://linuxhint.com/install-c-compiler-windows/
   - Como compilar C no windows com makefile: https://linuxhint.com/run-makefile-windows/


## Implementações:

  #### FUNCIONALIDADE 1: visualização (ok!)

  - [Ler AFD](./src/afd/leitura.c)
  - [Exportar .dot]((./src/afd/exportar.c))


  #### FUNCIONALIDADE 2: complemento

  #### FUNCIONALIDADE 3: interseção e união

  #### FUNCIONALIDADE 4: minimização

  #### FUNCIONALIDADE 5: reconhecimento de palavra