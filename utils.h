/* Estruturas */

typedef struct{

    int estados[20]; //armazena a qtd. de estados [m�ximo de 20 estados]
    char simbolos[20]; //e a qtd. de s�mbolos do aut�mato lido [m�ximo de 20 s�mbolos]
    int estadoInicial; //armazena o estado inicial
    int estadoFinal; //e o estado final do aut�mato lido
    int qtdEstados; //armazena a qtd. de estados [vari�vel de contagem]
    int qtdSimbolos; //e a qtd. de s�mbolos do aut�mato lido [vari�vel de contagem]
                            //dado que uma transi��o em um AFD � do tipo (estado de entrada, s�mbolo de entrada)=estado de sa�da,
    int funcProgEstado[50]; //armazena os estados de entrada das transi��es do aut�mato lido [m�ximo de 50 transi��es]
    char funcProgSimbolo[50]; //armazena os s�mbolos de entrada das transi��es do aut�mato lido [m�ximo de 50 transi��es]
    int funcProgResultado[50]; //armazena os estados de sa�da das transi��es do aut�mato lido [m�ximo de 50 transi��es]
    int contFuncProg; //armazena a qtd. de transi��es lidas pelo arquivo que cont�m o AFD [vari�vel de contagem]

}AUTOMATO;

typedef struct{
                           //dado que uma deriva��o em uma GR � do tipo estado de entrada -> (s�mbolo de entrada)(estado de sa�da),
    int estadoEntrada[20]; //armazena os estados de entrada resultantes da convers�o do AFD em GR [m�ximo de 20 estados]
    char simboloEntrada[20][20]; //armazena os s�mbolos de entrada resultantes da convers�o do AFD em GR [m�ximo de 20 s�mbolos]
    int estadoSaida[20][20]; //armazena os estados de sa�da resultantes da convers�o do AFD em GR [m�ximo de 20 estados]

    int estadoOpcoes[20]; //armazena as poss�veis deriva��es de um estado da GR [m�ximo de 20 deriva��es]
    int qtdEstados; //armazena a qtd. de estados do AFD convertido em GR [vari�vel de contagem]

    int estadoInicial; //armazena o estado inicial
    int estadoFinal; //e o estado final do AFD convertido em GR

}GRAMATICA;

typedef struct{

     int resultadoPalavra; //armazena o resultado da classifica��o de uma palavra como aceita("1") ou rejeitada("0") pela linguagem

     int estadoEntrada[20]; //armazena o estado de entrada,
     char simboloEntrada[20]; //o s�mbolo de entrada
     int estadoSaida[20]; //e o estado de sa�da da sequ�ncia de deriva��es de uma palavra aceita pela linguagem [m�ximo de 20 deriva��es]
     int qtdTransicoes; //armazena a qtd. de deriva��es da sequ�ncia [vari�vel de contagem]

}PALAVRA;

/* Esqueleto das fun��es */

AUTOMATO leArquivoAutomato(char nomeDoArquivo[30]);
PALAVRA classificaPalavra(GRAMATICA gr, char palavra[10]);
GRAMATICA automatoParaGramatica(AUTOMATO afd);
void imprimeGramatica(GRAMATICA gr);
void imprimePasso(PALAVRA palavra, GRAMATICA gr);
