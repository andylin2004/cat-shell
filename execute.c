#include "execute.h"

void executeLine(char *input){
    char **commands = parse_args(input, ';');
    char *current = *commands;
    char **args;
    while (current)
    {
        args = parse_args(current, ' ');
        execvp(args[0], args);
        current++;
    }
}