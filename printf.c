#include "main.h"
#include <stdio.h>  
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Produces output according to a format
 * @format: A character string containing directives
 * Return: The number of characters printed (excluding the null byte)
 */
int _printf(const char *format, ...)
{
	int x, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (x = 0; format && format[x] != '\0'; x++)
	{
		if (format[x] != '%')
		{
			buffer[buff_ind++] = format[x];
			if (buff_ind == BUFF_SIZE)
			{
				print_buffer(buffer, &buff_ind);
			}
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &x);
			width = get_width(format, &x, list);
			precision = get_precision(format, &x, list);
			size = get_size(format, &x);
			++x;
			printed = handle_print(format, &x, list, buffer,
				flags, width, precision, size);
			if (printed == -1)
			{
				va_end(list);
				return (-1);
			}
			printed_chars += printed;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(list);

	return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exists
 * @buffer: An array of characters
 * @buff_ind: Pointer to add the next character, represents the length
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
	{
		write(1, &buffer[0], *buff_ind);
	}

	*buff_ind = 0;
}
/**
 * print_integer - Prints an integer
 * @num: The number to print
 * Return: The number of characters printed
 */
int print_integer(int num)
{
	int count = 0;

	if (num < 0)
	{
		putchar('-');
		count++;
		num = -num;
	}

	if (num >= 10)
		count += print_integer(num / 10);

	putchar('0' + (num % 10));
	count++;

	return (count);
}
