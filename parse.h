#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define SIZE 1000

char ** parse_args(char *code, char delim);
int countDelimiters(char *code, char delim);
int arrayOfStringsLength(char **array);
char *standardizeString(char *oldString);