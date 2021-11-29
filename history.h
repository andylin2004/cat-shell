#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int fileHistory;

void writeCommandToHistory(char *command);