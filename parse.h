#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

char ** parse_args(char *code);
int count_args(char *code);
void standardize(char *code);