#include "shell.h"

/**
 * myHistory - prints th list's history
 * @inf: Structure that contains possible args
 *  Return: 0
 */
int myHistory(info_t *inf)
{
	printList(inf->history);
	return (0);
}

/**
 * unsetAlias - unsets alias to a str
 * @inf: Structure that contains possible args
 * @_str: string input
 *
 * Return:  0 success, 1 faillure
 */
int unsetAlias(info_t *inf, char *_str)
{
	char *ptr, ch;
	int r;

	ptr = _strchr(_str, '=');
	if (!ptr)
		return (1);
	ch = *ptr;
	*ptr = 0;
	r = nodeDeleterAtIndex(&(inf->alias),
		indexNodeGetter(inf->alias, nodeStartsWith(inf->alias, _str, -1)));
	*ptr = ch;
	return (r);
}

/**
 * aliasSetter - gives alias to string
 * @inf: Structure that contains possible args
 * @_str: string input
 *
 * Return: 0 success, 1 faillure
 */
int aliasSetter(info_t *inf, char *_str)
{
	char *ptr;

	ptr = _strchr(_str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unsetAlias(inf, _str));

	unsetAlias(inf, _str);
	return (addNodeEnd(&(inf->alias), _str, 0) == NULL);
}

/**
 * aliasPrinter - displays string's alias
 * @_node: node's alias
 *
 * Return: 0 on success, 1 failure
 */
int aliasPrinter(list_t *_node)
{
	char *ptr = NULL, *als = NULL;

	if (_node)
	{
		ptr = _strchr(_node->s, '=');
		for (als = _node->s; als <= ptr; als++)
			_putchar(*als);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * myAlias - man alias
 * @inf: Structure that contains possible args
 *  Return: 0
 */
int myAlias(info_t *inf)
{
	int j = 0;
	char *ptr = NULL;
	list_t *_node = NULL;

	if (inf->argc == 1)
	{
		_node = inf->alias;
		while (_node)
		{
			aliasPrinter(_node);
			_node = _node->next;
		}
		return (0);
	}
	for (j = 1; inf->argv[j]; j++)
	{
		ptr = _strchr(inf->argv[j], '=');
		if (ptr)
			aliasSetter(inf, inf->argv[j]);
		else
			aliasPrinter(nodeStartsWith(inf->alias, inf->argv[j], '='));
	}

	return (0);
}
