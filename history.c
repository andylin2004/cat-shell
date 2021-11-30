#include "history.h"

void openHistory(){
    char *homedir = getenv("HOME");
    int i;
    for (i = 0; i < PATH_MAX; i++){
        catshDirectory[i] = '\0';
    }
    strcat(catshDirectory, homedir);
    strcat(catshDirectory, "/.catsh_history");
    historyFile = open(catshDirectory, O_RDWR | O_APPEND | O_CREAT, 0777);
}

void writeCommandToHistory(char* command){
    openHistory();
    write(historyFile, command, strlen(command) * sizeof(char));
}

void readHistory(){
    openHistory();
    struct stat fileInfo;
    stat(catshDirectory, &fileInfo);
    int fileSize = fileInfo.st_size;
    char *historyFileContents = malloc(fileSize + sizeof(char));
    read(historyFile, historyFileContents, fileSize + sizeof(char));
    historyLength = countDelimiters(historyFileContents, '\n') - 1;
    history = parse_args(historyFileContents, '\n');
}

void printHistory(){
    int i;
    readHistory();
    if (historyLength - 1){
        printf("History of commands used: \n");
        for (i = 0; i < historyLength - 1; i++)
        {
            printf("%d: %s\n", i, history[i]);
        }
    }else{
        printf("No commands in history.\n");
    }
}

void runHistory(char *input){
    int indice;
    sscanf(input, "%d", &indice);
    if (history == NULL)
    {
        readHistory();
    }
    if (indice >= 0 && indice <= historyLength){
        printf("%s\n", history[indice]);
        executeLine(history[indice]);
    }
}