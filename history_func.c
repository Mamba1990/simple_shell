#include "shell.h"
/**
 * fileHistoryGetter - returns file's
 * @inf: Structure that contains possible args
 * Return: string that contains the file history
 */
char *fileHistoryGetter(info_t *inf)
{
	char *b, *d;

	d = getEnv(inf, "HOME=");
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
 * historyWriter - create a file or adjusts the one that exixts
 * @inf: Structure that contains possible args
 * Return: 1 success, -1  failure
 */
int historyWriter(info_t *inf)
{
	ssize_t f;
	char *fname = fileHistoryGetter(inf);
	list_t *_node = NULL;

	if (!fname)
		return (-1);

	f = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (f == -1)
		return (-1);
	for (_node = inf->history; _node; _node = _node->next)
	{
		_putsfd_(_node->s, f);
		_putfd_('\n', f);
	}
	_putfd_(BUFF_FLUSH, f);
	close(f);
	return (1);
}

/**
 * historyReader - read the file history
 * @inf: Structure that contains possible args
 * Return: hisCount success, 0 failure
 */
int historyReader(info_t *inf)
{
	int j, _last = 0, lineCount = 0;
	ssize_t f, _rdlen, _fsize = 0;
	struct stat _st;
	char *b = NULL, *fname = fileHistoryGetter(inf);

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
			buildHistoryList(inf, b + _last, lineCount++);
			_last = j + 1;
		}
	if (_last != j)
		buildHistoryList(inf, b + _last, lineCount++);
	free(b);
	inf->histCount = lineCount;
	while (inf->histCount-- >= _HIST_MAX)
		nodeDeleterAtIndex(&(inf->history), 0);
	renumberHistory(inf);
	return (inf->histCount);
}

/**
 * buildHistoryList - adds history's entry linked list
 * @inf: Structure that contains possible args
 * @buff: mem block
 * @lineCount: integer
 * Return: 0
 */
int buildHistoryList(info_t *inf, char *buff, int lineCount)
{
	list_t *_node = NULL;

	if (inf->history)
		_node = inf->history;
	addNodeEnd(&_node, buff, lineCount);

	if (!inf->history)
		inf->history = _node;
	return (0);
}

/**
 * renumberHistory - gives a number to the history list
 * @inf: Structure that contains possible args
 * Return: integer
 */
int renumberHistory(info_t *inf)
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
