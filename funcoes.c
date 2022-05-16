#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
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
     
     for (i = 0; i < n+1; i++){
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
     argvv[k][l] = NULL;
     index[k] = l;
     
     return j;
}

int redirecionamento(char **argv){
     int i;
     for (i = 0; argv[i] != NULL; i++){
          if (strcmp(argv[i], "=>") == 0){
               argv[i] = NULL;
               return 1;
          }else if (strcmp(argv[i], "<=") == 0){
               argv[i] = NULL;
               return 2;
          }         
     }
     return 0;
}

int entrada_saida(char **argv, int *file){
     int r, f, i;
     f = 0;

     for (i = 0; argv[i] != NULL; i++){
          f++;
     }
     r = redirecionamento(argv); 
     if (r == 0){
          return 0;
     }

    printf("\n\n%s\n\n", argv[f-1]);
     
     if (r == 1){
          file[0] = open(argv[f-1], O_WRONLY | O_CREAT, 0777);
          dup2(file[0], 1);
          close(file[0]);
          return 1;         
     }
     
     if(r == 2){
          file[0] = open(argv[f-1], O_RDONLY, 0777);
          if (file[0] == -1){
               exit(1);
          }
          
          dup2(file[0], 0);
          close(file[0]);
          return 2;
     }

     return 4;
}

void  executa(char **argv){
     pid_t pid;
     int file;
     int status;
     
     if ((pid = fork()) < 0) {/*usa o fork*/
          printf("erro no fork\n");
          exit(1);
     }
     else if (pid == 0) {/*filho*/
          entrada_saida(argv, &file);
          if (execvp(argv[0], argv) < 0) {/* execulta o comando */
               printf("erro no exec\n");
               exit(1);
          }
     }
     
     else {/* pai */
          waitpid(pid, &status, 0);
     }
}

int executapipe(char **argv1, char **argv2){
     int fd[2];
     int status, file1, file2;
     pid_t pid;
     pipe(fd);
     
     /*processo filho 1*/
     pid = fork();
     if(pid < 0){
          printf("erro no fork\n");
     }else if(pid == 0){
          entrada_saida(argv1, &file1);
          close(fd[0]);
          dup2(fd[1], 1); /*escreve a saida no pipe*/
          execvp(argv1[0], argv1);
     }

     /*processo filho 2*/
     pid = fork();
     if(pid < 0){
          printf("erro no fork\n");
     }else if(pid == 0){
          entrada_saida(argv2, &file2);
          close(fd[1]);
          dup2(fd[0], 0); /*le a entrada do pipe*/
          execvp(argv2[0], argv2);
     }

     /*processo pai*/
     close(fd[0]);
     close(fd[1]);

     waitpid(-1, &status, 0);
     waitpid(-1, &status, 0);

     return 0;
}

void promptprint(void){
    printf("$ ");
}