#include "shell.h"

/**
 * _myhistory - prints th list's history
 * @inf: Structure that contains possible args
 *  Return: 0
 */
int _myhistory(info_t *inf)
{
	print_list(inf->history);
	return (0);
}

/**
 * unset_alias - unsets alias to a str
 * @inf: Structure that contains possible args
 * @_str: string input
 *
 * Return:  0 success, 1 faillure
 */
int unset_alias(info_t *inf, char *_str)
{
	char *ptr, ch;
	int r;

	ptr = _strchr(_str, '=');
	if (!ptr)
		return (1);
	ch = *ptr;
	*ptr = 0;
	r = delete_node_at_index(&(inf->alias),
		get_node_index(inf->alias, node_starts_with(inf->alias, _str, -1)));
	*ptr = ch;
	return (r);
}

/**
 * set_alias - gives alias to string
 * @inf: Structure that contains possible args
 * @_str: string input
 *
 * Return: 0 success, 1 faillure
 */
int set_alias(info_t *inf, char *_str)
{
	char *ptr;

	ptr = _strchr(_str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(inf, _str));

	unset_alias(inf, _str);
	return (add_node_end(&(inf->alias), _str, 0) == NULL);
}

/**
 * print_alias - displays string's alias
 * @_node: node's alias
 *
 * Return: 0 on success, 1 failure
 */
int print_alias(list_t *_node)
{
	char *ptr = NULL, *als = NULL;

	if (_node)
	{
		ptr = _strchr(_node->s, '=');
		for (als = node->s; als <= ptr; als++)
			_putchar(*als);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - man alias
 * @inf: Structure that contains possible args
 *  Return: 0
 */
int _myalias(info_t *inf)
{
	int j = 0;
	char *ptr = NULL;
	list_t *_node = NULL;

	if (inf->argc == 1)
	{
		_node = inf->alias;
		while (_node)
		{
			print_alias(_node);
			_node = _node->next;
		}
		return (0);
	}
	for (j = 1; inf->argv[j]; j++)
	{
		ptr = _strchr(inf->argv[j], '=');
		if (ptr)
			set_alias(inf, inf->argv[j]);
		else
			print_alias(node_starts_with(inf->alias, inf->argv[j], '='));
	}

	return (0);
}
