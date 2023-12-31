#include "shell.h"

/**
 * inputBuff - buffers chained commands
 * @inf: Structure that contains possible args
 * @buff: pointer to buffer
 * @length: pointer to of var length
 *
 * Return: length
 */
ssize_t inputBuff(info_t *inf, char **buff, size_t *length)
{
	ssize_t a = 0;
	size_t len = 0;

	if (!*length) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if _USE_GETLINE
		a = getline(buff, &len, stdin);
#else
		a = _getline_(inf, buff, &len);
#endif
		if (a > 0)
		{
			if ((*buff)[a - 1] == '\n')
			{
				(*buff)[a - 1] = '\0'; /* remove trailing newline */
				a--;
			}
			inf->lineCountFlag = 1;
			removeComment(*buff);
			buildHistoryList(inf, *buff, inf->histCount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*length = a;
				inf->cmdBuff = buff;
			}
		}
	}
	return (a);
}

/**
 * inputGetter - gets line subtracted from the newline
 * @inf: Structure that contains possible args
 *
 * Return: length or -1
 */
ssize_t inputGetter(info_t *inf)
{
	static char *buff;
	static size_t j, k, length;
	ssize_t a = 0;
	char **buffP = &(inf->arg), *ptr;

	_putchar(BUFF_FLUSH);
	a = inputBuff(inf, &buff, &length);
	if (a == -1)
		return (-1);
	if (length)
	{
		k = j;
		ptr = buff + j;

		check_chain(inf, buff, &k, j, length);
		while (k < length)
		{
			if (is_chain(inf, buff, &k))
				break;
			k++;
		}

		j = k + 1;
		if (j >= length)
		{
			j = length = 0;
			inf->cmdBuffType = _CMD_NORM;
		}

		*buffP = ptr;
		return (_strlen(ptr));
	}

	*buffP = buff;
	return (a);
}

/**
 * buffReader - reads buff
 * @inf: Structure that contains possible args
 * @buff: the buffer
 * @j:the  size
 *
 * Return: s
 */
ssize_t buffReader(info_t *inf, char *buff, size_t *j)
{
	ssize_t s = 0;

	if (*j)
		return (0);
	s = read(inf->read_fd, buff, READ_BUFF_S);
	if (s >= 0)
		*j = s;
	return (s);
}

/**
 * _getline_ - gets next line from STDIN
 * @inf: Structure that contains possible args
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline_(info_t *inf, char **ptr, size_t *length)
{
	static char buf[READ_BUFF_S];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *newP = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = buffReader(inf, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	newP = _realloc(p, s, s ? s + k : k + 1);
	if (!newP)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(newP, buf + i, k - i);
	else
		_strncpy(newP, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = newP;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - manages ctrl-C
 * @sigNum: signal
 *
 * Return: nothing
 */
void sigintHandler(__attribute__((unused))int sigNum)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFF_FLUSH);
}
