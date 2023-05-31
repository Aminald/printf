#include "main.h"

/**
 * is_printable - Determines if a character is printable
 * @c: The character to be evaluated.
 *
 * Return: 1 if the c is printable, 0 otherwise
 */

int is_printable(char c)
{
	return ((c >= 32 && c < 127) ? 1 : 0);
}

/**
 * append_hexa_code - Adds ASCII code in hexadecimal format to the buffer array
 * @buffer: Character array to store the result.
 * @i: Index at which to start appending the hexadecimal code.
 * @ascii_code: ASCII code to be converted to hexadecimal.
 * Return: Always returns 3
 */

int append_hexa_code(char ascii_code, char buffer[], int i)
{
	const char map_to[] = "0123456789ABCDEF";

	if (ascii_code < 0)
	ascii_code *= -1;

	buffer[i++] = '\\';
	buffer[i++] = 'x';

	buffer[i++] = map_to[ascii_code / 16];
	buffer[i] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - Checks chether a char is digit
 * @c: Character to be evaluated
 *
 * Return: return 1 if c is a digit, 0 otherwise
 */

int is_digit(char c)
{
	return ((c >= '0' && c <= '9') ? 1 : 0);
}

/**
 * convert_size_number - Performs a type conversion on a given number 
 * @num: The number to be converted.
 * @size: Number specifier indicating the desired conversion
 *
 * Return: Converted value of num
 */

long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
	return (num);
	else if (size == S_SHORT)
	return ((short)num);

	return ((int)num);
}

/**
 * convert_size_unsgnd - Performs a type conversion on a number
 * @num: Number to be converted
 * @size: Size specifier indicating the desired type of conversion
 *
 * Return: Converted value of num based on the specified size
 */

long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
	return (num);
	else if (size == S_SHORT)
	return ((unsigned short)num);

	return ((unsigned int)num);
}
