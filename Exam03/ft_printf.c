#include <stdarg.h>
#include <unistd.h>

void	put_str(char *str, int *printed)
{
	if (!str)
		str = "(null)";
	while (*str)
		*printed += write(1, str++, 1);
}

void	put_num(long long int num, int base, int *printed)
{
	if (num < 0)
		*printed += write(1, "-", 1);
	if (num >= base)
		put_num(num / base, base, printed);
	*printed += write(1, &"0123456789abcdef"[num % base], 1);
}

int ft_printf(const char *format,...)
{
	int	printed = 0;
	va_list ptr;
	va_start(ptr, format);
	while (*format)
	{
		if (*format == '%')
		{
			if (!*(format + 1))
				break ;
			if (*(format + 1) != 'd' && *(format + 1) != 'x' && *(format + 1) != 's')
			{
				printed += write(1, "%", 1);
				printed += write(1, format + 1, 1);
			}
			format++;
			if (*format == 's')
				put_str(va_arg(ptr, char *), &printed);
			else if (*format == 'd')
				put_num((long long int)va_arg(ptr, int), 0xA, &printed);
			else if (*format == 'x')
				put_num((long long int)va_arg(ptr, unsigned int), 0x10, &printed);
		}
		else
			printed += write(1, format, 1);
		format++;
	}
	va_end(ptr);
	return printed;
}
