#include "shell.h"

/**
 * _strcpy - copies a string
 * @dst: input value
 * @sc: input tring
 *
 * Return: dest
 */
char *_strcpy(char *dst, char *sc)
{
	int j = 0;

	if (dst == sc || sc == 0)
		return (dst);
	while (sc[j])
	{
		dst[j] = sc[j];
		j++;
	}
	dst[j] = 0;
	return (dst);
}

/**
 * _strdup - creates a duplication of a string given
 * @s: string to be duplicated
 *
 * Return: pointer to dup
 */
char *_strdup(const char *s)
{
	int len = 0;
	char *dup;

	if (s == NULL)
		return (NULL);
	while (*s++)
		len++;
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	for (len++; len--;)
		dup[len] = *--s;
	return (dup);
}

/**
 *_puts - displays an input string
 *@str: the printed string
 *
 * Return: Nothing
 */

void _puts(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_putchar(str[j]);
		j++;
	}
}

/**
 * _putchar - writes a char  to stdout
 * @cc: char to be printed print
 *
 * Return: 1 success -1 failure
 */
int _putchar(char cc)
{
	static int j;
	static char buff[WRITE_BUFF_S];

	if (cc == BUFF_FLUSH || j >= WRITE_BUFF_S)
	{
		write(1, buff, j);
		j = 0;
	}
	if (cc != BUFF_FLUSH)
		buff[j++] = cc;
	return (1);
}
