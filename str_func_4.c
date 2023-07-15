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
		for (k = 0; !is_delim(s[i + k], dl) && s[i + k]; )
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
 * **strtow2 - toktenizes a string into words.

 * @s: the input string
 * @dl: the delimeter of a string
 * Return: address of an array of strings, or NULL 
 */
char **strtow2(char *s, char dl)
{
	int i, j, k, n, num_words = 0;
	char **str;

	if (s == NULL || s[0] == 0)
		return (NULL);
	for (i = 0; s[i] != '\0'; i++)
		if ((s[i] != dl && s[i + 1] == dl) ||
		    (s[i] != dl && !s[i + 1]) || s[i + 1] == dl)
			num_words++;
	if (num_words == 0)
		return (NULL);
	str = malloc((1 + num_words) * sizeof(char *));
	if (!str)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (s[i] == dl && s[i] != dl)
			i++;
		k = 0;
		while (s[i + k] != dl && s[i + k] && s[i + k] != dl)
			k++;
		str[j] = malloc((k + 1) * sizeof(char));
		if (!str[j])
		{
			for (k = 0; k < j; k++)
				free(str[k]);
			free(str);
			return (NULL);
		}
		for (n = 0; n < k; n++)
			str[j][n] = s[i++];
		str[j][n] = 0;
	}
	str[j] = NULL;
	return (str);
}
