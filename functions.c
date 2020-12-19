/* Bibliotecas e arquivos */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "utils.h"

/* Fun��es */

/* Objetivo: ler o arquivo que cont�m o aut�mato finito determin�stico

             o arquivo segue o seguinte formato:
             primeira linha: AUTOMATO=({estados},{s�mbolos},Prog,estado inicial,estado final)
             linhas seguintes: transi��es do aut�mato finito que seguem o formato (estado,s�mbolo)=estado

   Entrada: nome do arquivo a ser lido
   Sa�da: estrutura que armazena dados do AFD */

AUTOMATO leArquivoAutomato(char nomeDoArquivo[30]){

    FILE *ptArq;
    AUTOMATO afd;

    char carac;

    int i=0;
    int numEstado;
    char simboloLido;

    ptArq = fopen(nomeDoArquivo, "r"); //abre o arquivo

    if(ptArq != NULL){

        do{

            fscanf(ptArq, "%c", &carac);
        }while(carac != '{'); //l� at� chegar ao primeiro '{'

        do{

            fscanf(ptArq, "%c%d%c", &carac, &numEstado, &carac);
            afd.estados[i] = numEstado;
            i++;
        }while(carac != '}'); //l� os estados presentes no AFD

        afd.qtdEstados = i; //armazena a quantidade de estados em uma vari�vel da estrutura
        i=0;

        fscanf(ptArq, "%c%c", &carac, &carac); //l� os char ',' e '{'

        do{

            fscanf(ptArq, "%c%c", &simboloLido, &carac);
            afd.simbolos[i] = simboloLido;
            i++;
        }while(carac != '}'); //l� os s�mbolos presentes no AFD

        afd.qtdSimbolos = i; //armazena a quantidade de s�mbolos em uma vari�vel da estrutura
        i=0;

        fscanf(ptArq, "%c", &carac); //l� o char ','

        do{

            fscanf(ptArq, "%c", &carac);
        }while(carac != ','); //l� o arquivo at� achar a pr�xima v�rgula (que vem antes do estado inicial)

        fscanf(ptArq, "%c%d%c", &carac, &numEstado, &carac); //l� estado inicial

        afd.estadoInicial = numEstado; //armazena em uma vari�vel da estrutura

        fscanf(ptArq, "%c%d%c", &carac, &numEstado, &carac); //l� estado final

        afd.estadoFinal = numEstado; //armazena em uma vari�vel da estrutura

        while(!feof(ptArq)){ //l� todas as transi��es do AFD

            fscanf(ptArq, "\n%c%c%d%c%c%c", &carac, &carac, &numEstado, &carac, &simboloLido, &carac);
            afd.funcProgEstado[i] = numEstado;
            afd.funcProgSimbolo[i] = simboloLido;

            fscanf(ptArq, "%c%c%d", &carac, &carac, &numEstado);
            afd.funcProgResultado[i] = numEstado;

            i++;
        }

        afd.contFuncProg = i; //armazena a quantidade de transi��es do AFD
        fclose(ptArq); //fecha o arquivo
    }
    else{

        printf("\n|| Failed to open the file...");
    }

    return afd; //e retorna a estrutura que armazena os dados do AFD lido pelo arquivo
}

/* Objetivo: dado uma gram�tica regular criada a partir de um afd que reconhece uma linguagem L,
   classificar uma palavra como aceita ou rejeitada pela linguagem

   Entrada: estrutura contendo dados de uma gram�tica
   Sa�da: estrutura contendo informa��es do resultado (se a palavra � aceita [retorna 1] ou n�o [retorna 0]) e dados para
   imprimir a sequ�ncia de deriva��es de uma gram�tica seguida por uma palavra qualquer

   Exemplos de uso: classificaPalavra(afd, "VAVDVHVK") --> retorna "1" no item resultadoPalavra da estrutura PALAVRA
                    classificaPalavra(afd, "XNXNXNXN") --> retorna "1" no item resultadoPalavra da estrutura PALAVRA
                    classificaPalavra(afd, "VDVAXNXA") --> retorna "0" no item resultadoPalavra da estrutura PALAVRA
                    classificaPalavra(afd, "XAVDVIAX") --> retorna "0" no item resultadoPalavra da estrutura PALAVRA */

