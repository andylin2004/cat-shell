#include "parse.h"

char ** parse_args(char *string, char delim) {
    int num = countDelimiters(string, delim) + 1;
    char *current;
    char ** result = malloc(num * sizeof(char *));
    int i = 0;
    char seperatorChars[2] = "\n";
        seperatorChars[1] = delim;
    while ((current = strsep(&string, seperatorChars)))
    {
        if (*current){
            result[i] = current;
            i++;
        }
    }
    result[i] = NULL;
    result = realloc(result, (i + 1) * sizeof(char *));
    return result;
}

int countDelimiters(char *string, char delim) {
    char *n = string;
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

char* squigglyToHomeDirectory(char* string){
    string = string + 1;
    char *dir = string + 1;
    char *homedir = getenv("HOME");
    char *completeDir;
    if (*string == '/')
    {
        completeDir = malloc((strlen(homedir) + strlen(dir - 1)) * sizeof(char));
        strcat(completeDir, homedir);
        strcat(completeDir, dir - 1);
    }else if (*string == '\0'){
        completeDir = malloc(strlen(homedir) * sizeof(char));
        strcat(completeDir, homedir);
    }
    else
    {
        completeDir = malloc((strlen(homedir) + strlen("/../") + strlen(dir)) * sizeof(char));
        strcat(completeDir, homedir);
        strcat(completeDir, "/../");
        strcat(completeDir, dir - 1);
    }
    return completeDir;
}