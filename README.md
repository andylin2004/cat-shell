# CAT (Christopher, Andy, Theo) Shell.

Shell Features:
- Current Working Directory and Username in the Shell line.
- Executes commands using execvp.
- ";" separates different commands.
- Redirections
    - "<" and ">" indicate reading from and writing to a file.
    - ">>" indicate appending to a file.
    - Redirection behavior is similar to bash.
- "|" represents simple piping.
- Multiple redirections and up to two pipes are supported on a single line.
- cd to different directories, including the user root directory and directories from the user root directories using "~"

Features Attempted/ Work In progress: 
- Using Up Arrow Key as a method to call previous functions
- Using Tab in the same way as Bash
- Handling more than two pipes on the same line.

Noted Bugs:
- When using cd, sometimes an error gets printed out saying that it cannot find the directory, however function still works as intended.
- Piping works with up to two pipes. More pipes beyond that will cause issues with the shell.