#include "parse.h"
#include <signal.h>

void executeLine(char *input);
void cd(char ** args);
char **redirectionParseAndSetup(char **input);