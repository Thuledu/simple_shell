#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_INPUT_LENGTH 100
#define BUFFER_SIZE 1024
#define MAX_COMMAND_LENGTH 1024
#define MAX_ALIASES 100
#define MAX_VARIABLE_LENGTH 100


/**
 * Node - A structure to represent the nodes in a linked list
 * @data: A pointer to the data stored in the node
 * @next: A pointer to the next node in the list
 */
typedef struct node {
        char *data;
        struct node *next;
} Node;


/**
 * struct directory_s - singly linked list
 * @dir: directory name
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct directory_s
{
    char *dir;
    struct directory_s *next;
} directory_t;
directory_t *build_path_list(void);

extern char **environ;


/**
 * struct alias_s - singly linked list of aliases
 * @name: name of the alias
 * @value: value of the alias
 * @next: pointer to the next alias in the list
 **/
typedef struct alias_s
{
        char *name;
        char *value;
} alias_t;

int alias_builtin(char **args, alias_t *aliases);
void print_aliases(alias_t *aliases);
void print_alias(alias_t *aliases, char *alias_name);
void define_alias(alias_t *aliases, char *alias_name, char *alias_value);

void exit_handler(int status);
int exit_builtin(void);
int env_builtin(void);
int printenv(void);
int env_and_environ(int argc, char *argv[], char *env[]);
char *_getenv(const char *name);
int main(void); /*int execute(char **args, char **frnt); int execute(char **argv);*/
/*int main(int ac, char **argv);*/
void print_path_directories(void);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
int my_getline(char *buffer, size_t max_size);
void my_env(void);
int printPathDirectories(int argc, char *argv[]);
int cd_handler(char *directory);
char *replace_variables(char *command, int last_command_exit_status);

#endif
