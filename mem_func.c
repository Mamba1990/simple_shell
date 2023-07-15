#include "shell.h"

/**
* _memset - fills memory with a constant byte.
* @s: starting address of memory to be filled
* @b: constant byte
* @n: number of bytes of the memory area to be changed.
*
* Return: array with changed bytes.
*/
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int j;
	
	j = 0;

	while (j < n)
	{
		s[j] = b;
		j++;
	}
	return (s);
}

/**
 * ffree - frees a strings
 * @pp: string input
 * Return: nothing
 */
void ffree(char **ss)
{
	char **p = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(p);
}

/**
 * _realloc - reallocates a memory bloch
 * @p: address of previous malloc'ated block
 * @oldSize: size of previous block(byte)
 * @newSize: size of new block(byte)
 *
 * Return: address of realoccted blck
 */
void *_realloc(void *p, unsigned int oldSize, unsigned int newSize)
{
	char *pt;

	if (!p)
		return (malloc(newSize));
	if (!newSize)
		return (free(p), NULL);
	if (newSize == oldSize)
		return (p);

	pt = malloc(newSize);
	if (!pt)
		return (NULL);

	oldSize = oldSize < newSize ? oldSize : newSize;
	while (oldSize--)
		pt[oldSize] = ((char *)p)[oldSize];
	free(p);
	return (pt);
}
