#include "parse.h"
#ifndef HISTORY_H
#define HISTORY_H
#include "history.h"
#endif
#include <signal.h>
#include <sys/wait.h>

/**
 * @brief Takes in a line entered into the terminal and executes the line.
 * 
 * @param input The line entered into the terminal.
 */
void executeLine(char *input);
/**
 * @brief Changes the current working directory to the directory specified by the newDirectory param.
 * 
 * @param newDirectory The directory to change the current working directory to.
 */
void cd(char **newDirectory);
/**
 * @brief Parses out the files to redirect to, and redirects standard in and/or standard out to the given files to redirect to. Strips the char* array of the redirection elements.
 * 
 * @param input The array of char* that represent what to execute in the shell.
 * @return char** The char* array without the redirection args. 
 */
char **redirectionParseAndSetup(char **input);
/**
 * @brief Executes a command that has already been split in a char* array. This is also where the pipes are handled.
 * 
 * @param commands A char* array consisting of a command that has been split into a char* array.
 * @param pipes The number of pipes that are in the command. This will be used for piping if the command involves piping.
 */
void executeCommand(char **commands, int pipes);
/**
 * @brief Forks off the executeCommand function and executes one section of a command that involves piping, split off by the '|' deliminator
 * 
 * @param commands A char* array consisting of a command that has been split into a char* array.
 * @param start The start indice, determined by the previous fork of the execute based on where the '|' was at.
 * @param currentPipeSet The current pipe set that the code is working on. (Will use currentPipeSet - 2 and currentPipeSet + 1)
 */
void executeCommandFork(char **commands, int start, int currentPipeSet);
/**
 * @brief Closes the pipes where standard in and out is fed and obtained from.
 * 
 */
void closePipes();

int standardOutReal;
int standardInReal;
int status;
int *pipefd;
int pipes;