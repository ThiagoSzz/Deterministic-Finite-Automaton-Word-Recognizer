/* Estruturas */

typedef struct{

    int estados[20]; //armazena a qtd. de estados [máximo de 20 estados]
    char simbolos[20]; //e a qtd. de símbolos do autômato lido [máximo de 20 símbolos]
    int estadoInicial; //armazena o estado inicial
    int estadoFinal; //e o estado final do autômato lido
    int qtdEstados; //armazena a qtd. de estados [variável de contagem]
    int qtdSimbolos; //e a qtd. de símbolos do autômato lido [variável de contagem]
                            //dado que uma transição em um AFD é do tipo (estado de entrada, símbolo de entrada)=estado de saída,
    int funcProgEstado[50]; //armazena os estados de entrada das transições do autômato lido [máximo de 50 transições]
    char funcProgSimbolo[50]; //armazena os símbolos de entrada das transições do autômato lido [máximo de 50 transições]
    int funcProgResultado[50]; //armazena os estados de saída das transições do autômato lido [máximo de 50 transições]
    int contFuncProg; //armazena a qtd. de transições lidas pelo arquivo que contém o AFD [variável de contagem]

}AUTOMATO;

typedef struct{
                           //dado que uma derivação em uma GR é do tipo estado de entrada -> (símbolo de entrada)(estado de saída),
    int estadoEntrada[20]; //armazena os estados de entrada resultantes da conversão do AFD em GR [máximo de 20 estados]
    char simboloEntrada[20][20]; //armazena os símbolos de entrada resultantes da conversão do AFD em GR [máximo de 20 símbolos]
    int estadoSaida[20][20]; //armazena os estados de saída resultantes da conversão do AFD em GR [máximo de 20 estados]

    int estadoOpcoes[20]; //armazena as possíveis derivações de um estado da GR [máximo de 20 derivações]
    int qtdEstados; //armazena a qtd. de estados do AFD convertido em GR [variável de contagem]

    int estadoInicial; //armazena o estado inicial
    int estadoFinal; //e o estado final do AFD convertido em GR

}GRAMATICA;

typedef struct{

     int resultadoPalavra; //armazena o resultado da classificação de uma palavra como aceita("1") ou rejeitada("0") pela linguagem

     int estadoEntrada[20]; //armazena o estado de entrada,
     char simboloEntrada[20]; //o símbolo de entrada
     int estadoSaida[20]; //e o estado de saída da sequência de derivações de uma palavra aceita pela linguagem [máximo de 20 derivações]
     int qtdTransicoes; //armazena a qtd. de derivações da sequência [variável de contagem]

}PALAVRA;

/* Esqueleto das funções */

AUTOMATO leArquivoAutomato(char nomeDoArquivo[30]);
PALAVRA classificaPalavra(GRAMATICA gr, char palavra[10]);
GRAMATICA automatoParaGramatica(AUTOMATO afd);
void imprimeGramatica(GRAMATICA gr);
void imprimePasso(PALAVRA palavra, GRAMATICA gr);
