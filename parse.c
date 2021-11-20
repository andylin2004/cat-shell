#include "parse.h"

char ** parse_args(char *code, char delim) {
    int num = countDelimiters(code, delim) + 1;
    char *current;
    char ** result = malloc(num * sizeof(char *));
    int i = 0;
    char seperatorChars[2] = "\n";
    seperatorChars[1] = delim;
    while (current = strsep(&code, seperatorChars))
    {
        if (*current){
            result[i] = current;
            i++;
        }
    }
    result[i] = NULL;
    return result;
}

//counts number of arguments in a correctly formatted string (no starting, trailing, and consecutively repeated ' ' characters)
int countDelimiters(char *code, char delim) {
    char *n = code;
    int num = 1;
    while (*n) {
        if (*n == ' ') {
            num++;
        }
        n++;
    }
    return num;
}
