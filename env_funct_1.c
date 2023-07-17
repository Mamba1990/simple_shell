#include "shell.h"

/**
 * _myenv - displays the actual environment
 * @inf: Structure that contains possible args
 * Return: 0
 */
int _myenv(info_t *inf)
{
	print_list_str(inf->env);
	return (0);
}

/**
 * _getenv - gets the environ variable's value
 * @inf: Structure that contains possible args
 * @name: the name of environ variable
 *
 * Return: env's value
 */
char *_getenv(info_t *inf, const char *name)
{
	list_t *_node = inf->env;
	char *ptr;

	while (_node)
	{
		ptr = starts_with(_node->s, name);
		if (ptr && *ptr)
			return (ptr);
		_node = _node->next;
	}
	return (NULL);
}

/**
 * _mysetenv sets a new environment variable,
 *             or adjusts the existing one
 * @inf: Structure that contains possible args
 *  Return: 0
 */
int _mysetenv(info_t *inf)
{
	if (inf->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(inf, inf->argv[1], inf->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - deletes an environment variable
 * @inf: Structure that contains possible args
 *  Return: 0
 */
int _myunsetenv(info_t *inf)
{
	int j;

	if (inf->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= inf->argc; j++)
		_unsetenv(inf, inf->argv[j]);

	return (0);
}

/**
 * populate_env_list - settles environ of thr linked list
 * @inf: Structure that contains possible args.
 * Return: 0
 */
int populate_env_list(info_t *inf)
{
	list_t *_node = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		add_node_end(&_node, environ[j], 0);
	inf->env = _node;
	return (0);
}
