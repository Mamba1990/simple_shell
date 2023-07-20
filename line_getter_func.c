#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @inf: Structure that contains possible args
 * @buff: pointer to buffer
 * @length: pointer to of var length
 *
 * Return: length
 */
ssize_t input_buf(info_t *inf, char **buff, size_t *length)
{
	ssize_t a = 0;
	size_t len = 0;

	if (!*length) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		a = getline(buff, &len, stdin);
#else
		a = _getline(inf, buff, &len);
#endif
		if (a > 0)
		{
			if ((*buff)[a - 1] == '\n')
			{
				(*buff)[a - 1] = '\0'; /* remove trailing newline */
				a--;
			}
			inf->lineCountFlag = 1;
			remove_comments(*buff);
			build_history_list(inf, *buff, inf->histCount++);
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
 * get_input - gets line subtracted from the newline
 * @inf: Structure that contains possible args
 *
 * Return: length or -1
 */
ssize_t get_input(info_t *inf)
{
	static char *buff; /* the ';' command chain buffer */
	static size_t j, k, length;
	ssize_t a = 0;
	char **buffP = &(inf->arg), *ptr;

	_putchar(BUFF_FLUSH);
	a = input_buf(inf, &buff, &length);
	if (a == -1) /* EOF */
		return (-1);
	if (length)	/* we have commands left in the chain buffer */
	{
		k = j; /* init new iterator to current buf position */
		ptr = buff + j; /* get pointer for return */

		check_chain(inf, buff, &k, j, length);
		while (k < length) /* iterate to semicolon or end */
		{
			if (is_chain(inf, buff, &k))
				break;
			k++;
		}

		j = k + 1; /* increment past nulled ';'' */
		if (j >= length) /* reached end of buffer? */
		{
			j = length = 0; /* reset position and length */
			inf->cmdBuffType = _CMD_NORM;
		}

		*buffP = ptr; /* pass back pointer to current command position */
		return (_strlen(ptr)); /* return length of current command */
	}

	*buffP = buff; /* else not a chain, pass back buffer from _getline() */
	return (a); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads buff
 * @inf: Structure that contains possible args
 * @buff: the buffer
 * @j:the  size
 *
 * Return: s
 */
ssize_t read_buf(info_t *inf, char *buff, size_t *j)
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
 * _getline - gets next line from STDIN
 * @inf: Structure that contains possible args
 * @p: address of pointer to buffer, preallocated or NULL
 * @leng: size of preallocated ptr buffer if not NULL
 *
 * Return: r
 */
int _getline(info_t *inf, char **p, size_t *leng)
{
	static char buff[READ_BUFF_S];
	static size_t j, length;
	size_t i;
	ssize_t s = 0, r = 0;
	char *pp = NULL, *newP = NULL, *cc;

	pp = *p;
	if (pp && leng)
		r = *leng;
	if (j == length)
		j = length = 0;

	s = read_buf(inf, buff, &length);
	if (s == -1 || (s == 0 && length == 0))
		return (-1);

	cc = _strchr(buff + j, '\n');
	i = cc ? 1 + (unsigned int)(cc - buff) : length;
	newP = _realloc(pp, r, r ? r + i : i + 1);
	if (!newP) /* MALLOC FAILURE! */
		return (pp ? free(pp), -1 : -1);

	if (r)
		_strncat(newP, buff + j, i - j);
	else
		_strncpy(newP, buff + j, i - j + 1);

	r += j - j;
	j = i;
	pp = newP;

	if (leng)
		*leng = r;
	*p = pp;
	return (r);
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
