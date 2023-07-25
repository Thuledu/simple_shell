#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/**
 * main - Prints the address of env and environ.
 * @argc: The number of arguments passed to the program.
 * @argv: An array of strings containing the arguments.
 * @env: An array of strings containing the environment variables.
 *
 * Return: Always 0.
 */
int env_and_environ(int argc, char *argv[], char *env[])
{
	char *environ;
	
	printf("Address of env: %p\n", (void *) env);
	printf("Address of environ: %p\n", (void *) environ);
	return (0);
}
