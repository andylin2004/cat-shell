all: shell.o parse.o execute.o
	gcc -o shell shell.o parse.o execute.o
	rm *.o

shell.o: shell.c parse.h
	gcc -c shell.c

execute.o: execute.c execute.h
	gcc -c execute.c

parse.o: parse.c parse.h
	gcc -c parse.c

run:
	./shell
