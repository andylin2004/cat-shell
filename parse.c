#include "parse.h"

char ** parse_args(char *code) {
    standardize(code);
    int num = count_args(code) + 1;
    char *n = code;
    char ** result = malloc(num * sizeof(char *));
    char *current;
    int i = 0;
    while (current = strsep(&code, " ")){
        if (*current){
            result[i] = current;
            i++;
        }
    }
    result[i] = NULL;
    return result;
}

//counts number of arguments in a correctly formatted string (no starting, trailing, and consecutively repeated ' ' characters)
int count_args(char *code) {
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

//removes '\n' + starting, trailing, and consecutively repeated ' ' characters.
void standardize(char *code) {
    code[strcspn(code, "\n")];
}
