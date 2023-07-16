#include "shell.h"
/**
 *_eputs - print a string
 * @str: string
 * Return: void
 */
void _eputs(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_eputchar(str[j]);
		j++;
	}
}

/**
 * _eputchar - print the character
 * @c: character to write
 * Return: 1 on success and -1 on failure
 */
int _eputchar(char c)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}

/**
 * _putfd - print the character into filedescriptor
 * @c: character to write
 * @f: filedescriptor
 * Return: 1 on success and -1 on failure
 */
int _putfd(char c, int f)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(f, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}

/**
 *_putsfd - print a string
 * @str: string
 * @f: filedescriptor
 * Return: number of characters
 */
int _putsfd(char *str, int f)
{
	int j = 0;

	if (!str)
		return (0);
	while (*str)
	{
		j += _putfd(*str++, f);
	}
	return (j);
}
