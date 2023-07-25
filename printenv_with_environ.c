#include <stdio.h>
#include <stdlib.h>
#include "main.h"

extern char **environ;

/**
 * printenv - Prints the environment using the global variable environ.
 * Return: Always EXIT_SUCCESS.
 */
int printenv(void)
{
    char **env = environ;

    while (*env)
    {
        printf("%s\n", *env);
        env++;
    }

    return EXIT_SUCCESS;
}
