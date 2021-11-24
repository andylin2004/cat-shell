#include "parse.h"

char ** parse_args(char *code, char delim) {
    int num = countDelimiters(code, delim) + 1;
    char *current;
    char ** result = malloc(num * sizeof(char *));
    int i = 0;
    char seperatorChars[2] = "\n";
    seperatorChars[1] = delim;
    while ((current = strsep(&code, seperatorChars)))
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

int arrayOfStringsLength(char **array){
    char **current = array;
    int total = 0;
    while (*current)
    {
        total += strlen(*current);
        current++;
    }
    return total;
}

char *standardizeString(char *oldString){
    int newStringLength = (countDelimiters(oldString, '>') - 1)*2 + (countDelimiters(oldString, '<')- 1)*2 + (countDelimiters(oldString, '|')-1)*2 + strlen(oldString);
    char *newString = malloc(newStringLength);
    char *current = oldString;
    int indice = 0;
    while (*current)
    {
        if (*current == '>' && *(current + 1) == '>'){
            newString[indice] = ' ';
            indice++;
            newString[indice] = *current;
            indice++;
            newString[indice] = *current;
            indice++;
            newString[indice] = ' ';
            current++;
        }
        else if (*current == '>' || *current == '<' || *current == '|')
        {
            newString[indice] = ' ';
            indice++;
            newString[indice] = *current;
            indice++;
            newString[indice] = ' ';
        }
        else
        {
            newString[indice] = *current;
        }
        indice++;
        current++;
    }
    return newString;
}

int lengthOfArray(char **array){
    int total = 0;
    while(*array){
        total++;
        array++;
    }
    return total;
}