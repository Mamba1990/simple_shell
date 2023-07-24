#include "shell.h"

/**
 * is_chain - verified actual char in buffer is a chain delim
 * @inf: Structure that contains possible args
 * @buff: buffer's char
 * @ptr: pointer of actual position
 *
 * Return: 1 if true, 0 false
 */
int is_chain(info_t *inf, char *buff, size_t *ptr)
{
	size_t k = *ptr;

	if (buff[k] == '|' && buff[k + 1] == '|')
	{
		buff[k] = 0;
		k++;
		inf->cmdBuffType = _CMD_OR;
	}
	else if (buff[k] == '&' && buff[k + 1] == '&')
	{
		buff[k] = 0;
		k++;
		inf->cmdBuffType = _CMD_AND;
	}
	else if (buff[k] == ';')
	{
		buff[k] = 0;
		inf->cmdBuffType = _CMD_CHAIN;
	}
	else
		return (0);
	*ptr = k;
	return (1);
}

/**
 * check_chain - checks chaining
 * @inf: Structure that contains possible args
 * @buff: buffer
 * @ptr: pointer of actual position
 * @j: fisrt position in buf
 * @length: buff's length
 *
 * Return: nothing
 */
void check_chain(info_t *inf, char *buff, size_t *ptr, size_t j, size_t length)
{
	size_t k = *ptr;

	if (inf->cmdBuffType == _CMD_AND)
	{
		if (inf->status)
		{
			buff[j] = 0;
			k = length;
		}
	}
	if (inf->cmdBuffType == _CMD_OR)
	{
		if (!inf->status)
		{
			buff[j] = 0;
			k = length;
		}
	}

	*ptr = k;
}

/**
 * replace_alias - places the  aliases in the splitted string
 * @inf: Structure that contains possible args
 *
 * Return: 1 success, 0 failure
 */
int replace_alias(info_t *inf)
{
	int k;
	list_t *_node;
	char *ptr;

	for (k = 0; k < 10; k++)
	{
		_node = nodeStartsWith(inf->alias, inf->argv[0], '=');
		if (!_node)
			return (0);
		free(inf->argv[0]);
		ptr = _strchr(_node->s, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		inf->argv[0] = ptr;
	}
	return (1);
}

/**
 * replace_vars - places varriables in the splitted string
 * @inf: Structure that contains possible args
 *
 * Return: 1 if succes, 0 failure
 */
int replace_vars(info_t *inf)
{
	int k = 0;
	list_t *_node;

	for (k = 0; inf->argv[k]; k++)
	{
		if (inf->argv[k][0] != '$' || !inf->argv[k][1])
			continue;

		if (!_strcmp(inf->argv[k], "$?"))
		{
			replace_string(&(inf->argv[k]),
				_strdup(convert_number(inf->status, 10, 0)));
			continue;
		}
		if (!_strcmp(inf->argv[k], "$$"))
		{
			replace_string(&(inf->argv[k]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		_node = nodeStartsWith(inf->env, &inf->argv[k][1], '=');
		if (_node)
		{
			replace_string(&(inf->argv[k]),
				_strdup(_strchr(_node->s, '=') + 1));
			continue;
		}
		replace_string(&inf->argv[k], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - string replacing
 * @ol: the pointer of old str
 * @ne: the new string
 *
 * Return: 1 success, 0 faillure
 */
int replace_string(char **ol, char *ne)
{
	free(*ol);
	*ol = ne;
	return (1);
}
