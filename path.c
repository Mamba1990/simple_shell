#include "shell.h"
/**
 * is_cmd - check if file is an executable command
 * @info: parameter struct
 * @path: path
 * Return: 1 on success, 0 on failure
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicate characters
 * @pathstr: PATH string
 * @start: index of starting
 * @stop: index of stopping
 * Return: pointer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int j = 0, c = 0;

	for (c = 0, j = start; j < stop; j++)
		if (pathstr[j] != ':')
			buf[c++] = pathstr[j];
	buf[c] = 0;
	return (buf);
}

/**
 * find_path - find the command in path string
 * @info: parameter struct
 * @pathstr: PATH string
 * @cmd: command
 * Return: path of command or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int j = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[j] || pathstr[j] == ':')
		{
			path = dup_chars(pathstr, curr_pos, j);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[j])
				break;
			curr_pos = j;
		}
		j++;
	}
	return (NULL);
}
