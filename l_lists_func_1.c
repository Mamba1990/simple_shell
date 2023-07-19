#include "shell.h"


/**
 * add_node - adds a node to the start of the list
 * @h: pointer of pointer to head node
 * @s: string member of node
 * @number: index that history uses
 * Return: list's size
 */
list_t *add_node(list_t **h, const char *s, int number)
{
	list_t *head;

	if (!h)
		return (NULL);
	head = malloc(sizeof(list_t));
	if (!head)
		return (NULL);
	_memset((void *)head, 0, sizeof(list_t));
	head->number= number;
	if (s)
	{
		head->s = _strdup(s);
		if (!head->s)
		{
			free(head);
			return (NULL);
		}
	}
	head->next = *h;
	*h = head;
	return (head);
}

/**
 * add_node_end - adds a node to the end of the list
 * @h: pointer of pointer to head node
 * @s: string member of node
 * @number: index that history uses
 * Return: list's size
 */
list_t *add_node_end(list_t **h, const char *s, int number)
{
	list_t *n, *_node;

	if (!h)
		return (NULL);

	_node = *h;
	n = malloc(sizeof(list_t));
	if (!n)
		return (NULL);
	_memset((void *)n, 0, sizeof(list_t));
	n->number = number;
	if (s)
	{
		n->s = _strdup(s);
		if (!n->s)
		{
			free(n);
			return (NULL);
		}
	}
	if (_node)
	{
		while (_node->next)
			_node = _node->next;
		node->next = n;
	}
	else
		*h = n;
	return (n);
}

/**
 * print_list_str - displays the string of a linked list
 * @head: pointing  first node
 * Return:  list's size
 */
size_t print_list_str(const list_t *head)
{
	size_t j = 0;

	while (head)
	{
		_puts(head->s ? head->s : "(nil)");
		_puts("\n");
		head = head->next;
		j++;
	}
	return (j);
}

/**
 * delete_node_at_index - erases node at a specific index
 * @h: 1st node
 * @idx: node's index
 * Return: 1 success, 0 failure
 */
int delete_node_at_index(list_t **h, unsigned int idx)
{
	list_t *_node, *prev_n;
	unsigned int j = 0;

	if (!h || !*h)
		return (0);

	if (!idx)
	{
		_node = *h;
		*h = (*h)->next;
		free(_node->s);
		free(_node);
		return (1);
	}
	_node = *h;
	while (_node)
	{
		if (j == idx)
		{
			prev_n->next = _node->next;
			free(_node->s);
			free(_node);
			return (1);
		}
		j++;
		prev_n = _node;
		_node = _node->next;
	}
	return (0);
}

/**
 * free_list - free nodes 
 * @head_p: pointer of pointer to head node
 * Return: nothing
 */
void free_list(list_t **head_p)
{
	list_t *_node, *next_n, *h;

	if (!head_p || !*head_p)
		return;
	h = *head_p;
	_node = h;
	while (_node)
	{
		next_n = _node->next;
		free(_node->s);
		free(_node);
		_node = next_n;
	}
	*head_p = NULL;
}
