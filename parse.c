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

//counts number of occurrences of a certain deliminator (which will be used in parseargs)
int countDelimiters(char *code, char delim) {
    char *n = code;
    int num = 1;
    while (*n) {
        if (*n == delim) {
            num++;
        }
        n++;
    }
    return num;
}
