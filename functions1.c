#include "main.h"
#include <unistd.h> /* Include the necessary header for write() function */

#define UNUSED(x) (void)(x) /* Macro to silence unused parameter warnings */

/**
 * write_unsgnd - Writes a string to the standard output
 * @filedes: File descriptor (0 for standard output)
 * @nbytes: Number of bytes to write
 * @buf: Buffer containing the string to write
 * @flags: Integer value representing active formatting flags
 * @width: Integer value representing the width specification
 * @precision: Integer value representing the precision specification
 * @size: Integer value representing the size specifier
 * Return: The number of characters written
 */
int write_unsgnd(int filedes, int nbytes, char *buf,
int flags, int width, int precision, int size)
{
UNUSED(flags);
UNUSED(width);
UNUSED(precision);
UNUSED(size);
return (write(filedes, buf, nbytes));
/* Use the write() function to write the buffer to the standard output */
}

/**
 * print_unsigned - Prints an unsigned number
 * @types: Variadic argument list containing the unsigned number to be printed
 * @buffer: Character array used as a buffer for printing
 * @flags:  Integer value representing active formatting flags
 * @width: Integer value representing the width specification
 * @precision: Integer value representing the precision specification
 * @size: Integer value representing the size specifier
 * Return: The number of characters printed
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int p = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[p--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[p--] = (num % 10) + '0';
		num /= 10;
	}

	p++;

	return (write_unsgnd(0, p, buffer, flags, width, precision, size));
}

/**
 * print_octal - Prints an unsigned number in octal format
 * @types: Variadic argument list containing the unsigned number to be printed
 * @buffer: Character array used as a buffer for printing
 * @flags: Integer value representing active formatting flags
 * @width: Integer value representing the width specification
 * @precision: Integer value representing the precision specification
 * @size: Integer value representing the size specifier
 * Return: The number of characters printed
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int q = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[q--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[q--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[q--] = '0';

	q++;

	return (write_unsgnd(0, q, buffer, flags, width, precision, size));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/**
 * print_hexa_upper - Prints an unsigned number in uppercase hexa format
 * @types: Variadic argument list containing the unsigned number to be printed
 * @buffer: Character array used as a buffer for printing
 * @flags: Integer value representing active formatting flags
 * @width: Integer value representing the width specification
 * @precision: Integer value representing the precision specification
 * @size: Integer value representing the size specifier
 * Return: The number of characters printed
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/**
 * print_hexa - Prints a hexadecimal number in lower or upper case
 * @types: Variadic argument list containing the number to be printed
 * @map_to: Array of characters used to map the number to the desired case
 * @buffer: Character array used as a buffer for printing
 * @flags:  Integer value representing active formatting flag
 * @flag_ch: Character value representing the active formatting flag
 * @width: Integer value representing the width specification
 * @precision:  Integer value representing the precision specification
 * @size: Integer value representing the size specifier
 * @size: Integer value representing the size specification
 * Return: Number of characters printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)

{
	int w = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[w--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[w--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[w--] = flag_ch;
		buffer[w--] = '0';
	}

	w++;

	return (write_unsgnd(0, w, buffer, flags, width, precision, size));
}
