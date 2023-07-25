#include "shell.h"

/**
 * clearInfo - clears info_t struct
 * @inf: pointer of struct
 */
void clearInfo(info_t *inf)
{
	inf->arg = NULL;
	inf->argv = NULL;
	inf->path = NULL;
	inf->argc = 0;
}

/**
 * infoSetter - gives an initialization to info_t struct
 * @inf: pointer of struct
 * @av: argument vector
 */
void infoSetter(info_t *inf, char **av)
{
	int j = 0;

	inf->f_name = av[0];
	if (inf->arg)
	{
		inf->argv = _strtow(inf->arg, " \t");
		if (!inf->argv)
		{

			inf->argv = malloc(sizeof(char *) * 2);
			if (inf->argv)
			{
				inf->argv[0] = _strdup(inf->arg);
				inf->argv[1] = NULL;
			}
		}
		for (j = 0; inf->argv && inf->argv[j]; j++)
			;
		inf->argc = j;

		replace_alias(inf);
		replace_vars(inf);
	}
}

/**
 * freeInfo - frees the members of info_t struct
 * @inf: pointer of the struct
 * @all_f: returns true if struct members are freed
 */
void freeInfo(info_t *inf, int all_f)
{
	f_free(inf->argv);
	inf->argv = NULL;
	inf->path = NULL;
	if (all_f)
	{
		if (!inf->cmdBuff)
			free(inf->arg);
		if (inf->env)
			freeList(&(inf->env));
		if (inf->history)
			freeList(&(inf->history));
		if (inf->alias)
			freeList(&(inf->alias));
		f_free(inf->environ);
			inf->environ = NULL;
		b_free((void **)inf->cmdBuff);
		if (inf->read_fd > 2)
			close(inf->read_fd);
		_putchar(BUFF_FLUSH);
	}
}
