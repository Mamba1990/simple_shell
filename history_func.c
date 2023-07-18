#include "shell.h"
/**
 * get_history_file - get history file
 * @info: parameter struct
 * Return: string
 */
char *get_history_file(info_t *info)
{
	char *b, *d;

	d = _getenv(info, "HOME=");
	if (!d)
		return (NULL);
	b = malloc(sizeof(char) * (_strlen(d) + _strlen(HIST_FILE) + 2));
	if (!b)
		return (NULL);
	b[0] = 0;
	_strcpy(b, d);
	_strcat(b, "/");
	_strcat(b, HIST_FILE);
	return (b);
}

/**
 * write_history - create a file
 * @info: parameter struct
 * Return: 1 on success, -1 on failure
 */
int write_history(info_t *info)
{
	ssize_t f;
	char *fname = get_history_file(info);
	list_t *node = NULL;

	if (!fname)
		return (-1);

	f = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (f == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, f);
		_putfd('\n', f);
	}
	_putfd(BUF_FLUSH, f);
	close(f);
	return (1);
}

/**
 * read_history - read history file
 * @info: parameter struct
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int j, last = 0, linecount = 0;
	ssize_t f, rdlen, fsize = 0;
	struct stat st;
	char *b = NULL, *fname = get_history_file(info);

	if (!fname)
		return (0);

	f = open(fname, O_RDONLY);
	free(fname);
	if (f == -1)
		return (0);
	if (!fstat(f, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	b = malloc(sizeof(char) * (fsize + 1));
	if (!b)
		return (0);
	rdlen = read(f, b, fsize);
	b[fsize] = 0;
	if (rdlen <= 0)
		return (free(b), 0);
	close(f);
	for (j = 0; j < fsize; j++)
		if (b[j] == '\n')
		{
			b[j] = 0;
			build_history_list(info, b + last, linecount++);
			last = j + 1;
		}
	if (last != j)
		build_history_list(info, b + last, linecount++);
	free(b);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: parameter struct
 * @buf: character
 * @linecount: integer
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - renumber the history list
 * @info: parameter struct
 * Return: histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int j = 0;

	while (node)
	{
		node->num = j++;
		node = node->next;
	}
	return (info->histcount = j);
}
