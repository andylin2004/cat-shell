#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

int main() {
    while (1){
        printf("catsh $");
        fflush(stdout);
        char command[100] = {0};
        read(STDIN_FILENO, command, 100);
        parse_args(command);
    }
}
