#include "main.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <stddef.h>
#define UNUSED(x) (void)(x)
/*handle_write_char */
/**
* handle_write_char - Prints a character
* @c: Character to be printed
* @buffer: Character array used as a buffer for printing
* @flags: Integer value representing active formatting flags
* @width: Integer value representing the width specification
* @precision: Integer value representing the precision specifier
* @size:  Integer value representing the size specifie
*
* Return: Returns the number of characters printed
*/
int handle_write_char(char c, char buffer[],
int flags, int width, int precision, int size)
{
int i = 0;
char padd = ' ';

UNUSED(precision);
UNUSED(size);

if (flags & F_ZERO)
padd = '0';

buffer[i++] = c;
buffer[i] = '\0';

if (width > 1)
{
buffer[BUFF_SIZE - 1] = '\0';
for (i = 0; i < width - 1; i++)
buffer[BUFF_SIZE - i - 2] = padd;

if (flags & F_MINUS)
return write(1, &buffer[0], 1) +
write(1, &buffer[BUFF_SIZE - i - 1], width - 1);
else
return write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
write(1, &buffer[0], 1);
}

return (write(1, &buffer[0], 1));
}

/* WRITE_NUMBER */
/**
* write_number - Prints a number to the buffer
* @is_negative: Indicates if the number is negative
* @ind: Index position in the buffer
* @buffer: Buffer array to store the printed number
* @flags: Active flags for number formatting
* @width: Width specifier for number formatting
* @precision: Precision specifier for number formatting
* @size: Size specifier for number formatting
*
* Return: The number of chararacters printed.
*/
int write_number(int is_negative, int ind, char buffer[],
int flags, int width, int precision, int size)
{
int length = BUFF_SIZE - ind - 1;
char padd = ' ', extra_ch = 0;

UNUSED(size);

if ((flags & F_ZERO) && !(flags & F_MINUS))
padd = '0';
if (is_negative)
extra_ch = '-';
else if (flags & F_PLUS)
extra_ch = '+';
else if (flags & F_SPACE)
extra_ch = ' ';

return (write_num(ind, buffer, flags, width,
precision, length, padd, extra_ch));
}

/**
* write_num - Prints a number to the buffer
* @ind: Index position in the buffer
* @buffer: Buffer array to store the printed number
* @flags: Active flags for number formatting
* @width: width specifier for number formatting
* @prec: Precision specifier for number formatting
* @length:  Length of the number
* @padd: A padding chararcter
* @extra_c: Extra character for number
*
* Return: returns the number of printed characters.
*/
int write_num(int ind, char buffer[], int flags,
int width, int prec, int length, char padd, char extra_c)
{
int i, padd_start = 1;

if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
return (0); /* printf(".0d", 0)  no char is printed */
if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
{
buffer[ind] = padd = ' ';
--ind;
}
if (ind == BUFF_SIZE - 1)
{
buffer[ind] = extra_c;
--ind;
}
if (flags & F_MINUS)
padd_start = 0;
for (i = ind; i >= ind - length + padd_start + (prec > 0 ? 1 : 0); --i)
{
if (prec == 0 && i == ind - 1)
break;
if (i == ind - 1)
buffer[i] = '.';
else if (i == ind && flags & F_ZERO && !(flags & F_MINUS))
buffer[i] = extra_c;
else if (i >= ind - length + padd_start)
{
buffer[i] = buffer[i - (prec > 0 ? 1 : 0)];
if (buffer[i] == ' ')
buffer[i] = padd;
}
else
buffer[i] = padd;
}
return width >= length + (prec > 0 ? 1 : 0) ?
width : length + (prec > 0 ? 1 : 0);
}

/**
 * write_unsgnd - Writes an unsigned number to the buffer
 * @is_negative: Indicates whether the number is negative
 * @ind: Index at which the number starts in the buffer
 * @buffer: Array of characters
 * @flags: Flags specifier (unused in this function)
 * @width: Width specifier (unused in this function)
 * @precision: Precision specifier (unused in this function)
 * @size: Size specifier (unused in this function)
 *
 * Return: The number of characters written.
 */

int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position i */
	int length = BUFF_SIZE - ind - 1, i = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < length)
		padd = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = padd;

		buffer[i] = '\0';

		if (flags & F_MINUS) /* Asign extra char to left of buffer [buffer>padd]*/
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], i));
		}
		else /* Asign extra char to left of padding [padd>buffer]*/
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - Writes a memory address to the buffer
 * @buffer: Array of characters to store the formatted output
 * @ind: Index at which the memory address starts in the buffer
 * @length: Length of the memory address
 * @width: Width specifier for formatting
 * @flags: Flags specifier for formatting
 * @padd: Character representing the padding
 * @extra_c: Extra character for special formatting
 * @padd_start: Index at which the padding should start
 *
 * Return: Number of characters written to the buffer.
 */
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)

{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) -2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
