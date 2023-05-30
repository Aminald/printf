#include "main.h"

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
