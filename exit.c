#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int exit_builtin(void);
void exit_handler(int status);

/**
  * exit_builtin - Exit shell
  * Return: Always 0
  */
int exit_builtin(void)
{
        exit(EXIT_SUCCESS);
}

/**
 * exit_handler - Handle exit shell command with status argument
 *
 * Description: Exits the shell process with the given status code.
 * Arguments:   The integer status code to be used for exiting the shell.
 * Returns:     Does not return.
 */
void exit_handler(int status)
{
    /* Exit the shell process with the given status code*/
    exit(status);
}
