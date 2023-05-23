#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;


/**
 * struct data - struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
    char **av;
    char *input;
    char **args;
    int status;
    int counter;
    char **_environ;
    char *pid;
} data_shell;

/**
 * struct sep_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct sep_list_s
{
    char separator;
    struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_list_s
{
    char *line;
    struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct r_var_list
{
    int len_var;
    char *val;
    int len_val;
    struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
    char *name;
    int (*f)(data_shell *datash);
} builtin_t;

/* aux_lists.c */
sep_list *add_sep_node_end(sep_list **head, char sep);
void free_sep_list(sep_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);

/* aux_lists2.c */
r_var *add_rvar_node(r_var **head, int lvar, char *var, int lval);
void free_rvar_list(r_var **head);

/* aux_str functions */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

/* aux_mem.c */
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

/* aux_str2.c */
char *_strdup(const char *s);
int _strlen(const char *s);
int _strncmp(const char *s1, const char *s2, int n);
char *_strndup(const char *s, int n);

/* env.c */
void _setenv(char *name, char *value);
void _unsetenv(const char *name);
void print_env(void);
int _getenv(const char *name);

/* execute.c */
int execute_cmd(data_shell *datash);

/* execute2.c */
int execute_builtin(data_shell *datash);
int check_for_builtins(data_shell *datash);
int check_access(char *command);

/* handle_errors.c */
void error_message(data_shell *datash);

/* holberton.h */
int _putchar(char c);
int _puts(char *str);
char *_getline(void);
char **tokenize(char *input, char *delim);
void *_calloc(unsigned int nmemb, unsigned int size);
void free_double_ptr(char **ptr);

/* path.c */
char *_getpath(void);
char *path_concat(char *dir, char *cmd);

/* shell.c */
void sigint_handler(int sig);
char *input_prompt(data_shell *datash);
void start_shell(data_shell *datash);
void init_shell(data_shell *datash);
void free_data(data_shell *datash);
void exit_shell(data_shell *datash);

/* str_functions.c */
int _atoi(char *s);
void reverse_string(char *s);
char *itoa(int num, char *str, int base);

/* str_functions2.c */
int is_num(char *str);
int only_digits(char *str);

/* string_manipulation.c */
char *_strtok(char *str, const char *delim);
int _strcnt(const char *str, char c);

#endif
