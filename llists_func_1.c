#include "shell.h"


/**
 * add_node - adds a node to the start of the list
 * @h: pointer of pointer to head node
 * @s: string member of node
 * @number: index that history uses
 *
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
 * add_node_end - add node to end of list
 * @head: head node
 * @str: str field of node
 * @num: node index
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *n, *node;

	if (!head)
		return (NULL);

	node = *head;
	n = malloc(sizeof(list_t));
	if (!n)
		return (NULL);
	_memset((void *)n, 0, sizeof(list_t));
	n->num = num;
	if (str)
	{
		n->str = _strdup(str);
		if (!n->str)
		{
			free(n);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = n;
	}
	else
		*head = n;
	return (n);
}

/**
 * print_list_str - print str element of a linked list
 * @h: pointer to first node
 * Return: size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * delete_node_at_index - delete node at given index
 * @head: first node
 * @index: index of node
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_n;
	unsigned int j = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (j == index)
		{
			prev_n->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		j++;
		prev_n = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - free nodes of list
 * @head_ptr: head node
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_n, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_n = node->next;
		free(node->str);
		free(node);
		node = next_n;
	}
	*head_ptr = NULL;
}
