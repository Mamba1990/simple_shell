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
	int src_length = 0;

	for ( ; src_length < n && src[src_length] != '\0' ; src_length++)
	{
		dest[src_length] = src[src_length];
	}
	for ( ; src_length < n; src_length++)
	{
		dest[src_length] = '\0';
	}
	return (dest);
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
	int dest_length = 0;
	int src_length = 0;

	while (*(dest + dest_length) != '\0')
	{
		dest_length++;
	}
	while (src_length < n && *(src + src_length) != '\0')
	{
		dest[dest_length] = src[src_length];
		dest_length++;
		src_length++;
	}
	dest[dest_length] = '\0';
	return (dest);
}
/**
 * _strchr - locates a character in a string.
 * @s:  input string
 * @c:  input char
 *
 * Return: location of charachter or NULL
 */

char *_strchr(char *s, char c)
{
	int j;

	j = 0;
	while (*(s + j) >= '\0')
	{
		if (s[j] == c)
		{
			return (&s[j]);
		}
		j++;
	}
return (NULL);
}
