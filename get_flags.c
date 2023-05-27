#include "main.h"

/**
 * get_flags - Calculates active flags in the format string
 * @format: The format string
 * @i: Pointer to the current index in the format string
 *
 * Return: The flags calculated based on the format string
 */
int get_flags(const char *format, int *i)
{
	int j, curr_i;
	int flags = 0;
	const char flags_ch[] = {'-', '+', '0', '#', ' ', '\0'};
	const int flags_arr[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		for (j = 0; flags_ch[j] != '\0'; j++)
		{
			if (format[curr_i] == flags_ch[j])
			{
				flags |= flags_arr[j];
				break;
			}
		}

		if (flags_ch[j] == 0)
			break;
	}

	*i = curr_i - 1;

	return (flags);
}
