/* Bibliotecas e arquivos */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "utils.h"

/* Fun��o principal */

int main(void){

    AUTOMATO afd; //estrutura para armazenar dados relativos ao AFD lido
    GRAMATICA gr; //estrutura para armazenar dados relativos � GR convertida de um AFD
    PALAVRA plv; //estrutura contendo dados para imprimir a sequ�ncia de deriva��es e o resultado da classifica��o de uma
                 //palavra como aceita ou rejeitada pela linguagem
    int i;

    char palavraLida[10]={}; //vetor que armazena a string entrada pelo usu�rio
    char nomeDoArquivo[30]={}; //string com nome do arquivo

    printf("\n|| DFA to RG");
    printf("\n|| Evaluate a word as accepted or rejected by the language\n");

    printf("\n|| Enter the file's name: ");
    gets(nomeDoArquivo);
    afd = leArquivoAutomato(nomeDoArquivo); //l� o arquivo contendo as informa��es do AFD
    gr = automatoParaGramatica(afd); //converte o AFD em GR

    do{ //in�cio da leitura das strings do usu�rio

        printf("\n|| To stop the entry, type \"stop\"");
        printf("\n|| Enter the word to be tested: ");
        gets(palavraLida); //entrada da string do usu�rio

        if(strcmp(palavraLida, "stop") != 0){ //se a string entrada n�o for de parada,

            system("cls");
            imprimeGramatica(gr); //imprime as poss�veis deriva��es da GR

            printf("|| Word: ");

            for(i=0; i<strlen(palavraLida); i++)
                printf("%c", toupper(palavraLida[i])); //imprime a string de entrada do usu�rio

            printf("\n");

            plv = classificaPalavra(gr, palavraLida); //classifica a palavra como aceita/rejeitada e coleta informa��es
                                                      //para imprimir a sequ�ncia de deriva��es posteriormente
            if(plv.resultadoPalavra == 1){ //se o retorno da fun��o "classificaPalavra" for "1", � aceita

                imprimePasso(plv, gr); //ent�o imprime a sequ�ncia de deriva��es
                printf("\n|| The word belongs to the language\n"); //e indica que foi aceita
            }
            else{

                printf("\n|| The word does not belong to the language\n");
            }
        }
    }while(strcmp(palavraLida, "stop") != 0); //repete o loop at� que a string do usu�rio n�o seja "stop"

    return 0; //fim
}
