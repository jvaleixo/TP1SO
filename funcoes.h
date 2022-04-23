
#ifdef _XOPEN_SOURCE 
#undef _XOPEN_SOURCE
#define _XOPEN_SOURCE 200112L
#endif
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#define TRUE 1
#ifndef _H_TESTE
#define _H_TESTE
 
void helloWorld(void);
void promptprint(void);
#endif