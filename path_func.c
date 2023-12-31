#include "shell.h"
/**
 * isCommd - check  executability of the file as command
 * @inf: structure that contains possible args
 * @path: path
 * Return: 1 success, 0 failure
 */
int isCommd(info_t *inf, char *path)
{
	struct stat st;

	(void)inf;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * charsDuplicator - gives a duplication to characters
 * @path_str: string's path
 * @_start: debut of index
 * @_stop:  end of index
 * Return: address of the duplicated character
 */
char *charsDuplicator(char *path_str, int _start, int _stop)
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
 * pathFinder - localises the command in path
 * @inf:  Structure that contains possible args
 * @path_str: PATH's string
 * @_cmd: command
 * Return: path of command or NULL
 */
char *pathFinder(info_t *inf, char *path_str, char *_cmd)
{
	int j = 0, currPos = 0;
	char *_path;

	if (!path_str)
		return (NULL);
	if ((_strlen(_cmd) > 2) && starts_with(_cmd, "./"))
	{
		if (isCommd(inf, _cmd))
			return (_cmd);
	}
	while (1)
	{
		if (!path_str[j] || path_str[j] == ':')
		{
			_path = charsDuplicator(path_str, currPos, j);
			if (!*_path)
				_strcat(_path, _cmd);
			else
			{
				_strcat(_path, "/");
				_strcat(_path, _cmd);
			}
			if (isCommd(inf, _path))
				return (_path);
			if (!path_str[j])
				break;
			currPos = j;
		}
		j++;
	}
	return (NULL);
}
