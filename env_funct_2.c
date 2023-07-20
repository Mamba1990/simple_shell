#include "shell.h"

/**
 * get_environ - get a copy of the string array of the env
 * @inf: Structure that contains possible args
 * Return: 0
 */
char **get_environ(info_t *inf)
{
	if (!inf->environ || inf->envChanged)
	{
		inf->environ = list_to_strings(inf->env);
		inf->envChanged = 0;
	}

	return (inf->environ);
}

/**
 * _unsetenv - deletes the variable's
 * @inf: Structure that contains possible args
 * @var: the prperty of the string env var 
 */
int _unsetenv(info_t *inf, char *var)
{
	list_t *_node = inf->env;
	size_t j = 0;
	char *ptr;

	if (!_node || !var)
		return (0);

	while (_node)
	{
		ptr = starts_with(_node->s, var);
		if (ptr && *ptr == '=')
		{
			inf->envChanged = delete_node_at_index(&(inf->env), j);
			j = 0;
			_node = inf->env;
			continue;
		}
		_node = _node->next;
		j++;
	}
	return (inf->envChanged);
}

/**
 * _setenv - sets a new environment variable,
 * @inf: Structure that contains possible args
 * @var: prperty of the string env var
 * @value: envir value of string
 *  Return: 0
 */
int _setenv(info_t *inf, char *var, char *value)
{
	char *buff = NULL;
	list_t *_node;
	char *ptr;

	if (!var || !value)
		return (0);

	buff = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, value);
	_node = inf->env;
	while (_node)
	{
		ptr = starts_with(_node->s, var);
		if (ptr && *ptr == '=')
		{
			free(_node->s);
			_node->s = buff;
			inf->envChanged = 1;
			return (0);
		}
		_node = _node->next;
	}
	add_node_end(&(inf->env), buff, 0);
	free(buff);
	inf->envChanged = 1;
	return (0);
}
