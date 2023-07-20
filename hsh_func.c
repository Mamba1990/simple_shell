#include "shell.h"

/**
 * hsh - main shell loop
 * @inf: Structure that contains possible args
 * @av: argument vector 
 *
 * Return: 0 success, 1 failure
 */
int hsh(info_t *inf, char **av)
{
	ssize_t s = 0;
	int builtinR = 0;

	while (s != -1 && builtinR != -2)
	{
		clear_info(inf);
		if (interactive(inf))
			_puts("$ ");
		_eputchar(BUFF_FLUSH);
		s = get_input(inf);
		if (s != -1)
		{
			set_info(inf, av);
			builtinR = find_builtin(inf);
			if (builtinR == -1)
				find_cmd(inf);
		}
		else if (interactive(inf))
			_putchar('\n');
		free_info(inf, 0);
	}
	write_history(inf);
	free_info(inf, 1);
	if (!interactive(inf) && inf->status)
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
 * find_builtin - finds the builtin cmd
 * @inf: Structure that contains possible args
 *
 * Return: -1 if not found,
 *	    0 success
 *	    1 if builtin found, no success,
 *	    -2 if signals exiting
 */
int find_builtin(info_t *inf)
{
	int j, builtInR = -1;
	builtinTable builtin_tbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
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
 * find_cmd - finds the path cmd
 * @inf: Structure that contains possible args
 *
 * Return: nothing
 */
void find_cmd(info_t *inf)
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
		if (!is_delim(inf->arg[j], " \t\n"))
			l++;
	if (!l)
		return;

	_path = find_path(inf, _getenv(inf, "PATH="), inf->argv[0]);
	if (_path)
	{
		inf->path = _path;
		fork_cmd(inf);
	}
	else
	{
		if ((interactive(inf) || _getenv(inf, "PATH=")
			|| inf->argv[0][0] == '/') && is_cmd(inf, inf->argv[0]))
			fork_cmd(inf);
		else if (*(inf->arg) != '\n')
		{
			inf->status = 127;
			print_error(inf, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks  exec thread that runs command
 * @inf: Structure that contains possible args
 *
 * Return: nothing
 */
void fork_cmd(info_t *inf)
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
		if (execve(inf->path, inf->argv, get_environ(inf)) == -1)
		{
			free_info(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(inf->status));
		if (WIFEXITED(inf->status))
		{
			inf->status = WEXITSTATUS(inf->status);
			if (inf->status == 126)
				print_error(inf, "Permission denied\n");
		}
	}
}
