#include <stdlib.h>
#include <string.h>
#include "main.h"

/**
 * _setenv - Sets a variable name and value in the environment.
 * @name: A pointer to a string containing the name of the variable.
 * @value: A pointer to a string containing the value to set for the variable.
 * @overwrite: An integer flag indicating whether existing variables should be overwritten.
 * 
 * Return: 0 if successful, -1 otherwise.
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	size_t size = strlen(name) + strlen(value) + 2; /* add 2 for equals sign and null terminator */
	char *env_var = (char *) malloc(size);
	sprintf(env_var, "%s=%s", name, value);

	int result;
	if (getenv(name) != NULL)
	{
		if (overwrite == 0)
		{
			result = 0;
		}
		else
		{
			result = putenv(env_var);
		}
	}
	else
	{
		result = putenv(env_var);
	}
    
	return (result);
}
