#include "execute.h"

int main() {
    while (1) {
        char path[1000];
        getcwd(path,1000);
        char ** code;
        int n;
        n = countDelimiters(path,'/');
        code = parse_args(path, '/');
        printf("%s %s catsh$ ", getlogin(),code[n-2]);
        fflush(stdout);
        char command[1000] = {0};
        read(STDIN_FILENO, command, 100);
        executeLine(command);
    }
    return 0;
}
