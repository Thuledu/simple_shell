#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_aliases(alias_t *aliases);
void print_alias(alias_t *aliases, char *alias_name);
void define_alias(alias_t *aliases, char *alias_name, char *alias_value);


/**
 * print_aliases - prints all aliases
 * @aliases: an array of aliases
 **/
void print_aliases(alias_t *aliases)
{
        int i;

        for (i = 0; i < MAX_ALIASES; i++)
        {
                if (aliases[i].name != NULL)
                        printf("%s='%s'\n", aliases[i].name, aliases[i].value);
        }
}

/**
 * print_alias - prints an alias
 * @aliases: an array of aliases
 * @alias_name: the name of the alias to print
 **/
void print_alias(alias_t *aliases, char *alias_name)
{
        int i;

        for (i = 0; i < MAX_ALIASES; i++)
        {
                if (aliases[i].name != NULL && strcmp(aliases[i].name, alias_name) == 0)
                {
                        printf("%s='%s'\n", aliases[i].name, aliases[i].value);
                        return;
                }
        }
        fprintf(stderr, "alias: %s: not found\n", alias_name);
}

/**
 * define_alias - defines an alias
 * @aliases: an array of aliases
 * @alias_name: the name of the alias to define
 * @alias_value: the value of the alias to define
 **/
void define_alias(alias_t *aliases, char *alias_name, char *alias_value)
{
        int i;

        for (i = 0; i < MAX_ALIASES; i++)
        {
                if (aliases[i].name != NULL && strcmp(aliases[i].name, alias_name) == 0)
                {
                        free(aliases[i].value);
                        aliases[i].value = strdup(alias_value);
                        return;
                }
                else if (aliases[i].name == NULL)
                {
                        aliases[i].name = strdup(alias_name);
                        aliases[i].value = strdup(alias_value);
                        return;
                }
        }
        fprintf(stderr, "alias: too many aliases defined\n");
}

/**
 * alias_builtin - executes the alias builtin command
 * @args: an array of arguments passed to the command
 * @aliases: an array of aliases
 * Return: 1 if the shell should continue, 0 otherwise
 **/
int alias_builtin(char **args, alias_t *aliases)
{
        if (args[1])
	{
                print_aliases(aliases);
        }
	 else if (args[1][0] == '\'' || args[1][0] == '\"') /* defining one alias */
        {
                char *alias_name = strtok(args[1], "=\'\"");
                char *alias_value = strtok(NULL, "=\'\"");
                if (alias_value == NULL)
                        print_alias(aliases, alias_name);
                else
                        define_alias(aliases, alias_name, alias_value);
        }
        else /* printing multiple aliases */
        {
                int i;
                for (i = 1; args[i] != NULL; i++)
                        print_alias(aliases, args[i]);
        }
        return (1);
}
