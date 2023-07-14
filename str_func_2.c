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
 *_puts - prints an input string
 *@str: the printed string
 *
 * Return: Nothing
 */
void _puts(char *s)
{
	int j = 0;

	if (!s)
		return;
	for ( ;s[j] != '\0'; j++)
	{
		_putchar(s[j]);
		
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
