#include <stdlib.h>
#include <string.h>
#include "main.h"

/**
 * _unsetenv - Deletes a variable name from the environment.
 * @name: The name of the environment variable to delete.
 *
 * Return: 0 if successful, -1 otherwise.
 */
int _unsetenv(const char *name)
{
	size_t name_len = strlen(name);
	char **ep = environ;

	while (*ep != NULL)
	{
		if (strncmp(*ep, name, name_len) == 0 && (*ep)[name_len] == '=')
		{
			/* Found entry, remove it */
			char **tmp = ep;
			while (*tmp != NULL)
			{
				*tmp = *(tmp + 1);
				tmp++;
			}
			return (0);
		}
		ep++;
	}
	return (-1); /* Variable not found */
}
