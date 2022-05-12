# My first makefile
all: main
main: shellso.o funcoes.o
	gcc shellso.o funcoes.o -o main
shellso.o: shellso.c funcoes.h
	gcc -o shellso.o shellso.c -c -W -Wall -ansi -pedantic
funcoes.o: funcoes.c funcoes.h
	gcc -o funcoes.o funcoes.c -c -W -Wall -ansi -pedantic
clean:
	rm -rf *.o *~ main