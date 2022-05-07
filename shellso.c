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
    char ***argvv = (char***)malloc(15*sizeof(char**));
    int i, n, j, k, l;
    int index[15];
    while(TRUE){
        promptprint();

        for (i = 0; i < 15; i++)
        {
            index[i] = -1;
            argvv[i] = (char**)malloc(15*sizeof(char*));
        }
        
        if(fgets(comandos, sizeof(comandos), stdin) == NULL) exit(0); /* sair no ctrl D*/

        n = parsecomando(comandos, argv);

        if(strcmp(argv[0],"\0") == 0){
            promptprint();    
            continue;
        }

        if (strcmp(argv[0], "fim") == 0){/* sai do programa*/ 
            free(argv[0]);
            exit(0);
        } 

        j = 0;
        for (i = 0; i < n; i++){
            if (strcmp(argv[i], "|") == 0) {
               j++;
            }       
        }
        k = 0;
        l = 0;
        for (i = 0; j > 0 && i < n; i++){
            if (strcmp(argv[i], "|") == 0) {
                argvv[k][l] = NULL;
                index[k] = l;
                k++;
                l=0;
            }else{
                argvv[k][l] = strdup(argv[i]);
                l++;
            }
        }

        if (j > 0){
            for (i = 0; i < j+1; i++){   
                printf("%d - ", i);
                for (k = 0; k < index[i]; k++){
                    printf(" %s", argvv[i][k]);
                }
                printf("\n");
            }
            
        }else
            executa(argv);
        
        
        for (i = 0; i < n+1; i++){
            free(argv[i]);
        }
        
    }
    return (0);
}