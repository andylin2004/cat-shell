#include "parse.h"

int main() {
    while (1) {
        printf("ACT$: ");
        fflush(stdout);
        char command[100] = {0};
        read(STDIN_FILENO, command, 100);
        parse_args(command);
    }
    return 0;
}