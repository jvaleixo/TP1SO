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
    char comandos[512];
    char *argv[MAX_NUM_PARAMS+1];
    char ***argvv;
    int i, n, j, k, bg;
    int index[15];
    while(TRUE){
        promptprint();
        bg = 1;
        j = 0;
        argvv = (char***)malloc(15*sizeof(char**));
        
        for (i = 0; i < 15; i++)
        {
            index[i] = -1;
        }
        
        fflush(stdin);
        if(fgets(comandos, sizeof(comandos), stdin) == NULL){/* sair no ctrl D*/
            free(argvv);
            exit(0);
        }
        n = parsecomando(comandos, argv);

        if (strcmp(argv[n], "&") == 0){
            bg = 0;
            argv[n] = NULL;
            n--;
        }
        
        if(argv[0] == NULL){/* continue quando aperta enter sem comandos */
            free(argvv);
            continue;
        }

        if (strcmp(argv[0], "fim") == 0){/* sai do programa*/
            free(argvv);
            free(argv[0]);
            exit(0);
        }

        j = parsepipe(argvv, argv, index, n);

        /* define se usa o pipe ou o processo unico*/
        if (j > 0){
            executapipe(argvv[0], argvv[1], bg);
        }else
            executa(argv, bg);
        
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