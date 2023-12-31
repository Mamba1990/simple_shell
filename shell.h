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
#define _CMD_AND	2
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

/**
 *struct builtIn - structures a string and its suitable function
 *@type: command flag's builtin
 *@func:  function
 */
typedef struct builtIn
{
	char *type;
	int (*func)(info_t *);
} builtinTable;

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
char **_strtow(char *s, char *dl);
char **_strtow_2(char *s, char dl);

/* Memory Functions */
char *_memset(char *s, char b, unsigned int n);
void f_free(char **ss);
void *_realloc(void *p, unsigned int oldSize, unsigned int newSize);
int b_free(void **p);

/* Supplumentary Functions */

int _interactive(info_t *inf);
int isDelim(char cc, char *dl);
int _isalpha(int c);
int _atoi(char *str);

/* Linked Lists Functions */

/* 1 */
list_t *addNodeEnd(list_t **h, const char *s, int number);
size_t listStrPrinter(const list_t *head);
int nodeDeleterAtIndex(list_t **h, unsigned int idx);
void freeList(list_t **head_p);

/* 2 */
size_t listLength(const list_t *head);
char **listToStrings(list_t *h);
size_t printList(const list_t *head);
list_t *nodeStartsWith(list_t *node, char *pfix, char cc);
ssize_t indexNodeGetter(list_t *h, list_t *_node);

/* Errors Functions */
/* 1 */
void _eputs_(char *s);
int _eputchar_(char cc);
int _putfd_(char cc, int f);
int _putsfd_(char *s, int f);

/* 2 */
int _erratoi_(char *str);
void errorPrinter(info_t *inf, char *errs);
int dPrinter(int iput, int fid);
char *numberConverter(long int number, int b, int flgs);
void removeComment(char *buff);

/* Informations Getter Functions */
void clearInfo(info_t *inf);
void infoSetter(info_t *inf, char **av);
void freeInfo(info_t *inf, int all_f);

/* Environ Functions */
/* 1 */
int myEnv(info_t *inf);
char *getEnv(info_t *inf, const char *name);
int mySetEnv(info_t *inf);
int myUnsetEnv(info_t *inf);
int envListPopulator(info_t *inf);
/* 2 */
char **getEnviron(info_t *inf);
int unsetEnv(info_t *inf, char *var);
int setEnv(info_t *inf, char *var, char *value);

/* History Functions */
char *fileHistoryGetter(info_t *inf);
int historyWriter(info_t *inf);
int historyReader(info_t *inf);
int buildHistoryList(info_t *inf, char *buff, int lineCount);
int renumberHistory(info_t *inf);

/* Path Functions */
int isCommd(info_t *inf, char *_path);
char *charsDuplicator(char *path_str, int _start, int _stop);
char *pathFinder(info_t *inf, char *path_str, char *_cmd);

/* Builters Functions */

/* 1 */
int myExit(info_t *inf);
int myCd(info_t *inf);
int myHelper(info_t *inf);

/* 2 */
int myHistory(info_t *inf);
int unsetAlias(info_t *inf, char *_str);
int aliasSetter(info_t *inf, char *_str);
int aliasPrinter(list_t *_node);
int myAlias(info_t *inf);

/* Chain Functions */
int is_chain(info_t *inf, char *buff, size_t *ptr);
void check_chain(info_t *inf, char *buff, size_t *ptr,
		size_t j, size_t length);
int replace_alias(info_t *inf);
int replace_vars(info_t *inf);
int replace_string(char **ol, char *ne);

/* Line Getter Functions */
ssize_t inputBuff(info_t *inf, char **buff, size_t *length);
ssize_t inputGetter(info_t *inf);
ssize_t buffReader(info_t *inf, char *buff, size_t *j);
int _getline_(info_t *inf, char **p, size_t *leng);
void sigintHandler(__attribute__((unused))int sigNum);

/* hsh Functions */
int _hsh_(info_t *inf, char **av);
int builtinfinder(info_t *inf);
void cmdFinder(info_t *inf);
void forkComd(info_t *inf);


#endif
