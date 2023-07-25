#include "shell.h"

/**
 * myExit - exits the shell
 * @inf:  Structure that contains possible args
 *  Return: integer
 */
int myExit(info_t *inf)
{
	int exitCheck;

	if (inf->argv[1])
	{
		exitCheck = _erratoi_(inf->argv[1]);
		if (exitCheck == -1)
		{
			inf->status = 2;
			errorPrinter(inf, "Illegal number: ");
			_eputs_(inf->argv[1]);
			_eputchar_('\n');
			return (1);
		}
		inf->errNum = _erratoi_(inf->argv[1]);
		return (-2);
	}
	inf->errNum = -1;
	return (-2);
}

/**
 * myCd - changes the working directory
 * @inf: Structure that contains possible args
 *  Return: 0
 */
int myCd(info_t *inf)
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
		chdirRet =
			chdir((_dir = getEnv(inf, "OLDPWD=")) ? _dir : "/");
	}
	else
		chdirRet = chdir(inf->argv[1]);
	if (chdirRet == -1)
	{
		errorPrinter(inf, "can't cd to ");
		_eputs_(inf->argv[1]), _eputchar_('\n');
	}
	else
	{
		setEnv(inf, "OLDPWD", getEnv(inf, "PWD="));
		setEnv(inf, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * myHelper - helps changing the working dir
 * @inf: Structure that contains possible args
 *  Return: 0
 */
int myHelper(info_t *inf)
{
	char **argArray;

	argArray = inf->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argArray);
	return (0);
}
