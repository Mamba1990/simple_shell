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
#if _USE_GETLINE
		
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
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *inf, char **ptr, size_t *length)
{
	static char buf[READ_BUFF_S];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(inf, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

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
