#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * cd_handler - Changes the current directory of the process.
 * Description: Changes the current directory of the process 
 * to the given directory, or to the HOME directory if no 
 * directory is given, also updates the environment variable PWD accordingly.
 * Arguments:The directory to change to, or NULL.
 * Return: 0 (success), or -1 (failure).
 */
int cd_handler(char *directory)
{
    static char previous_directory[MAX_PATH_LENGTH];

    /* Save the current directory for use with the cd - command */
    if (getcwd(previous_directory, sizeof(previous_directory)) == NULL) {
        fprintf(stderr, "Error: Unable to get current directory.\n");
        return -1;
    }

    /* If no directory is specified, change to the HOME directory */
    if (directory == NULL) {
        directory = getenv("HOME");
    }

    /* Change to the specified directory*/
    if (chdir(directory) != 0) {
        fprintf(stderr, "Error: Unable to change directory to %s.\n", directory);
        return -1;
    }

    /* Update the PWD environment variable*/
    if (setenv("PWD", directory, 1) != 0) {
        fprintf(stderr, "Error: Unable to update PWD environment variable.\n");
        return -1;
    }

    /* Print the new current directory*/
    char current_directory[MAX_PATH_LENGTH];
    if (getcwd(current_directory, sizeof(current_directory)) != NULL) {
        printf("%s\n", current_directory);
    } else {
        fprintf(stderr, "Error: Unable to get current directory.\n");
        return -1;
    }

    return 0;
}
