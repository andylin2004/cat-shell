#include "history.h"

void openHistory(){
    historyFile = open(".catsh_history", O_RDWR | O_APPEND | O_CREAT, 0777);
}

void writeCommandToHistory(char* command){
    openHistory();
    write(historyFile, command, strlen(command) * sizeof(char));
}

void readHistory(){
    openHistory();
    struct stat fileInfo;
    int i;
    stat(".catsh_history", &fileInfo);
    int fileSize = fileInfo.st_size;
    char *historyFileContents = malloc(fileSize + sizeof(char));
    read(historyFile, historyFileContents, fileSize + sizeof(char));
    int historyLength = countDelimiters(historyFileContents, '\n');
    history = parse_args(historyFileContents, '\n');
    printf("History of commands used: \n");
    for (i = 0; i < historyLength - 2; i++)
    {
        printf("%d: %s\n", i, history[i]);
    }
}