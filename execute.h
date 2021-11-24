#include "parse.h"
#include <signal.h>
#include <errno.h>

void executeLine(char *input);
void cd(char ** args);
char **redirectionParseAndSetup(char **input);