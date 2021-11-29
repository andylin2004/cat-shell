# CAT (Christopher, Andy, Theo) Shell.

## Shell Features
- Current Working Directory and Username in the Shell line.
- Executes commands using execvp.
- ";" separates different commands.
- Redirections
    - "<" and ">" indicate reading from and writing to a file.
    - ">>" indicate appending to a file.
    - Redirection behavior is similar to bash.
- "|" represents simple piping.
- Multiple redirections and pipes are supported on the same line.
- cd to different directories, including the user root directory and directories from the user root directories using "~"
- History
    - View previously entered commands with `history`.
    - Enter a previously entered command with history [list number]:
        
        eg: 
        ``` 
        catsh$ history 69
        ```

## Features Attempted/Work In progress
- Using Arrow Keys as a method to call previous functions and to move text field cursor between characters
- Using Tab in the same way as Bash

## Noted Bugs
- You cannot use pipes or redirections on the same command as cd, exit, or history. (I don't expect anyone to do this anyways, unless you are a weird shell user.)