#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

void parsecomando(char *comandos, char **argv){
    int i = 0;
    /*const char s[1] = " ";*/
    char *token;
    token = strtok(comandos," ");
    while(token != NULL){
        argv[i] = token;
        i++;
        /*token = strtok(NULL," ");*/
    }
}
void  executa(char **argv)
{
     pid_t  pid;
     int    status;
     
     if ((pid = fork()) < 0) {     /* fork a child process           */
          printf("*** ERROR: forking child process failed\n");
          exit(1);
     }
     else if (pid == 0) {          /* for the child process:         */
          if (execvp(*argv, argv) < 0) {     /* execute the command  */
               printf("*** ERROR: exec failed\n");
               exit(1);
          }
     }
     else {                                  /* for the parent:      */
          while (wait(&status) != pid)       /* wait for completion  */
               ;
     }
}
void promptprint(void){
    printf("Qual o seu comando? ");
}