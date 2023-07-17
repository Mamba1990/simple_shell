#include "shell.h"
/**
 *_eputs - displays a string
 * @str: string input
 * Return: nothing
 */
void _eputs(char *s)
{
	int j = 0;

	if (!s)
		return;
	while (s[j] != '\0')
	{
		_eputchar(s[j]);
		j++;
	}
}

/**
 * _eputchar - puts the character to stderr
 * @cc: the  character to be  written
 * Return: 1 success and -1 failure
 */
int _eputchar(char cc)
{
	static int j;
	static char buff[WRITE_BUFF_S];

	if (cc == BUFF_FLUSH || j >= WRITE_BUFF_S)
	{
		write(2, buff, j);
		j = 0;
	}
	if (cc != BUFF_FLUSH)
		buff[j++] = cc;
	return (1);
}

/**
 * _putfd - puts the character into filedescriptor
 * @cc: character to write
 * @f: file's descriptor
 * Return: 1  success, -1 failure
 */
int _putfd(char cc, int f)
{
	static int j;
	static char buff[WRITE_BUFF_S];

	if (cc == BUFF_FLUSH || j >= WRITE_BUFF_S)
	{
		write(f, buff, j);
		j = 0;
	}
	if (cc != BUFF_FLUSH)
		buff[j++] = cc;
	return (1);
}

/**
 *_putsfd - displays a string
 * @s: string input
 * @f: filedescriptor
 * Return: characters' number
 */
int _putsfd(char *s, int f)
{
	int j = 0;

	if (!s)
		return (0);
	while (*s)
	{
		j += _putfd(*s++, f);
	}
	return (j);
}
