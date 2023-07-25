#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * _getenv - Finds the value of the environment variable 'name'.
 * @name: The name of the variable to find.
 *
 * Return: A pointer to the value of the environment variable, or NULL if not found.
 */
char *_getenv(const char *name)
{
	char **envp;
	char *tok, *p, *key;
	const size_t len_name = strlen(name);
	const size_t buffer_size = len_name + 2;
	char *buffer = malloc(buffer_size);

	if (!buffer)
		return NULL;

	envp = environ;

	for (; (p = *envp) != NULL; envp++)
	{
		key = p;
		tok = buffer;

		for (; *p != '=' && tok < buffer + len_name && *p; p++, tok++)
			*tok = *p;

		*tok = '\0';

		if (strcmp(buffer, name) == 0)
			return ++p;
	}

	free(buffer);
	return NULL;
}
