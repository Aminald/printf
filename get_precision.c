#include "main.h"

/**
 * get_precision - Calculates the precision for printing
 * @format: Formatted %s in which to print the arguments
 * @i: List of args to be printed.
 * @list: list of args.
 *
 * Return: Precision.
 */
int get_precision(const char *format, int *i, va_list list)
{
	int curr_i = *i + 1;
	int precision = -1;

	if (format[curr_i] != '.')
	return (precision);
	precision = 0;
	while (format[curr_i] != '\0')
	{
	if (isdigit(format[curr_i]))
	{
	precision *= 10;
	precision += format[curr_i] - '0';
	curr_i++;
	}
	else if (format[curr_i] == '*')
	{
	curr_i++;
	precision = va_arg(list, int);
	break;
	}
	else
	{
	break;
	}
	}

	*i = curr_i - 1;

	return (precision);
