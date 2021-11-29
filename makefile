all: shell.o execute.o parse.o history.o
	gcc -o shell shell.o execute.o parse.o history.o
	rm *.o

shell.o: shell.c execute.h parse.h history.c
	gcc -c shell.c

execute.o: execute.c execute.h parse.h
	gcc -c execute.c

parse.o: parse.c parse.h
	gcc -c parse.c

history.o: history.c history.h parse.h
	gcc -c history.c

run:
	./shell
