#include "shell.h"
/**
 * is_cmd - check  executability of the file as command
 * @inf: structure that contains possible args
 * @_path: path
 * Return: 1 success, 0 failure
 */
int is_cmd(info_t *inf, char *_path)
{
	struct stat _st;

	(void)inf;
	if (!_path || stat(_path, &_st))
		return (0);

	if (_st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - gives a duplication to characters
 * @path_str: string's path
 * @_start: debut of index
 * @_stop:  end of index
 * Return: address of the duplicated character
 */
char *dup_chars(char *path_str, int _start, int _stop)
{
	static char buff[1024];
	int j = 0, c = 0;

	for (c = 0, j = _start; j < _stop; j++)
		if (path_str[j] != ':')
			buff[c++] = path_str[j];
	buff[c] = 0;
	return (buff);
}

/**
 * find_path - localises the command in path 
 * @inf:  Structure that contains possible args
 * @path_str: PATH's string
 * @_cmd: command
 * Return: path of command or NULL
 */
char *find_path(info_t *inf, char *path_str, char *_cmd)
{
	int j = 0, currPos = 0;
	char *_path;

	if (!path_str)
		return (NULL);
	if ((_strlen(_cmd) > 2) && starts_with(_cmd, "./"))
	{
		if (is_cmd(inf, _cmd))
			return (_cmd);
	}
	while (1)
	{
		if (!path_str[j] || path_str[j] == ':')
		{
			_path = dup_chars(path_str, currPos, j);
			if (!*_path)
				_strcat(_path, _cmd);
			else
			{
				_strcat(_path, "/");
				_strcat(_path, _cmd);
			}
			if (is_cmd(inf, _path))
				return (_path);
			if (!path_str[j])
				break;
			currPos = j;
		}
		j++;
	}
	return (NULL);
}
