#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define SIZE 1000

char ** parse_args(char *code);
int count_args(char *code);
