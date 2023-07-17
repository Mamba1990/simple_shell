#include "shell.h"

/**
 * clear_info - clears  info_t struct 
 * @inf: pointer of struct
 */
void clear_info(info_t *inf)
{
	inf->arg = NULL;
	inf->argv = NULL;
	inf->path = NULL;
	inf->argc = 0;
}

/**
 * set_info - gives an initialization to info_t struct
 * @inf: pointer of struct
 * @av: argument vector
 */
void set_info(info_t *inf, char **av)
{
	int j = 0;

	inf->f_name = av[0];
	if (inf->arg)
	{
		inf->argv = strtow(inf->arg, " \t");
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
 * free_info - frees the members of info_t struct
 * @inf: pointer of the  struct 
 * @all_f: returns true if struct members are freed
 */
void free_info(info_t *inf, int all_f)
{
	ffree(inf->argv);
	inf->argv = NULL;
	inf->path = NULL;
	if (all_f)
	{
		if (!inf->cmdBuff)
			free(inf->arg);
		if (inf->env)
			free_list(&(inf->env));
		if (inf->history)
			free_list(&(inf->history));
		if (inf->alias)
			free_list(&(inf->alias));
		ffree(inf->environ);
			inf->environ = NULL;
		bfree((void **)inf->cmdBuff);
		if (inf->read_fd > 2)
			close(inf->read_fd);
		_putchar(BUFF_FLUSH);
	}
}
