#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include "funcoes.h"

#define TRUE 1 

int main(){
    char comandos[512]; /* ler do usuario*/
    char *argv[MAX_NUM_PARAMS+1]; /* comandos separados*/
    char ***argvv; 
    int i, n, j, k, bg; /*n = retorno numero de comandos que o usuario digitou, j = numero de pipes, bg = define se o processo vai para o background*/
    int index[15]; /* salva o numero de comandos por pipe*/
    while(TRUE){
        promptprint(); /* funcao para imprimir o '$ ' do shell*/
        bg = 1;
        j = 0;
        argvv = (char***)malloc(15*sizeof(char**)); /*alocando memoria para o recebimento dos comandos*/
        
        for (i = 0; i < 15; i++)
        {
            index[i] = -1;
        }
        
        fflush(stdin);
        if(fgets(comandos, sizeof(comandos), stdin) == NULL){/* sair no ctrl D*/
            free(argvv); /*liberar memoria*/
            exit(0); /* fecha o programa*/
        }
        n = parsecomando(comandos, argv); /* faz a divisão para identificar os comandos passados pelo usuario*/

        if (strcmp(argv[n], "&") == 0){ /* identifica alguma parte do argumeto eh &*/
            bg = 0; 
            argv[n] = NULL; /* posicao do argumento se torna NULL para facilitar no resto do programa */
            n--;
        }
        
        if(argv[0] == NULL){/* continue quando aperta enter sem comandos */
            free(argvv); /*liberar memoria*/
            continue;
        }

        if (strcmp(argv[0], "fim") == 0){/* sai do programa*/
            free(argvv); /*liberar memoria*/
            free(argv[0]); 
            exit(0); /* fecha o programa*/
        }

        j = parsepipe(argvv, argv, index, n); /*faz divisao para identificar os pipes*/

        /* define se usa o pipe ou o processo unico*/
        if (j > 0){
            executapipe(argvv[0], argvv[1], bg);
        }else
            executa(argv, bg);
        
        /* liberar memoria*/
        for (i = 0; i < n+1; i++){
            free(argv[i]);
        }
        for (i = 0; i < j+1; i++){
            for (k = 0; k < index[i]; k++){
                free(argvv[i][k]);
            }
            free(argvv[i]);
        }
        free(argvv);
    
    }
    return (0);
}