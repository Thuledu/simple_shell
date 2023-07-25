#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * env_builtin - Print the environment
 * Description: Print the current environment to stdout.
 * Returns: Always 0
 */
int env_builtin(void)
{
  extern char **environ;
  int i;
  for (i = 0; environ[i] != NULL; i++) {
    printf("%s\n", environ[i]);
  }
  return 0;
}
