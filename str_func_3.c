#include "shell.h"

/**
* _strncpy - copies a string
* @dest: input value
* @src: input string
*@n: input integer
* Return: dest
*/
char *_strncpy(char *dest, char *src, int n)
{
	int j, i;
	char *ss = dest;

	j = 0;
	while (src[j] != '\0' && j < n - 1)
	{
		dest[j] = src[j];
		j++;
	}
	if (j < n)
	{
		i = j;
		while (i < n)
		{
			dest[i] = '\0';
			i++;
		}
	}
	return (ss);
}
/**
* _strncat - concatenate two strings
* @dest: input
* @src: input
* @n: input integer
* Return: dest
*/
char *_strncat(char *dest, char *src, int n)
{
	int j, i;
	char *ss = dest;

	j = 0;
	i = 0;
	while (dest[j] != '\0')
		j++;
	while (src[i] != '\0' && i < n)
	{
		dest[j] = src[i];
		j++;
		i++;
	}
	if (i < n)
		dest[j] = '\0';
	return (ss);
}
/**
 * _strchr - locates a character in a string.
 * @ss:  input string
 * @cc:  input char
 *
 * Return: location of charachter or NULL
 */
char *_strchr(char *ss, char cc)
{
	do {
		if (*ss == cc)
			return (ss);
	} while (*ss++ != '\0');

	return (NULL);
}
