#include <stdio.h>
#include <stdarg.h>

/**
 * _printf - custom printf function
 * @str: string
 * Return: count
 */

int _printf(const char *str, ...)
{
	va_list ptr;
	int count = 0;

	va_start(ptr, str);

	while (*str != '\0')
	{
		if (*str != '%')
		{
			putchar(*str);
			count++;
		}
		else
		{
			switch (*++str)
			{
				case 'd':
					count += fprintf(stdout, "%d", va_arg(ptr, int));
					break;
				case 'c':
					count += fprintf(stdout, "%c", va_arg(ptr, int));
                                        break;
				case 's':
					count += fprintf(stdout, "%s", va_arg(ptr, char *));
                                        break;
				case 'f':
					count += fprintf(stdout, "%f", va_arg(ptr, double));
                                        break;
				case 'x':
					count += fprintf(stdout, "%x", va_arg(ptr, unsigned int));
                                        break;
				case 'X':
					count += fprintf(stdout, "%X", va_arg(ptr, unsigned int));
                                        break;
				case 'i':
					count += fprintf(stdout, "%i", va_arg(ptr, long));
					break;
				case 'u':
					count += fprintf(stdout, "%u", va_arg(ptr, long));
					break;
				case 'o':
					count += fprintf(stdout, "%o", va_arg(ptr, int));
					break;
				case '%':
					count += fprintf(stdout, "%%", va_arg(ptr, int));
					break;
				case 'p':
					count += fprintf(stdout, "%p", va_arg(ptr, char *));
					break;
				default:
					putchar('%');
					putchar(*str);
					count += 2;
					break;
			}
		}
		str++;
	}
	va_end(ptr);
	return count;
}
