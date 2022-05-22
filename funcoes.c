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
     int i = 0; /* controla o loop */
     char *token; 
     int n = -1; 
     
     if(comandos[strlen(comandos)-1] == '\n') { /* troca ultimos caracteres*/    
          comandos[strlen(comandos)-1] = '\0';
     }

     token = strtok(comandos," "); /*divide baseado no espaco entre os comandos*/

     /*transforma a string em um array de argumentos*/    
     while(token && i < MAX_NUM_PARAMS){
          argv[i] = strdup(token);
          i++;
          n++;
          token = strtok(NULL, " "); /*chamada com NULL pois apos a primeira chamada se for utilizada a propria string seria criado um loop infinito */
     }
     argv[i] = NULL;/* a função execvp para quando encontra o parametro NULL na string*/
     return n; /* usado na main para definir o numero de parametros passado para o shell*/
}

/* separa os argumentos em pipes para serem executados*/    
int parsepipe(char ***argvv, char **argv, int *index, int n){
     int i, j, k, l;
     j = 0;

     /* conta o numero de pipes no vetor de parametros */
     for (i = 0; i < n; i++){
          if (strcmp(argv[i], "|") == 0) {
               j++;
          }       
     }

     /* aloca a memoria para j + 1 listas de comandos */
     for (k = 0; k < j + 1; k++){
          argvv[k] = (char**)malloc(15*sizeof(char*));
     }
     
     k = 0;
     l = 0;
     
     /* separa o array de comandos em listas de comandos separados */
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
     argvv[k][l] = NULL;/* a função execvp para quando encontra o parametro NULL na string*/
     index[k] = l;
     
     /* retorna o numero de pipes */
     return j;
}

/* retornar o numero de redirecionamentos por comando */
/*retorna o tipo de redirecionamento a ser utilizado*/    
int redirecionamento(char **argv){
     int i, j;
     j = 0;
     for (i = 0; argv[i] != NULL; i++){
          j++;
     }
     
     for (i = 0; argv[i] != NULL; i++){
          if (strcmp(argv[i], "=>") == 0){
               argv[i] = NULL;
               return 1;
          }
          if (strcmp(argv[i], "<=") == 0){
               argv[i] = NULL;
               return 2;
          }         
     }
     return 0;
}

/*executa do redirecionamendo das entradas e saidas padrão*/    
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

     /*cria ou abre um arquivo para escrita e associa ele a saida padrão*/    
     if (r == 1){
          file[0] = open(argv[f-1], O_WRONLY | O_TRUNC | O_CREAT, 0777); /* cria ou reescreve um arquivo no disco */
          if (file[0] == -1){
               printf("Falha ao escrever ou criar arquivo\n");
               exit(1);
          }
          dup2(file[0], 1);
          close(file[0]);
          return 1;         
     }

     /*abre um arquivo para leitura e associa ele a entrada padrão*/    
     if(r == 2){
          file[0] = open(argv[f-1], O_RDONLY, 0777); /* abre um arquivo no disco*/
          if (file[0] == -1){
               printf("Falha ao abrir arquivo\n");
               exit(1);
          }
          
          dup2(file[0], 0);
          close(file[0]);
          return 2;
     }

     return 3;
}

int entrada_saida2(char **argv, int *file1, int *file2){
     int n, f, i;
     n = 0;
     for (i = 0; argv[i] != NULL; i++){
          if(strcmp(argv[i], "=>") == 0 || strcmp(argv[i], "<=") == 0){
               argv[i] = NULL;
               f = n-1;
          }
          n++;
     }
     
     /*abre um arquivo para leitura e associa ele a entrada padrão*/    
     file1[0] = open(argv[f], O_RDONLY, 0777); /* abre um arquivo no disco*/
     if (file1[0] == -1){
          printf("Falha ao abrir arquivo\n");
          return 1;
     }
     dup2(file1[0], 0);
     close(file1[0]);

     /*cria ou abre um arquivo para escrita e associa ele a saida padrão*/    
     file2[0] = open(argv[n-1], O_WRONLY | O_TRUNC | O_CREAT, 0777); /* cria ou reescreve um arquivo no disco */
     if (file2[0] == -1){
          printf("Falha ao escrever ou criar arquivo\n");
          return 2;
     }
     dup2(file2[0], 1);
     close(file2[0]);

     return 0;
}

int n_redirecionamentos(char **argv){
     int i, r;
     r = 0;
     for (i = 0; argv[i] != NULL; i++){
          if((strcmp(argv[i], "=>") == 0) || (strcmp(argv[i], "<=") == 0))
               r++;
     }
     return r;
}

void  executa(char **argv, int bg){
     pid_t pid;
     int file1, file2, r;
     int status;
     if ((pid = fork()) < 0) {/*usa o fork*/
          printf("erro no fork\n");
          exit(1);
     }
     else if (pid == 0) {/*filho*/
          r = n_redirecionamentos(argv);
          if(r >= 2){
               if(entrada_saida2(argv, &file1, &file2) == 1){
                    exit(1);
               }
          }else
               entrada_saida(argv, &file1);
          if (execvp(argv[0], argv) < 0) {/* executa o comando */
               printf("Comando não encontrado\n");
               exit(1);
          }
     }
     
     else {/* pai */
          if(bg){
               waitpid(pid, &status, 0);
          }else{
               
          }
     }
}

/* Cria dois processos filhos e encaminha a saida de um para a entrada do outro*/
int executapipe(char **argv1, char **argv2, int bg){
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
          dup2(fd[1], 1); /*escreve na entrada do pipe*/
          if(execvp(argv1[0], argv1) < 0){
               printf("Comando não encontrado\n");
               exit(1);
          }
     }

     /*processo filho 2*/
     pid = fork();
     if(pid < 0){
          printf("erro no fork\n");
     }else if(pid == 0){
          entrada_saida(argv2, &file2);
          close(fd[1]);
          dup2(fd[0], 0); /*le a saida do pipe*/
          if(execvp(argv2[0], argv2) < 0){
               printf("Comando não encontrado\n");
               exit(1);
          }
     }

     /*processo pai*/
     close(fd[0]);
     close(fd[1]);
 
     if(bg){
          waitpid(-1, &status, 0);
          waitpid(-1, &status, 0);
     }else{

     }
     return 0;
}

/* apenas o print da espera do shell */
void promptprint(void){
    printf("$ ");
}