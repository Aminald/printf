#include <unistd.h>
/**
 * _putchar - Outputs a character to the standard output.
 * @c: The character to written.
 *
 * Return: Returns 1 on success (the character written). On error, returns -1.
 */
int _putchar(char c)
{
return (write(1, &c, 1));
}
