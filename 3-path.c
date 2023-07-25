#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_PATH_LENGTH 1024

/**
 * printPathDirectories - Prints all directories listed in the PATH
 * environment variable, one per line.
 */

int printPathDirectories(int argc, char *argv[])
{
    char *path, *dir, *cmd_path;
    size_t path_len;
    int cmd_found = 0;
    char *cmd_name = argv[1];

    while (dir != NULL)
        {
                /* Check each directory for the command you want to run */
                printf("%s\n", dir);
                dir = strtok(NULL, ":");
        }

    /* Ensure proper usage*/
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s COMMAND\n", argv[0]);
        exit(1);
    }

    /* Get PATH environment variable */
    path = getenv("PATH");
    if (path == NULL)
    {
        fprintf(stderr, "Failed to retrieve PATH environment variable\n");
        exit(1);
    }

    /*Allocate memory for cmd_path */
    path_len = strlen(path);
    cmd_path = (char *)malloc(path_len + strlen(cmd_name) + 2);
    if (cmd_path == NULL)
    {
        fprintf(stderr, "Failed to allocate memory\n");
        exit(1);
    }

    /*Loop through each directory in PATH */
    dir = strtok(path, ":");
    while (dir != NULL)
    {
        /* Construct full path of command */
        snprintf(cmd_path, MAX_PATH_LENGTH, "%s/%s", dir, cmd_name);

        /* Check if command exists */
        if (access(cmd_path, X_OK) == 0)
        {
            cmd_found = 1;
            break;
        }

        /* Move to next directory */
        dir = strtok(NULL, ":");
    }

    /* If command not found, exit */
    if (!cmd_found)
    {
        fprintf(stderr, "Command not found in PATH\n");
        free(cmd_path);
        exit(1);
    }

    /* Execute command */
    pid_t pid;
    if ((pid = fork()) < 0)
    {
        perror("Failed to fork");
        free(cmd_path);
        exit(1);
    }
    else if (pid == 0)
    {
        /* We are in the child process */
        char *args[] = {cmd_name, NULL};
        execv(cmd_path, args);
        /* execv only returns on error */
        perror("execv failed");
        free(cmd_path);
        exit(1);
    }
    else
    {
	    /* We are in the parent process*/
	    int status;

	    if (waitpid(pid, &status, 0) == -1)
	    {
		    perror("Failed to wait for child process");
		    free(cmd_path);
		    exit(1);
	    }
	    if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	    {
		    fprintf(stderr, "Child process exited with error\n");
		    free(cmd_path);
		    exit(1);
	    }
	    free(cmd_path);
	    exit(0);
    }
}
