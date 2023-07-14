# CSI106TP: Automatos Finitos Determinísticos

## CSI106 - Fundamentos Teóricos da Computação :: 2022.2

Trabalho Prático - Automatos Finitos Determinísticos

 - O objetivo deste projeto é abordar a representação prática dos Automatos Finitos Determinísticos (AFDs) incluíndo operações de leitura, escrita, reconhecimento de palavras, e operações entre AFDS.

## Compilação:
1) Gera os binários com Makefile
  ```
    $ make
  ```

2) Executa a aplicação com os argumentos especificos de cada operação:
  ```
  $ ./afdtool --dot afd.txt --output afd.dot
  $ ./afdtool --complemento afd1.txt --output afd1-complemento.txt
  $ ./afdtool --minimizacao afd1.txt --output afd1-minimizacao.txt
  $ ./afdtool --reconhecer afd.txt palavras.txt --output palavras-reconhecidas.txt
  ```

## Sobre a implementação:

Com base na proposta do trabalho foram implementadas as seguintes funcionalidades:

  1) Exportar como dot;
  2) Gerar complemento de um AFD;
  3) Minimizar um AFD;
  4) Reconhecer um conjunto de palavras para um AFD de entrada;
  
 ### Estrutura do projeto:
 
  - Makefile fica no diretório raiz do projeto;
  - app/: reservada para o script afdtool.c que contém a main() do programa;
  - obj/: agrupa os binários gerados pelo Makefile;
  
  - src/: módulos implementados;
    
    -src/include/: arquivos .h
    
    - src/afd/: módulos específicos para manipulação de afds, assim como leitura e escrita;
    - src/operacoes/: módulos específicos para cada operação implementada;
    - src/operacoes.c: serve como interface para a chamada das operações;
    - src/utils/: implementa métdos auxilares, como manipulação de strings e vetores dinâmicos;
    
    
  
  
 
```
./
├── afd-operacoes.pdf
├── afd.txt
├── app
│   └── afdtool.c
├── exemplos_compilacao.txt
├── Makefile
├── obj
├── palavras.txt
├── README.md
├── resultados
│   ├── ...
└── src
    ├── include
    │   ├── afd
    │   │   ├── afd.h
    │   │   ├── escrever.h
    │   │   ├── exportar.h
    │   │   └── leitura.h
    │   ├── headers.h
    │   ├── operacoes
    │   │   ├── complemento.h
    │   │   ├── minimizar.h
    │   │   └── reconhecer_palavra.h
    │   ├── operacoes.h
    │   └── utils
    │       ├── particoes.h
    │       └── str_utils.h
    ├── afd
    │   ├── afd.c
    │   ├── escrever.c
    │   ├── exportar.c
    │   └── leitura.c    
    ├── operacoes
    │   ├── complemento.c
    │   ├── minimizar.c
    │   └── reconhecer_palavra.c
    ├── operacoes.c
    └── utils
        ├── particoes.c
        └── str_utils.c
```
 
  
