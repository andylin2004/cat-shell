all: shell.o parse.o
	gcc -o shell shell.o parse.o
	rm *.o

shell.o: shell.c parse.h
	gcc -c shell.c

parse.o: parse.c parse.h
	gcc -c parse.c

run:
	./shell
