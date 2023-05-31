#include "main.h"
/**
 * handle_print - Handles the printing of an argument based on its type
 * @fmt: The format string specifying the desired output format.
 * @ind: Pointer to the current index in the format string.
 * @list: List of arguments to be printed.
 * @buffer: Character array used as a buffer for printing.
 * @flags: Integer value representing active formatting flags.
 * @width: Integer value representing the width specification.
 * @precision: Integer value representing the precision specification.
 * @size: Integer value representing the size specifier.
 *
 * Return: returns the number of characters to be printed.
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
int flags, int width, int precision, int size)
{
	int l, unknown_len = 0, printed_chars = -1;

	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};

	for (l = 0; fmt_types[l].fmt != '\0'; l++)
	{
		if (fmt[*ind] == fmt_types[l].fmt)
			return (fmt_types[l].fn(list, buffer, flags, width, precision, size));
	}

	if (fmt_types[l].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);

		unknown_len += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unknown_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknown_len += write(1, &fmt[*ind], 1);
		return (unknown_len);
	}

	return (printed_chars);
}
