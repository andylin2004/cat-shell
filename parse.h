#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
// #include <readline/readline.h>
// #include <readline/history.h>
#define SIZE 1000

//separates a string by a certain delimiter, returns the separated pieces in an array; the final entry is NULL
char ** parse_args(char *code, char delim);
//counts number of occurrences of a certain delimiter (which will be used in parseargs)
int countDelimiters(char *code, char delim);
//calculates the total length of a string that has been separated into an array
int arrayOfStringsLength(char **array);
char *standardizeString(char *oldString);
//calculates the total amount of entries in a char* array.
int lengthOfArray(char **array);
