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





#endif
