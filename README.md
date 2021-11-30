# CAT (Christopher, Andy, Theo) Shell

## Shell Features
- Current Working Directory and Username in the Shell line.
- Executes commands using execvp.
- ";" separates different commands.
- Redirections
    - `<` and `>` indicate reading from a file to standard in and writing to a file from standard out respectively.
    - `>>` indicate writing and appending to a file.
    - Redirection behavior is similar to bash.
- Piping using `|`.
- Multiple redirections and pipes are supported on the same line.
- cd to different directories, including the user root directory and directories from the user root directories using "~"
- History
    - View previously entered commands in a list with `history`.
    - Enter a previously entered command with `history [list number]`:
        - eg: 
        ``` 
        catsh$ history 69
        ```
        - This also works with negative numbers, in order to do the last command or a command done two entries ago.
        eg:
        ```
        catsh$ history -420
        ```

## Launch Codes

### Cloning the Project
Run:
```
$ git clone https://github.com/andylin2004-systems/project_01.git
```

### Building the Project
Ensure that you have gcc installed on your system.
Run:
```bash
$ cd /path/to/project_01
$ make
```

### Running the Project
Run:

```bash
$ cd /path/to/project_01
$ make run
```
Alternatively, you can also run: 
```bash
$ cd /path/to/project_01
$ ./shell
```

## Features Attempted
- Using Arrow Keys as a method to call previous functions and to move text field cursor between characters, as intercepting key inputs would've been too complicated for us to do.
- Using Tab in the same way as Bash. This would involve intercepting key inputs, and we had issues with this.
- Redirection behavior found on Zsh.

## Noted Bugs
- You cannot change directory with arguments ``` ~[username] ```. 
- Pressing the arrow buttons will generate the ascii keys, instead of moving the cursor or going through the history.

## Function Headers

```c
int main();
void executeLine(char *input);
void cd(char **args);
char **redirectionParseAndSetup(char **input);
void executeCommand(char **commands, int pipes);
void executeCommandFork(char **commands, int start, int end, int pipeNum);
void closePipes();
void writeCommandToHistory(char *command);
void readHistory();
void printHistory();
void runHistory(char* input);
char ** parse_args(char *code, char delim);
int countDelimiters(char *code, char delim);
int arrayOfStringsLength(char **array);
char *standardizeString(char *oldString);
int lengthOfArray(char **array);
char * squigglyToHomeDirectory(char* string);
```