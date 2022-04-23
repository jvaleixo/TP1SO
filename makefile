# My first makefile
all: printy
printy: shellso.o funcoes.o
	gcc -o printy shellso.o funcoes.o
shellso.o: shellso.c funcoes.h
	gcc -o shellso.o shellso.c -c -W -Wall -ansi -pedantic
funcoes.o: funcoes.c funcoes.h
	gcc -o funcoes.o funcoes.c -c -W -Wall -ansi -pedantic
clean:
	rm -rf *.o *~ printy