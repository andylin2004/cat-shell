#include "execute.h"

void executeLine(char *input)
{
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
            if (strcmp(args[0], "cd") == 0){
                cd(args);
            }
            else if (strcmp(args[0], "exit") == 0)
            {
                kill(getppid(), SIGTERM); //ppid is the shell
            }
            execvp(args[0], args);
        }
    }
}

void executePipedCommands(char *input)
{
    char **commands = parse_args(input, '|');
    char **args;
}

void redirection(char **input)
{
    char *current = input;
    FILE *stdoutFile;
    FILE *stdinFile;
    FILE *standardOutReal = dup(STDOUT_FILENO);
    FILE *standardInReal = dup(STDIN_FILENO);
    while (current)
    {
        if (current == '>')
        {
            if (current + 1 == '>')
            {
                if (current + 1 == '\0')
                {
                    stdoutFile = open(current++, O_WRONLY | O_CREAT | O_APPEND, 0644);
                }
                else
                {
                    stdoutFile = open(current + 1, O_WRONLY | O_CREAT | O_APPEND, 0644);
                }
            }
            else if (current + 1 == '\0')
            {
                stdoutFile = open(current++, O_WRONLY | O_CREAT, 0644);
            }
            else
            {
                stdoutFile = open(current + 1, O_WRONLY | O_CREAT, 0644);
            }
        }
        else if (current == '<')
        {
            if (current + 1 == '\0')
            {
                stdinFile = open(current++, O_RDONLY, 0644);
            }
            else
            {
                stdinFile = open(current + 1, O_RDONLY, 0644);
            }
        }else{
            
        }
    }
    if (stdoutFile){
        dup2(stdoutFile, STDOUT_FILENO);
    }
    if (stdinFile){
        dup2(stdinFile, STDIN_FILENO);
    }
}

void cd(char ** args){
    char dir[1000];
    if (args[1]){
        chdir(args[1]);
    }else{
        char *homedir = getenv("HOME");
        chdir(homedir);
    }
}
