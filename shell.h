#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

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
/* for command chaining */
#define CMD_NORM	0
#define CMD_OR	        1
#define CMD_AND	        2
#define CMD_CHAIN       3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE	0
#define USE_STRTOK	0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory management */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;
/*his.c*/
int renumber_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int read_history(info_t *info);
int write_history(info_t *info);
char *get_history_file(info_t *info);

/*stringsandnodes*/
size_t list_len(const list_t *head);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *head);
ssize_t get_node_index(list_t *head, list_t *node);

/*exits.c*/
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);
char *_strchr(char *s, char c);
/*memory*/
int bfree(void **ptr);

int main(int argc, char **argv);

/*shell1.c*/
void display_prompt(const char* prompt);

/*var.c*/
int is_chain(info_t *info, char *buf, size_t *p);
void check_chain(info_t *info, char *buf, size_t *p, size_t b, size_t len);
int replace_alias(info_t *info);
int replace_vars(info_t *info);
void replace_string(char **old, char *new);

/*shell2.c*/
void display_prompt(const char* prompt);
/*shell3.c*/
void display_prompt(const char* prompt);
void write_error(const char* error_msg);
int command_exists(const char* command);
void get_full_path(const char* command, char* path_buf);

/*shell4.c*/
void get_full_path(const char* command, char* path_buf);

/*shell5.c*/
int print_env(info_t *info);
char *get_env_var(info_t *info, const char *name);
int set_env_var(info_t *info);
int unset_env_var(info_t *info);
int populate_env_list(info_t *info);

/*shell6.c*/
ssize_t input_buf(info_t *info, char **buf, size_t *len);
ssize_t get_input(info_t *info);
void sigintHandler(__attribute__((unused))int sig_num);

/*shell7.c*/
ssize_t num_chars = getline(&buffer, &bufsize, stdin);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/*shell8.c*/
int (*get_builtin(char *string))();
int env(void);
int _own_exit(void);

/*shell9.c*/

char **get_environ(info_t *info);
int _unsetenv(info_t *info, const char *var);
int _setenv(info_t *info, const char *var, const char *value);

/*shell10.c*/
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);
void help_pwd(void);

/*shell11.c*/
int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);
char **_strtok(char *line, char *delim);

/*shell13.c*/
int shellby_alias(char **args, char __attribute__((__unused__)) **front);
void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);

/*shell15.c*/
int main(int argc, char **argv);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

#endif
