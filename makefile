all: shell.o execute.o parse.o
	gcc -o shell shell.o execute.o parse.o
	rm *.o

shell.o: shell.c execute.h
	gcc -c shell.c

execute.o: execute.c execute.h
	gcc -c execute.c

parse.o: parse.c parse.h
	gcc -c parse.c

run:
	./shell
