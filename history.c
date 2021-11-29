#include "history.h"

void writeCommandToHistory(char* command){
    if (!fileHistory){
        fileHistory = open(".catsh_history", O_WRONLY | O_APPEND | O_CREAT, 0777);
    }
    write(fileHistory, command, strlen(command) * sizeof(char));
}