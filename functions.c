#include "main.h"

/** PRINT_CHAR **/

/**
 * print_char - Prints a character argument.
 * @types: The list of arguments
 * @buffer:  The buffer array to handle printing.
 * @flags: The active flags calculated
 * @width: Width specification
 * @precision: The precision specification
 * @size: thw size specifier
 * Return: Returns the number of characters printed.
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/* PRINT_STRING*/
/**
 * print_string - Prints the string
 * @types: Variadic argument list
 * @buffer: Buffer array to hold the printed string
 * @flags: Flag values indicating formatting options
 * @width: Width specification for the string
 * @precision: Precision specification for the string
 * @size: Size specifier for the string
 *
 * Description: This function handles the printing of a string. It takes in a
 * variadic argument list, processes any formatting options specified by the
 *
 * flags, width, precision, size parameters, and prints the resulting string
 * to the buffer array.
 *
 * Return: The number of characters printed.
 */

int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/*PRINT_PERCENT*/
/**
 * print_percent - Prints the percent sign
 * @types: Variadic argument list
 * @buffer: Buffer array to store the printed output
 * @flags: Flag options for formatting
 * @width: width specifier
 * @precision: Precision specifier
 * @size: Size specification
 * Return: Number of chars printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/* PRINT_INT */
/**
 * print_int - Prints an integer
 * @types: Variable argument list
 * @buffer: Buffer array to handle print
 * @flags: Flag indicators for formatting
 * @width: Width specification
 * @precision: Precision specifier
 * @size: Size specification
 *
 * Return: returns the number of characters printed
 */

int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

/* PRINT_BINARY */
/**
 * print_binary - Prints an unsigned number in binary format
 * @types: A variadic argument list containing the number to print
 * @buffer: A buffer array to handle the printing process
 * @flags: The active flags for formatting
 * @width: The width specification
 * @precision: The precision specification
 * @size: The size specifier
 *
 * Return: The number of characters printed.
 */

int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
