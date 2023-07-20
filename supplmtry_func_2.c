#include "shell.h"

/**
 * _erratoi - convertion of a string to an integer
 * @str: tring to convert
 * Return: 0  numbers found, converted number if not
 * -1 error
 */
int _erratoi(char *str)
{
	int j = 0;
	unsigned long int res = 0;

	if (*str == '+')
		str++;  
	j = 0;
	while (str[j] != '\0')
	{
		if (str[j] >= '0' && str[j] <= '9')
		{
			res *= 10;
			res += (str[j] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
		j++;
	}
	return (res);
}

/**
 * print_error - displays an error message
 * @inf: info struct
 * @errs: string that contains the error type
 * Return: 0 no numbers faound in string, converted number if not
 * -1 error
 */
void print_error(info_t *inf, char *errs)
{
	_eputs(inf->f_name);
	_eputs(": ");
	print_d(inf->lineCount, STDERR_FILENO);
	_eputs(": ");
	_eputs(inf->argv[0]);
	_eputs(": ");
	_eputs(errs);
}

/**
 * print_d - displays a decimal 
 * @iput:  parameter
 * @fid: filedescripto
 *
 * Return: chars printed
 */
int print_d(int iput, int fid)
{
	int (*__putchar)(char) = _putchar;
	int j, cnt = 0;
	unsigned int abso, crrt;

	if (fid == STDERR_FILENO)
		__putchar = _eputchar;
	if (iput < 0)
	{
		abso = -iput;
		__putchar('-');
		cnt++;
	}
	else
		abso = iput;
	crrt = abso;
	j = 1000000000;
	for ( ; j > 1; j /= 10)
	{
		if (abso / j)
		{
			__putchar('0' + crrt / j);
			cnt++;
		}
		crrt %= j;
	}
	__putchar('0' + crrt);
	cnt++;

	return (cnt);
}

/**
 * convert_number - converts a number
 * @number: input
 * @b: input
 * @flgs: input
 *
 * Return: pointer to a strinf
 */
char *convert_number(long int number, int b, int flgs)
{
	static char *arr;
	static char buff[50];
	char n = 0;
	char *p;
	unsigned long m = number;

	if (!(flgs & _CONVERT_UNSIGNED) && number < 0)
	{
	
		m = -number;
		n = '-';

	}
	arr = flgs & _CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buff[49];
	*p = '\0';

	do	{
		*--p = arr[m % b];
		m /= b;
	} while (m != 0);

	if (n)
		*--p = n;
	return (p);
}

/**
 * remove_comments - deletes comments
 * @buff: pouinter the string to be modified
 *
 * Return: 0
 */
void remove_comments(char *buff)
{
	int j;
	j = 0;
	for ( ; buff[j] != '\0'; j++)
		if (buff[j] == '#' && (!j || buff[j - 1] == ' '))
		{
			buff[j] = '\0';
			break;
		}
}
