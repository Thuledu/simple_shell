#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * main - simple UNIX command line interpreter
 * Return: always 0
 */
int main(void)
{
        char *command = NULL;
        size_t command_size = 0;
	char *prompt = "(simple_shell) $ ";
	char *lineptr = NULL;
	size_t p = 0;
	ssize_t nchars_read;

        while (1)
        {
                printf("%s ", prompt); /* display prompt */
                fflush(stdout); /* flush output buffer */

                if (getline(&command, &command_size, stdin) == -1) /* read command line */
                {
			 nchars_read = getline(&lineptr, &p, stdin);
			 
			 if (nchars_read == -1)
			 {
				 printf("Exiting the shell....\n");
				 free(lineptr);
				 exit(1);
			 }
                        if (feof(stdin)) /* handle end of file */
                        {
                                printf("\n");
                                exit(EXIT_SUCCESS);
                        }
                        else /* handle other errors */
                        {
                                perror("read");
                                exit(EXIT_FAILURE);
                        }
                }

                command[strcspn(command, "\n")] = '\0'; /* remove trailing newline */

                if (access(command, X_OK) == -1) /* check if file is executable */
                        fprintf(stderr, "%s: command not found\n", command);
                else
                {
                        pid_t child_pid;

                        child_pid = fork();
                        if (child_pid == -1) /* handle fork error */
                        {
                                perror("fork");
                                exit(EXIT_FAILURE);
                        }

                        if (child_pid == 0) /* child process */
                        {
                                char *argv[] = {command, NULL};

                                execve(command, argv, environ);
                                perror("execve"); /* handle execve error */
                                exit(EXIT_FAILURE);
                        }
                        else /* parent process */
                                wait(NULL);
                }
        }

        free(command); /* free memory allocated for command buffer */

        return (0);
}
