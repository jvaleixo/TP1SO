
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#define TRUE 1
#ifndef _H_TESTE
#define _H_TESTE
 
void parsecomando(char *comandos, char **argv);
void promptprint(void);
#endif