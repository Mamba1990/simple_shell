#include "shell.h"

/**
 * _hsh_ - main shell loop
 * @inf: Structure that contains possible args
 * @av: argument vector
 *
 * Return: 0 success, 1 failure
 */
int _hsh_(info_t *inf, char **av)
{
	ssize_t s = 0;
	int builtinR = 0;

	while (s != -1 && builtinR != -2)
	{
		clearInfo(inf);
		if (_interactive(inf))
			_puts("$ ");
		_eputchar_(BUFF_FLUSH);
		s = inputGetter(inf);
		if (s != -1)
		{
			infoSetter(inf, av);
			builtinR = builtinfinder(inf);
			if (builtinR == -1)
				cmdFinder(inf);
		}
		else if (_interactive(inf))
			_putchar('\n');
		freeInfo(inf, 0);
	}
	historyWriter(inf);
	freeInfo(inf, 1);
	if (!_interactive(inf) && inf->status)
		exit(inf->status);
	if (builtinR == -2)
	{
		if (inf->errNum == -1)
			exit(inf->status);
		exit(inf->errNum);
	}
	return (builtinR);
}

/**
 * builtinfinder - finds the builtin cmd
 * @inf: Structure that contains possible args
 *
 * Return: -1 if not found,
 *	    0 success
 *	    1 if builtin found, no success,
 *	    -2 if signals exiting
 */
int builtinfinder(info_t *inf)
{
	int j, builtInR = -1;
	builtinTable builtin_tbl[] = {
		{"exit", myExit},
		{"env", myEnv},
		{"help", myHelper},
		{"history", myHistory},
		{"setenv", mySetEnv},
		{"unsetenv", myUnsetEnv},
		{"cd", myCd},
		{"alias", myAlias},
		{NULL, NULL}
	};

	for (j = 0; builtin_tbl[j].type; j++)
		if (_strcmp(inf->argv[0], builtin_tbl[j].type) == 0)
		{
			inf->lineCount++;
			builtInR = builtin_tbl[j].func(inf);
			break;
		}
	return (builtInR);
}

/**
 * cmdFinder - finds the path cmd
 * @inf: Structure that contains possible args
 *
 * Return: nothing
 */
void cmdFinder(info_t *inf)
{
	char *_path = NULL;
	int j, l;

	inf->path = inf->argv[0];
	if (inf->lineCountFlag == 1)
	{
		inf->lineCount++;
		inf->lineCountFlag = 0;
	}
	for (j = 0, l = 0; inf->arg[j]; j++)
		if (!isDelim(inf->arg[j], " \t\n"))
			l++;
	if (!l)
		return;

	_path = pathFinder(inf, getEnv(inf, "PATH="), inf->argv[0]);
	if (_path)
	{
		inf->path = _path;
		forkComd(inf);
	}
	else
	{
		if ((_interactive(inf) || getEnv(inf, "PATH=")
			|| inf->argv[0][0] == '/') && isCommd(inf, inf->argv[0]))
			forkComd(inf);
		else if (*(inf->arg) != '\n')
		{
			inf->status = 127;
			errorPrinter(inf, "not found\n");
		}
	}
}

/**
 * forkComd - forks  exec thread that runs command
 * @inf: Structure that contains possible args
 *
 * Return: nothing
 */
void forkComd(info_t *inf)
{
	pid_t childPid;

	childPid = fork();
	if (childPid == -1)
	{
		perror("Error:");
		return;
	}
	if (childPid == 0)
	{
		if (execve(inf->path, inf->argv, getEnviron(inf)) == -1)
		{
			freeInfo(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(inf->status));
		if (WIFEXITED(inf->status))
		{
			inf->status = WEXITSTATUS(inf->status);
			if (inf->status == 126)
				errorPrinter(inf, "Permission denied\n");
		}
	}
}
