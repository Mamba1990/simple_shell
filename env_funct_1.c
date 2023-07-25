#include "shell.h"

/**
 * myEnv - displays the actual environment
 * @inf: Structure that contains possible args
 * Return: 0
 */
int myEnv(info_t *inf)
{
	listStrPrinter(inf->env);
	return (0);
}

/**
 * getEnv - gets the environ variable's value
 * @inf: Structure that contains possible args
 * @name: the name of environ variable
 *
 * Return: env's value
 */
char *getEnv(info_t *inf, const char *name)
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
 * mySetEnv - sets a new environment variable,
 *             or adjusts the existing one
 * @inf: Structure that contains possible args
 *  Return: 0
 */
int mySetEnv(info_t *inf)
{
	if (inf->argc != 3)
	{
		_eputs_("Incorrect number of arguements\n");
		return (1);
	}
	if (setEnv(inf, inf->argv[1], inf->argv[2]))
		return (0);
	return (1);
}

/**
 * myUnsetEnv - deletes an environment variable
 * @inf: Structure that contains possible args
 *  Return: 0
 */
int myUnsetEnv(info_t *inf)
{
	int j;

	if (inf->argc == 1)
	{
		_eputs_("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= inf->argc; j++)
		unsetEnv(inf, inf->argv[j]);

	return (0);
}

/**
 * envListPopulator - settles environ of thr linked list
 * @inf: Structure that contains possible args.
 * Return: 0
 */
int envListPopulator(info_t *inf)
{
	list_t *_node = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		addNodeEnd(&_node, environ[j], 0);
	inf->env = _node;
	return (0);
}
