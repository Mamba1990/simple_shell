#include "shell.h"

/**
 * _myexit - exits the shell
 * @inf:  Structure that contains possible args
 *  Return: integer
 */
int _myexit(info_t *inf)
{
	int exitCheck;

	if (inf->argv[1])
	{
		exitCheck = _erratoi(inf->argv[1]);
		if (exitCheck == -1)
		{
			inf->status = 2;
			print_error(inf, "Illegal number: ");
			_eputs(inf->argv[1]);
			_eputchar('\n');
			return (1);
		}
		inf->errNum = _erratoi(inf->argv[1]);
		return (-2);
	}
	inf->errNum = -1;
	return (-2);
}

/**
 * _mycd - changes the working directory
 * @inf: Structure that contains possible args
 *  Return: 0
 */
int _mycd(info_t *inf)
{
	char *str, *_dir, buff[1024];
	int chdirRet;

	str = getcwd(buff, 1024);
	if (!str)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!inf->argv[1])
	{
		_dir = getEnv(inf, "HOME=");
		if (!_dir)
			chdirRet =
				chdir((_dir = getEnv(inf, "PWD=")) ? _dir : "/");
		else
			chdirRet = chdir(_dir);
	}
	else if (_strcmp(inf->argv[1], "-") == 0)
	{
		if (!getEnv(inf, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(getEnv(inf, "OLDPWD=")), _putchar('\n');
		chdirRet = /* what should this be? */
			chdir((_dir = getEnv(inf, "OLDPWD=")) ? _dir : "/");
	}
	else
		chdirRet = chdir(inf->argv[1]);
	if (chdirRet == -1)
	{
		print_error(inf, "can't cd to ");
		_eputs(inf->argv[1]), _eputchar('\n');
	}
	else
	{
		setEnv(inf, "OLDPWD", getEnv(inf, "PWD="));
		setEnv(inf, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * _myhelp - helps changing the working dir
 * @inf: Structure that contains possible args
 *  Return: 0
 */
int _myhelp(info_t *inf)
{
	char **argArray;

	argArray = inf->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argArray);
	return (0);
}
