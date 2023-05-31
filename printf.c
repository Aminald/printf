#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

#define BUFF_SIZE 1024

void print_buffer(char buffer[], int *buff_ind);
int get_flags(const char *format, int *x);
int get_width(const char *format, int *x, va_list list);
int get_precision(const char *format, int *x, va_list list);
int get_size(const char *format, int *x);
void print_buffer(char buffer[], int *buff_ind);


/**
 * _printf - Produces output according to a format
 * @format: A character string containing directives
 * get_flags - Retrieves the flags from the format string
 * get_width - Retrieves the width from the format string
 * get_precision - Retrieves the precision from the format string
 * get_size - Retrieves the size from the format string
 * handle_print - Handles the conversion specifier and prints formatted output
 * Return: The number of characters printed (excluding the null byte)
 */
int _printf(const char *format, ...)
{
        va_list args;
        int printed_chars = 0;

        va_start(args, format);

        while (*format)
        {
                if (*format == '%')
                {
                        format++;

                        if (*format == 'd' || *format == 'i')
                        {
                                int num = va_arg(args, int);
                                printed_chars += putchar(num);
                        }
                }
                else
                {
                        printed_chars += putchar(*format);
                }

                format++;
        }

        va_end(args);

        return printed_chars;
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
