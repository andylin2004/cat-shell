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
                kill(getppid(), SIGTERM); //ppid is the shell
            }
            execvp(args[0], args);
        }
    }
}

void executePipedCommands(char *input){
    char **commands = parse_args(input, '|');
    char **args;
    
}

void redirection(char **input){
    int numIn = countDelimiters(input, '<');
    int numOut = countDelimiters(input, '>');
    int numSpaces = parse_args(input, ' ');
    int inSlot = 0;
    int outSlot = 0;
    char **filesIn = malloc(sizeof(char *) * numIn);
    char **filesOut = malloc(sizeof(char *) * numOut);
    char mode;
    int i;
    char *current;
    for (i = 1; i < numSpaces; i++)
    {
        current = input[i];
        if (current == '>'){
            // if (current + 1 == '>')
            // {
            // }
            // else 
            if (mode != NULL){
                break;
            }
            else if (current + 1 != '\0')
            {
                filesOut[outSlot] = current;
                outSlot++;
            }
            else
            {
                mode = '>';
            }
        }else if (current == '<'){
            if (mode != NULL){
                break;
            }
            if (current+1 != '\0'){
                filesIn[inSlot] = current;
                inSlot++;
            }
            else
            {
                mode = '<';
            }
        }else{
            if (mode == '<'){
                filesIn[inSlot] = current;
                inSlot++;
                mode = NULL;
            }
            else if (mode == '>'){
                filesOut[outSlot] = current;
                outSlot++;
                mode = NULL;
            }else{
                //treat as a normal command 
            }
        }
    }
}