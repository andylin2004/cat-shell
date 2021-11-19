#include "parse.h"

char ** parse_args(char *code) {
    standardize(code);
    int num = count_args(code);
    char *n = code;
    char *entry;
    char ** r = malloc(num * sizeof(char *));
    while ((entry = strsep(&n, " "))) {
        r[i] = malloc(SIZE);
        strcpy(r[i], entry);
        i++
    }
    return r;
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
