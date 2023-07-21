#include "shell.h"

/**
 * interactive - returns true if the interactive mode is active
 * @inf: struct address
 *
 * Return: 1 success, 0 failure
 */
int interactive(info_t *inf)
{
	return (isatty(STDIN_FILENO) && inf->read_fd <= 2);
}

/**
 * is_delim - checks if a char is a delim
 * @cc: char to be checked
 * @dl: the delimeter string
 * Return: 1 success, 0 faillure
 */
int is_delim(char cc, char *dl)
{
	while (*dl)
		if (*dl++ == cc)
			return (1);
	return (0);
}


/**
* _isalpha - Checks for alphabetic character
*@c: The character is in ASCII code
*
*Description: 'the program's description'
*Return: 0
*/
int _isalpha(int c)
{
	if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 *_atoi - converts a string to an integer
 *@str: the string to be converted
 *Return: 0 if function is num free, converted number if not
 */

int _atoi(char *str)
{
	int j, n = 1, flg = 0, oput;
	unsigned int res = 0;

	j = 0;
	while (str[j] != '\0' && flg != 2)
	{
		if (str[j] == '-')
			n *= -1;

		if (str[j] >= '0' && str[j] <= '9')
		{
			flg = 1;
			res *= 10;
			res += (str[j] - '0');
		}
		else if (flg == 1)
			flg = 2;
		j++;
	}

	if (n == -1)
		oput = -res;
	else
		oput = res;

	return (oput);
}

