#include "parse.h"

char ** parse_args(char *code) {
    int num = countDelimiters(code, ' ') + 1;
    char *current;
    char ** result = malloc(num * sizeof(char *));
    int i = 0;
    while (current = strsep(&code, " \n")){
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

//handles multiple commands seperated by a ;
//TODO: work on this
void parseWithSemicolons(char *code){
    int num = countDelimiters(code, ';') + 1;
    char *current;
    char **result = malloc(num * sizeof(char *));
    int i = 0;
    while (current = strsep(&code, ";\n"))
    {
        if (*current){
            result[i] = current;
            i++;
        }
    }
    result[i] = NULL;
    return result;
}

//handles pipes
//TODO: work on this
void parseWithPipes(){

}
