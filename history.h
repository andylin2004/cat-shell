#include <sys/stat.h>
#include <limits.h>
#include "parse.h"
#include "execute.h"

int historyFile;
char **history;
int historyLength;
char catshDirectory[PATH_MAX];

/**
 * @brief Writes a command to the .catsh_history file (where previous commands are stored)
 * 
 * @param command The command to be written to the .catsh_history file
 */
void writeCommandToHistory(char *command);

/**
 * @brief Loads in the .catsh_history file (where previous commands are stored) as a char* array
 * 
 */
void readHistory();

/**
 * @brief Prints the previously executed commands from the .catsh_history file that is now stored in the char* array.
 * 
 */
void printHistory();

/**
 * @brief Executes a command that was stored in the .catsh_history file (where previous commands are stored) based on the given array indice corresponding to a previous command in the char* array
 * 
 * @param input The array indice corresponding to a previously executed terminal command that is now stored in .catsh_history and the char* array
 */
void runHistory(char* input);