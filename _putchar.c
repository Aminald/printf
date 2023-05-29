#include <unistd.h>
/**
 * _putchar - Writes a character to stdout.
 * @c: The character to write.
 *
 * Return: 1 on success, the character written. On error, -1 is returned.
 */
int _putchar(char c)
{
return (write(1, &c, 1));
}
