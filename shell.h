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

/* Buffer to read & write */
#define READ_BUFF_S 1024
#define WRITE_BUFF_S 1024
#define BUFF_FLUSH -1

/* The chaining's Command*/
#define _CMD_NORM	0
#define _CMD_OR		1
#define _CMD_AND		2
#define _CMD_CHAIN	3

/* To Covert Numbers */
#define _CONVERT_LOWERCASE	1
#define _CONVERT_UNSIGNED	2

/* To use system getline() ->1 */
#define _USE_GETLINE 0
#define _USE_STRTOK 0

#define _HIST_FILE	".simple_shell_history"
#define _HIST_MAX	4096

extern char **environ;

/* Singly Linked Structures */
/**
 * struct list_str - singly linked list
 * @number: member containing a number
 * @s: string member
 * @next: pointing the next node
*/
typedef struct list_str
{
	int number;
	char *s;
	struct list_str *next;
} list_t;

/**
 *struct infoPasser - passes psesudo argmts  into a function,
 *@arg: the generated string  from getline that conatians arguements
 *@argv: the generated array of strings from arg
 *@path: path constructed from str for the current command
 *@argc: count of the argm
 *@lineCount: count of the errors
 *@errNum: error's code for exit()s
 *@lineCountFlag: if on count this line of input
 *@f_name: filename of the program
 *@env: local copy of the environ
 *@environ: the modified copy by custom of environ from LL env
 *@history: node of the history
 *@alias: node of the alias
 *@envChanged: environ changed
 *@status: the return status of the last exec'd command
 *@cmdBuff: pointer of pointer 
 *@cmdBuffType: && or other command seperator symbols
 *@read_fd: file descriptor to read input
 *@histCount: count if history line number
 */
typedef struct infoPasser
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int lineCount;
	int errNum;
	int lineCountFlag;
	char *f_name;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int envChanged;
	int status;

	char **cmdBuff; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmdBuffType; /* CMD_type ||, &&, ; */
	int read_fd;
	int histCount;
} info_t;

#define _INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/* String Functions */
int _strlen(char *s);
int _strcmp(char *str1, char *str2);
char *starts_with(const char *str, const char *substr);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dst, char *sc);
char *_strdup(const char *s);
void _puts(char *s);
int _putchar(char c);
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);
char *_strchr(char *s, char c);
char **strtow(char *s, char *dl);
char **strtow2(char *s, char dl);

/* Memory Functions */
char *_memset(char *s, char b, unsigned int n);
void ffree(char **ss);
void *_realloc(void *p, unsigned int oldSize, unsigned int newSize);

/* Supplumentary Functions */

int interactive(info_t *inf);
int is_delim(char cc, char *dl);
int _isalpha(int c);
int _atoi(char *str);

/* Linked Lists Functions */
/* 1 */
list_t *add_node(list_t **h, const char *s, int number);
list_t *add_node_end(list_t **h, const char *s, int number);
size_t print_list_str(const list_t *head);
int delete_node_at_index(list_t **h, unsigned int idx);
void free_list(list_t **head_p);
/* 2 */
size_t list_len(const list_t *head);
char **list_to_strings(list_t *h);
size_t print_list(const list_t *head);
list_t *node_starts_with(list_t *node, char *pfix, char cc);
ssize_t get_node_index(list_t *h, list_t *_node);

/* Errors Functions */
/* 1 */
void _eputs(char *s);
int _eputchar(char cc);
int _putfd(char cc, int f);
int _putsfd(char *s, int f);





#endif
