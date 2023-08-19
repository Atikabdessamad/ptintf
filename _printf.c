#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: format.
 * Return: int
 */
int _printf(const char *format, ...)
{
	int x, xprinted = 0, xprinted_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list l;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(l, format);

	for (x = 0; format && format[x] != '\0'; x++)
	{
		if (format[x] != '%')
		{
			buffer[buff_ind++] = format[x];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write(1, &format[x], 1);*/
			xprinted_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &x);
			width = get_width(format, &x, l);
			precision = get_precision(format, &x, l);
			size = get_size(format, &x);
			++x;
			xprinted = handle_print(format, &x, l, buffer,
				flags, width, precision, size);
			if (xprinted == -1)
				return (-1);
			xprinted_chars += xprinted;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(l);

	return (xprinted_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: char
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
