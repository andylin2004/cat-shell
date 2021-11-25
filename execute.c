#include "execute.h"

void cd(char **args);
char **redirectionParseAndSetup(char **input);
void popenTest();
void executeCommand(char **commands, int pipes);
void executeCommandFork(char **commands, int start, int end);
int standardOutReal;
int standardInReal;
int status;
int *pipefd;
int pipeNum = 0;
int pipes;

void executeLine(char *input)
{
    input = standardizeString(input);
    int numCommands = countDelimiters(input, ';');
    char **commands = parse_args(input, ';');
    char **args;
    int i;
    int redirect;
    for (i = 0; i < numCommands; i++)
    {
        redirect = countDelimiters(commands[i], '<') + countDelimiters(commands[i], '>') - 2;
        pipes = countDelimiters(commands[i], '|') - 1;
        args = parse_args(commands[i], ' ');
        if (fork())
        {
            wait(&status);
        }
        else
        {
            if (strcmp(args[0], "cd") == 0)
            {
                cd(args);
            }
            else if (strcmp(args[0], "exit") == 0)
            {
                kill(getppid(), SIGTERM); //ppid is the shell
            }
            if (redirect)
            {
                standardOutReal = dup(STDOUT_FILENO);
                standardInReal = dup(STDIN_FILENO);
                args = redirectionParseAndSetup(args);
            }
            executeCommand(args, pipes);
            // execvp(args[0], args);
            if (redirect || pipes)
            {
                dup2(standardInReal, STDIN_FILENO);
                dup2(standardOutReal, STDOUT_FILENO);
                close(standardInReal);
                close(standardOutReal);
            }
        }
    }
}

void executeCommand(char **commands, int pipes) //this will deal with pipings
{
    char **args;
    pipefd = malloc(sizeof(int) * pipes);
    int i;
    for (i = 0; i < pipes; i++){
        pipe(pipefd + i * 2);
    }

    executeCommandFork(commands, 0, 0);

    for (i = 0; i < pipes; i++){
        wait(&status);
    }
    for (i = 0; i < pipes * 2; i++){
            close(pipefd[i]);
        }

    pipeNum = 0;
}

void executeCommandFork(char **commands, int start, int end){
    char **args;
    int i;
    for (; end < lengthOfArray(commands) && *commands[end] != '|'; end++);
    int newStart = end + 1;
    end--;
    args = malloc(end - start + 1);
    args[end - start] = NULL;
    for (; end >= start; end--)
    {
        args[end - start] = commands[end];
    }
    dup2(standardOutReal, STDOUT_FILENO);
    if (fork() == 0)
    {
        printf("%d\n", pipeNum);
        if (pipeNum + 1 < pipes * 2)
        {
            dup2(pipefd[pipeNum + 1], STDOUT_FILENO);
        }

        if (pipeNum - 2 >= 0){
            dup2(pipefd[pipeNum - 2], STDIN_FILENO);
        }
        
        for (i = 0; i < pipes * 2; i++){
            close(pipefd[i]);
        }
        execvp(args[0], args);
    }else{
        pipeNum += 2;
        if (pipeNum <= pipes * 2){
            executeCommandFork(commands, newStart, newStart);
        }
    }
}

char **redirectionParseAndSetup(char **input)
{
    char **current = input;
    int stdoutFile;
    int stdinFile;
    char **newInput = malloc(sizeof(input));
    int i = 0;

    while (*current)
    {
        if (**current == '>')
        {
            if (*(*current + 1) == '>')
            {
                current++;
                stdoutFile = open(*current, O_WRONLY | O_CREAT | O_APPEND, 0777);
            }
            else
            {
                current++;
                stdoutFile = open(*current, O_WRONLY | O_CREAT | O_TRUNC, 0777);
            }
        }
        else if (**current == '<')
        {
            current++;
            stdinFile = open(*current, O_RDONLY, 0777);
        }
        else
        {
            newInput[i] = *current;
            i++;
        }
        current++;
    }
    newInput[i] = NULL;
    if (stdoutFile)
    {
        dup2(stdoutFile, STDOUT_FILENO);
        close(stdoutFile);
    }
    if (stdinFile)
    {
        dup2(stdinFile, STDIN_FILENO);
        close(stdinFile);
    }
    return newInput;
}

void cd(char **args)
{
    char dir[1000];
    if (args[1])
    {
        chdir(args[1]);
    }
    else
    {
        char *homedir = getenv("HOME");
        chdir(homedir);
    }
}
