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
    char *argv[100];
    /*FILE * pFile;
    pFile = fopen("arquivo.txt","w"); */
    /*pid_t cpid, w;*/
    /*int status,j;*/
    /*char a[1000];*/
    while(TRUE){
        promptprint();
        /*scanf("%s[^\n]",comandos);*/
        gets(comandos);
        parsecomando(comandos,argv);
        /* fputs(*argv,pFile); */
        if(strcmp(argv[0],"fim") == 0)
            exit(0);
        executa(argv);
        /*cpid = fork();
       /* if(cpid != 0){
            do {
            printf("\n entrei no do\n");
            w = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
            printf("\n teste\n"); 
            if (w == -1) {
                printf("\n entrei no if\n");
                perror("waitpid");
                exit(EXIT_FAILURE);
            }

           if (WIFEXITED(status)) {
                printf("exited, status=%d\n", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                printf("killed by signal %d\n", WTERMSIG(status));
            } else if (WIFSTOPPED(status)) {
                printf("stopped by signal %d\n", WSTOPSIG(status));
            } else if (WIFCONTINUED(status)) {
                printf("continued\n");
            }
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        exit(EXIT_SUCCESS);
    } else {
        printf("%s",a);
    } */
      /*  if(cpid == 0){
            printf("Child PID is %ld\n", (long) getpid());
            if (argc == 1)
                pause();                    Wait for signals 
            _exit(atoi(argv[1]));
        } else {                   Code executed by parent 
        do {
            w = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
            if (w == -1) {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }

           if (WIFEXITED(status)) {
                printf("exited, status=%d\n", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                printf("killed by signal %d\n", WTERMSIG(status));
            } else if (WIFSTOPPED(status)) {
                printf("stopped by signal %d\n", WSTOPSIG(status));
            } else if (WIFCONTINUED(status)) {
                printf("continued\n");
            }
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        exit(EXIT_SUCCESS);
         }  */  
    }
        return (0);
}