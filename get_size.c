#include "main.h"

/**
 * get_size -  Determines the appropriate size for casting the argument
 * @format: The format string containing the formatting instructions
 * @i: The argument to be printed
 *
 * Return: The size specifier for casting the argument
 */
int get_size(const char *format, int *i)
{
	int curr_i = *i + 1;
	int size = 0;

	if (format[curr_i] == 'l')
	{
	size = S_LONG;
	}
	else if (format[curr_i] == 'h')
	{
	size = S_SHORT;
	}
	else
	{
	*i = curr_i - 1;
	}
	if (size == 0)
	{
	*i = curr_i - 1;
	}
	else
	{
	*i = curr_i;
	}
	return (size);
	}
