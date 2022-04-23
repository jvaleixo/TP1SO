#include "funcoes.h"

#define TRUE 1 
int main(int argc, char *argv[]){
    pid_t cpid, w;
    int a,status;
    cpid = fork();
    while(TRUE){
        promptprint();
        scanf("%d",&a);
        if(cpid == 0){
            printf("Child PID is %ld\n", (long) getpid());
            if (argc == 1)
                pause();                    /* Wait for signals */
            _exit(atoi(argv[1]));
        } else {                    /* Code executed by parent */
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
    }
    }    
    return (0);
}