PALAVRA classificaPalavra(GRAMATICA gr, char palavra[10]){

    PALAVRA plv;

    int i, j, pos=0; //vari�veis i, j s�o usadas para contagem em loops; vari�vel "pos" usada para leitura da palavra de entrada
    int estadoAtual;
    char simboloAtual;

    estadoAtual = gr.estadoInicial; //o estado atual ser� iniciado com o estado inicial do AFD convertido em gram�tica
    simboloAtual = palavra[pos]; //e o s�mbolo atual ser� iniciado com o primeiro caractere da palavra de entrada

    plv.qtdTransicoes=0;
    plv.resultadoPalavra=0;

    for(i=0; i<gr.qtdEstados; i++){

        for(j=0; j<gr.estadoOpcoes[i]; j++){

            //se estiver no estado atual da GR e o s�mbolo lido pertencer a uma das transi��es feitas por ela
            if((gr.estadoEntrada[i] == estadoAtual)&&(gr.simboloEntrada[gr.estadoEntrada[i]][j] == toupper(simboloAtual))){

                //guarda estas informa��es para imprimir a sequ�ncia de deriva��es, posteriormente
                plv.estadoEntrada[pos] = gr.estadoEntrada[i];
                plv.simboloEntrada[pos] = toupper(simboloAtual);
                plv.estadoSaida[pos] = gr.estadoSaida[gr.estadoEntrada[i]][j];
                plv.qtdTransicoes++;

                //atualiza o estado atual para o estado resultante da combina��o entre o estado atual e o s�mbolo atual lidos
                estadoAtual = gr.estadoSaida[gr.estadoEntrada[i]][j];
                pos++; //e l� o pr�ximo caractere da palavra
                simboloAtual = palavra[pos];

                if(estadoAtual == gr.estadoFinal){ //se o estado atual for o estado final do AFD

                    //armazena essa informa��o para imprimir, posteriormente, a sequ�ncia de deriva��es
                    plv.estadoEntrada[pos] = gr.estadoSaida[gr.estadoEntrada[i]][j];
                    plv.simboloEntrada[pos] = 'F';
                    plv.qtdTransicoes++;
                    pos++;
                }

                break; //encerra o loop atual e parte para a an�lise do pr�ximo estado

            }
        }
    }

    if(estadoAtual == gr.estadoFinal) //se o �ltimo estado lido pela GR for igual ao estado final
        plv.resultadoPalavra = 1; //atualiza a vari�vel de retorno para "1"

    return plv; //retorna a estrutura contendo as informa��es para imprimir a sequ�ncia de deriva��es e se a palavra � aceita ou n�o
}

/* Objetivo: converter um aut�mato finito em uma gram�tica regular

   Entrada: estrutura contendo informa��es de um aut�mato finito determin�stico a ser convertido
   Sa�da: estrutura contendo informa��es de uma gram�tica regular */

GRAMATICA automatoParaGramatica(AUTOMATO afd){

    GRAMATICA gr;

    int i;

    gr.qtdEstados = afd.qtdEstados; //transfere a quantidade de estados, o estado inicial e o estado final para a estrutura da GR
    gr.estadoInicial = afd.estadoInicial;
    gr.estadoFinal = afd.estadoFinal;

    for(i=0; i<gr.qtdEstados; i++){ //transfere os estados do AFD para os estados da GR e inicializa a vari�vel com a quantidade
                                    //de transi��es de cada estado

        gr.estadoEntrada[i] = afd.estados[i];
        gr.estadoOpcoes[i]=0;
    }

    for(i=0; i<afd.contFuncProg; i++){ //l� todas as transi��es lidas pela fun��o de leitura arquivo contendo o AFD

        gr.simboloEntrada[afd.funcProgEstado[i]][gr.estadoOpcoes[afd.funcProgEstado[i]]] = afd.funcProgSimbolo[i];
        gr.estadoSaida[afd.funcProgEstado[i]][gr.estadoOpcoes[afd.funcProgEstado[i]]] = afd.funcProgResultado[i];
        gr.estadoOpcoes[afd.funcProgEstado[i]] += 1; //incrementa a vari�vel com a qtd. de poss�veis transi��es do estado atual
    }

    return gr; //retorna a estrutura contendo informa��es da gram�tica regular
}

/* Objetivo: imprime as deriva��es poss�veis de cada estado de uma GR

   Entrada: estrutura contendo informa��es de uma gram�tica regular
   Sa�da: nenhuma */

void imprimeGramatica(GRAMATICA gr){

    int i, j;

    printf("|| Regular Grammar (as a Right Linear Unitary Grammar): ");

    for(i=0; i<gr.qtdEstados; i++){

        printf("\n|| q%d -> ", gr.estadoEntrada[i]); //imprime o estado

        for(j=0; j<gr.estadoOpcoes[i]; j++){ //e as poss�veis deriva��es a serem feitas por ele

            printf("%cq%d", gr.simboloEntrada[gr.estadoEntrada[i]][j], gr.estadoSaida[gr.estadoEntrada[i]][j]);

            if(j+1 != gr.estadoOpcoes[i]){ //se houver mais que uma transi��o imprime o char '|' para dividi-las

                printf(" | ");
            }
        }

        if(gr.estadoEntrada[i] == gr.estadoFinal) //se for o estado final imprime a string "end" para representar
            printf("end");                        //a palavra vazia
    }

    printf("\n\n");
}

/* Objetivo: imprimir a sequ�ncia de deriva��es feita pelas transi��es da gram�tica at� chegar ao estado final

   Entrada: estrutura contendo informa��es da sequ�ncia de deriva��es feita pela palavra em uma gram�tica regular e estrutura
   contendo informa��es da gram�tica regular
   Sa�da: nenhuma */

void imprimePasso(PALAVRA palavra, GRAMATICA gr){

    int i;

    for(i=0; i<palavra.qtdTransicoes; i++){ //imprime a sequ�ncia de deriva��es de uma palavra aceita pelo AFD convertido em GR

        if(palavra.estadoEntrada[i] != gr.estadoFinal)
            printf("|| Step %d: q%d -> %cq%d\n", i+1, palavra.estadoEntrada[i], palavra.simboloEntrada[i], palavra.estadoSaida[i]);
        else
            printf("|| Step %d: q%d -> end\n", i+1, palavra.estadoEntrada[i]);
    }
}
