#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

void parsecomando(char *comandos, char **argv){
    int i = 0;
    const char s[2] = " ";
    char *token;
    token = strtok(comandos,s);
    while(token != NULL){
        argv[i]= token;
        i++;
        token = strtok(NULL,s);
    }
}
void promptprint(void){
    printf("Qual o seu comando?");
}