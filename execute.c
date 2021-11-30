#include "execute.h"

void executeLine(char *input)
{
    writeCommandToHistory(input);
    if (strchr(input, '\n') == NULL){
        writeCommandToHistory("\n");
    }
    input = standardizeString(input);
    int numCommands = countDelimiters(input, ';');
    char **commands = parse_args(input, ';');
    char **args;
    int i;
    int j;
    int redirect;
    if (input[0] == '\0')
    {
        printf("\n");
    }
    else
    {
        for (i = 0; i < numCommands; i++)
        {
            if (commands[i])
            {
                redirect = countDelimiters(commands[i], '<') + countDelimiters(commands[i], '>') - 2;
                pipes = countDelimiters(commands[i], '|') - 1;
                args = parse_args(commands[i], ' ');
                if (strcmp(args[0], "cd") == 0)
                {
                    cd(args);
                    return;
                }else if (strcmp(args[0], "history") == 0){
                    if (args[1]){
                        runHistory(args[1]);
                    }else{
                        printHistory();
                    }
                    return;
                }
                else if (strcmp(args[0], "exit") == 0)
                {
                    kill(getppid(), SIGTERM); //ppid is the shell
                    exit(0);                  // if make is not used to run
                }
                if (redirect)
                {
                    standardOutReal = dup(STDOUT_FILENO);
                    standardInReal = dup(STDIN_FILENO);
                    args = redirectionParseAndSetup(args);
                }
                executeCommand(args, pipes);
                for (j = 0; j < pipes + 1; j++)
                {
                    wait(&status);
                }
                if (redirect)
                {
                    dup2(standardInReal, STDIN_FILENO);
                    dup2(standardOutReal, STDOUT_FILENO);
                    close(standardInReal);
                    close(standardOutReal);
                }
            }
        }
    }
}

void executeCommand(char **commands, int pipes) //this will deal with pipings
{
    pipefd = malloc(pipes * sizeof(int *));
    int i;
    int fd_max;
    for (i = 0; i < pipes; i++)
    {
        pipe(pipefd + i * 2);
    }

    executeCommandFork(commands, 0, 0, 0);
    closePipes();
    if (*pipefd){
        free(pipefd);
    }
}

void executeCommandFork(char **commands, int start, int end, int pipeNum)
{
    char **args;
    int i;
    int forked = fork();
    for (; end < lengthOfArray(commands) && *commands[end] != '|'; end++)
        ;
    int newStart = end + 1;
    end--;
    args = malloc(end - start + 2);
    args[end - start + 1] = NULL;
    for (; end >= start; end--)
    {
        args[end - start] = commands[end];
    }
    if (forked == 0)
    {
        if (pipeNum - 2 >= 0)
        {
            dup2(pipefd[pipeNum - 2], STDIN_FILENO);
        }

        if (pipeNum + 1 < pipes * 2)
        {
            dup2(pipefd[pipeNum + 1], STDOUT_FILENO);
        }

        closePipes();

        status = execvp(args[0], args);

        if (status){
            printf("catsh: command not found: %s\n", args[0]);
            return;
        }

        free(args);
        free(pipefd);
    }
    else
    {
        pipeNum += 2;
        if (pipeNum <= pipes * 2 && !status)
        {
            executeCommandFork(commands, newStart, newStart, pipeNum);
        }
    }
}

char **redirectionParseAndSetup(char **input)
{
    int standardOutTemp;
    int standardInTemp;
    char **current = input;
    char **newInput = malloc(lengthOfArray(input) * sizeof(char *));
    int i = 0;

    while (*current)
    {
        if (**current == '>')
        {
            if (*(*current + 1) == '>')
            {
                current++;
                standardOutTemp = open(*current, O_WRONLY | O_CREAT | O_APPEND, 0777);
            }
            else
            {
                current++;
                standardOutTemp = open(*current, O_WRONLY | O_CREAT | O_TRUNC, 0777);
            }
        }
        else if (**current == '<')
        {
            current++;
            standardInTemp = open(*current, O_RDONLY, 0777);
        }
        else
        {
            newInput[i] = *current;
            i++;
        }
        current++;
    }
    newInput[i] = NULL;
    if (standardOutTemp)
    {
        dup2(standardOutTemp, STDOUT_FILENO);
        close(standardOutTemp);
    }
    if (standardInTemp)
    {
        dup2(standardInTemp, STDIN_FILENO);
        close(standardInTemp);
    }
    newInput = realloc(newInput, sizeof(char *) * (i + 1));
    return newInput;
}

void cd(char **args)
{
    char *homedir = getenv("HOME");
    if (args[1])
    {
        if (args[1][0] == '~')
        {
            char *dir = args[1] + 1;
            char *completeDir = malloc((strlen(homedir) + strlen(dir)) * sizeof(char));
            strcat(completeDir, homedir);
            strcat(completeDir, dir);
            chdir(completeDir);
        }
        else if (args[1][0] != '~')
        {
            chdir(args[1]);
        }
    }
    else
    {
        chdir(homedir);
    }
}

void closePipes()
{
    int i;
    for (i = 0; i < pipes * 2; i++)
    {
        close(pipefd[i]);
    }
}