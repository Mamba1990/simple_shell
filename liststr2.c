#include "shell.h"
/**
 * list_len - precise length of list
 * @h: first node
 * Return: list's size
 */
size_t list_len(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * list_to_strings - gives array of strings
 * @head: first node
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t j = list_len(head), c;
	char **s;
	char *str;

	if (!head || !j)
		return (NULL);
	s = malloc(sizeof(char *) * (j + 1));
	if (!s)
		return (NULL);
	for (j = 0; node; node = node->next, j++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (c = 0; c < j; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		s[j] = str;
	}
	s[j] = NULL;
	return (s);
}
/**
 * print_list - print elements of a list
 * @h: first node
 * Return: list's size
 */
size_t print_list(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * node_starts_with - determines node that starts with prefix
 * @node: list head
 * @prefix: string
 * @c: character after prefix
 * Return: node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *a = NULL;

	while (node)
	{
		a = starts_with(node->str, prefix);
		if (a && ((c == -1) || (*a == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - get node's index
 * @head: list head
 * @node: node
 * Return: node's index or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t j = 0;

	while (head)
	{
		if (head == node)
			return (j);
		head = head->next;
		j++;
	}
	return (-1);
}

