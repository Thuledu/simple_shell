#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX_VARIABLE_LENGTH 100

/**
 * replace_variables - Replace variables in a command with their values.
 * Description: Replaces the $?, $$, and environment variables 
 * in a command with their respective values.
 * Arguments:The command to replace variables in.
 * Return: The new string with variables replaced or NULL on failure.
 */
char *replace_variables(char *command, int last_command_exit_status)
{
    static char new_command[MAX_COMMAND_LENGTH];
    memset(new_command, 0, sizeof(new_command));
    
    char *p = command;
    char *q = new_command;

    while (*p != '\0') {
        if (*p == '$') {
            /* Process variable substitution */
            if (p[1] == '$') {
                /* $$ variable: Process ID of shell process */
                sprintf(q, "%d", getpid());
                p += 2;
                q += strlen(q);
            } else if (p[1] == '?') {
                /* $? variable: Exit status of last command*/
                sprintf(q, "%d", WEXITSTATUS(last_command_exit_status));
                p += 2;
                q += strlen(q);
            } else if (p[1] == '{') {
                /* Environment variables: ${NAME}*/
                char *env_name_start = p + 2;
                char *env_name_end = strchr(env_name_start, '}');
                if (env_name_end == NULL) {
                    fprintf(stderr, "Error: Invalid environment variable syntax: %s\n", p);
                    return NULL;
                }
                size_t env_name_length = env_name_end - env_name_start;
                char env_name[MAX_VARIABLE_LENGTH];
                memcpy(env_name, env_name_start, env_name_length);
                env_name[env_name_length] = '\0';

                char *env_value = getenv(env_name);
                if (env_value == NULL) {
                    fprintf(stderr, "Error: Environment variable not found: %s\n", env_name);
                    return NULL;
                }

                strcat(q, env_value);
                p = env_name_end + 1;
                q += strlen(q);
            } else {
                *q++ = *p++;
            }
        } else {
            *q++ = *p++;
        }

        if (q - new_command >= MAX_COMMAND_LENGTH) {
            fprintf(stderr, "Error: Command too long: %s\n", command);
            return NULL;
	}
    }
    return strdup(new_command);
}

