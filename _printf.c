#include <unistd.h>
#include "main.h"

/**
 * _printf - Produces output according to a format
 * @format: A character string containing directives
 *
 * Return: The number of characters printed (excluding the null byte)
 */
int _printf(const char *format, ...)
{
	va_list args;
	int i = 0, count = 0;

	va_start(args, format);

	while (format && format[i])
	{
		if (format[i] != '%')
		{
			_putchar(format[i]);
			count++;
		}
		else
		{
			i++;
			if (format[i] == '\0')
				return (-1);
			else if (format[i] == '%')
			{
				_putchar('%');
				count++;
			}
			else if (format[i] == 'c')
			{
				char c = va_arg(args, int);
				_putchar(c);
				count++;
			}
			else if (format[i] == 's')
			{
				char *str = va_arg(args, char *);
				if (str == NULL)
					str = "(null)";
				while (*str)
				{
					_putchar(*str);
					count++;
					str++;
				}
			}
		}
		i++;
	}

	va_end(args);
	return (count);
}

/**
 * _putchar - Writes a character to stdout
 * @c: The character to write
 *
 * Return: On success, the character written. On error, -1 is returned.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
