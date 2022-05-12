#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include "funcoes.h"

int parsecomando(char *comandos, char **argv){
     int i = 0;
     char *token;
     int n = -1;
     
     if(comandos[strlen(comandos)-1] == '\n') { /* troca ultimos caracteres*/    
          comandos[strlen(comandos)-1] = '\0';
     }

     token = strtok(comandos," ");
 
     while(token && i < MAX_NUM_PARAMS){
          /*if(strcmp(token, "=>") == 0)
               argv[i] = strdup(">");
          else if(strcmp(token, "<=") == 0)
               argv[i] = strdup("<");
          else*/
               argv[i] = strdup(token);
          
          i++;
          n++;
          token = strtok(NULL, " ");
     }
     argv[i] = NULL;
     return n;
}

int parsepipe(char ***argvv, char **argv, int *index, int n){
     int i, j, k, l;
     j = 0;
     for (i = 0; i < n; i++){
          if (strcmp(argv[i], "|") == 0) {
               j++;
          }       
     }

     for (k = 0; k < j + 1; k++){
          argvv[k] = (char**)malloc(15*sizeof(char*));
     }
     
     k = 0;
     l = 0;

     for (i = 0; j > 0 && i < n+1; i++){
          if (strcmp(argv[i], "|") == 0) {
               argvv[k][l] = NULL;
               index[k] = l;
               l=0;
               k++;
          }else{
               argvv[k][l] = strdup(argv[i]);
               l++;
          }
     }
     index[k] = l;
     return j;
}

void  executa(char **argv)
{
     pid_t pid;
     int status;

     if ((pid = fork()) < 0) {/*usa o fork*/
          printf("erro no fork\n");
          exit(1);
     }
     else if (pid == 0) {/*filho*/
          if (execvp(argv[0], argv) < 0) {/* execulta o comando */
               printf("erro no exec\n");
               exit(1);
          }
     }
     else {/* pai */
          waitpid(pid, &status, 0);
     }
}

void promptprint(void){
    printf("Qual o seu comando? ");
}