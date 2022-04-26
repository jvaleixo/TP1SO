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
    char comandos[1024];
    char *argv[MAX_NUM_PARAMS+1]; 
    /*int i, n;*/
    while(TRUE){
        promptprint();
        
        if(fgets(comandos, sizeof(comandos), stdin) == NULL) break; /* sair no ctrl D*/

        /*n = parsecomando(comandos, argv);*/
        parsecomando(comandos, argv);
       
        if (strcmp(argv[0], "fim") == 0) exit(0); /* sai do programa*/
        
        if(strcmp(argv[0],"\0") == 0)
            promptprint();    
        executa(argv);
    }
    return (0);
}