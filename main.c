#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t inf[] = { _INFO_INIT };
	int f = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (f)
		: "r" (f));

	if (ac == 2)
	{
		f = open(av[1], O_RDONLY);
		if (f == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs_(av[0]);
				_eputs_(": 0: Can't open ");
				_eputs_(av[1]);
				_eputchar_('\n');
				_eputchar_(BUFF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		inf->read_fd = f;
	}
	envListPopulator(inf);
	historyReader(inf);
	_hsh_(inf, av);
	return (EXIT_SUCCESS);
}
