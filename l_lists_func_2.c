#include "shell.h"
/**
 * listLength - precise length of list
 * @head: 1st node
 * Return: list's size
 */
size_t listLength(const list_t *head)
{
	size_t j = 0;

	while (head)
	{
		head = head->next;
		j++;
	}
	return (j);
}

/**
 * listToStrings - gives array of strings
 * @h: 1st node
 * Return: strings' array
 */
char **listToStrings(list_t *h)
{
	list_t *_node = h;
	size_t j = listLength(h), c;
	char **ss;
	char *str;

	if (!h || !j)
		return (NULL);
	ss = malloc(sizeof(char *) * (j + 1));
	if (!ss)
		return (NULL);
	for (j = 0; _node; _node = _node->next, j++)
	{
		str = malloc(_strlen(_node->s) + 1);
		if (!str)
		{
			for (c = 0; c < j; c++)
				free(ss[c]);
			free(ss);
			return (NULL);
		}

		str = _strcpy(str, _node->s);
		ss[j] = str;
	}
	ss[j] = NULL;
	return (ss);
}
/**
 * printList - displays elements of a list
 * @head: 1st node
 * Return: list's size
 */
size_t printList(const list_t *head)
{
	size_t j = 0;

	while (head)
	{
		_puts(numberConverter(head->number, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->s ? head->s : "(nil)");
		_puts("\n");
		head = head->next;
		j++;
	}
	return (j);
}

/**
 * nodeStartsWith - determines node starting with prefix
 * @_node: list head
 * @pfix: string
 * @cc: character after prefix
 * Return: node or null
 */
list_t *nodeStartsWith(list_t *_node, char *pfix, char cc)
{
	char *a = NULL;

	while (_node)
	{
		a = starts_with(_node->s, pfix);
		if (a && ((cc == -1) || (*a == cc)))
			return (_node);
		_node = _node->next;
	}
	return (NULL);
}

/**
 * indexNodeGetter - get node's index
 * @h: address of the list head
 * @_node: node
 * Return: node's index or -1
 */
ssize_t indexNodeGetter(list_t *h, list_t *_node)
{
	size_t j = 0;

	while (h)
	{
		if (h == _node)
			return (j);
		h = h->next;
		j++;
	}
	return (-1);
}

