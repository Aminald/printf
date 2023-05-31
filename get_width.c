#include "main.h"

/**
 * get_width - Determines the width for printing
 * @format: Format specifier string used for printing
 * @i: Index of the current argument being processed.
 * @list: list of arguments to be printed
 *
 * Return: The calculated width for printing.
 */

int get_width(const char *format, int *i, va_list list)
{
int curr_i = *i + 1;
int width = 0;

while (format[curr_i] != '\0')
{
if (is_digit(format[curr_i]))
{
width = width * 10 + (format[curr_i] - '0');
curr_i++;
}
else if (format[curr_i] == '*')
{
curr_i++;
width = va_arg(list, int);
break;
}
else
{
break;
}
}

*i = curr_i - 1;

return (width);
}
