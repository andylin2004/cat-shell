#include "execute.h"

void executeLine(char *input){
    int numCommands = countDelimiters(input, ';');
    char **commands = parse_args(input, ';');
    char **args;
    int i;
    int status;
    for (i = 0; i < numCommands; i++)
    {
        args = parse_args(commands[i], ' ');
        if (fork())
        {
            wait(&status);
        }
        else
        {
            if (strcmp(args[0], "exit") == 0){
                kill(getppid(), SIGTERM);
            }
            execvp(args[0], args);
        }
    }
}

void executePipedCommands(char *input){
    char **commands = parse_args(input, '|');
    char **args;
    
}

void redirection(char *input){
    char **commands = parse_args(input, '>');
    char **args;

}