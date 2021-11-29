#include <sys/stat.h>
#include "parse.h"

int historyFile;
char **history;

void writeCommandToHistory(char *command);
void readHistory();