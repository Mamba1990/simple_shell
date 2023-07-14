#include "shell.h"

/**
 * **strtow - toktenizes a string into words. 
 * @s: the input string
 * @dl: delimeter of string
 * Return: pointer to an array of strings, or NULL 
 */

char **strtow(char *s, char *dl)
{
	int i, j, k, n, num_words = 0;
	char **str;

	if (s == NULL || s[0] == 0)
		return (NULL);
	if (!dl)
		dl = " ";
	for (i = 0; s[i] != '\0'; i++)
		if (!is_delim(s[i], dl) && (is_delim(s[i + 1], dl) || !s[i + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	str = malloc((1 + num_words) * sizeof(char *));
	if (!str)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (is_delim(s[i], dl))
			i++;
		for (k = 0; !is_delim(s[i + k], d) && s[i + k]; )
		{
			k++;
		}
		str[j] = malloc((k + 1) * sizeof(char));
		if (!str[j])
		{
			for (k = 0; k < j; k++)
				free(str[k]);
			free(str);
			return (NULL);
		}
		for (n= 0; n < k; n++)
			str[j][n] = s[i++];
		str[j][n] = 0;
	}
	str[j] = NULL;
	return (str);
}

/**
 * **strtow2 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
