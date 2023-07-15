#include "shell.h"

/**
 * bfree - frees a pointer and NULLs the address
 * @ptr: pointer's address to be freed
 *
 * Return: 1 success, 0 failure
 */
int bfree(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
