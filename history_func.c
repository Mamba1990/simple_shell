#include "shell.h"
/**
 * get_history_file - returns file's
 * @inf: Structure that contains possible args
 * Return: string that contains the file history
 */
char *get_history_file(info_t *inf)
{
	char *b, *d;

	d = _getenv(inf, "HOME=");
	if (!d)
		return (NULL);
	b = malloc(sizeof(char) * (_strlen(d) + _strlen(_HIST_FILE) + 2));
	if (!b)
		return (NULL);
	b[0] = 0;
	_strcpy(b, d);
	_strcat(b, "/");
	_strcat(b, _HIST_FILE);
	return (b);
}

/**
 * write_history - create a file or adjusts the one that exixts
 * @inf: Structure that contains possible args
 * Return: 1 success, -1  failure
 */
int write_history(info_t *inf)
{
	ssize_t f;
	char *fname = get_history_file(inf);
	list_t *_node = NULL;

	if (!fname)
		return (-1);

	f = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (f == -1)
		return (-1);
	for (_node = inf->history; _node; _node = _node->next)
	{
		_putsfd(_node->s, f);
		_putfd('\n', f);
	}
	_putfd(BUFF_FLUSH, f);
	close(f);
	return (1);
}

/**
 * read_history - read the file  history 
 * @inf: Structure that contains possible args
 * Return: hisCount success, 0 failure
 */
int read_history(info_t *inf)
{
	int j, _last = 0, lineCount = 0;
	ssize_t f, _rdlen, _fsize = 0;
	struct stat _st;
	char *b = NULL, *fname = get_history_file(inf);

	if (!fname)
		return (0);

	f = open(fname, O_RDONLY);
	free(fname);
	if (f == -1)
		return (0);
	if (!fstat(f, &_st))
		_fsize = _st.st_size;
	if (_fsize < 2)
		return (0);
	b = malloc(sizeof(char) * (_fsize + 1));
	if (!b)
		return (0);
	_rdlen = read(f, b, _fsize);
	b[_fsize] = 0;
	if (_rdlen <= 0)
		return (free(b), 0);
	close(f);
	for (j = 0; j < _fsize; j++)
		if (b[j] == '\n')
		{
			b[j] = 0;
			build_history_list(inf, b + _last, lineCount++);
			_last = j + 1;
		}
	if (_last != j)
		build_history_list(inf, b + _last, lineCount++);
	free(b);
	inf->histCount = lineCount;
	while (inf->histCount-- >= _HIST_MAX)
		delete_node_at_index(&(inf->history), 0);
	renumber_history(inf);
	return (inf->histCount);
}

/**
 * build_history_list - adds history's entry linked list
 * @inf: Structure that contains possible args
 * @buff: mem block
 * @lineCount: integer
 * Return: 0
 */
int build_history_list(info_t *inf, char *buff, int lineCount)
{
	list_t *_node = NULL;

	if (inf->history)
		_node = inf->history;
	add_node_end(&_node, buff, lineCount);

	if (!inf->history)
		inf->history = _node;
	return (0);
}

/**
 * renumber_history - gives a number to the history list
 * @inf: Structure that contains possible args
 * Return: integer
 */
int renumber_history(info_t *inf)
{
	list_t *_node = inf->history;
	int j = 0;

	while (_node)
	{
		_node->number = j++;
		_node = _node->next;
	}
	return (inf->histCount = j);
}
