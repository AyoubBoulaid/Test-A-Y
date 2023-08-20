#include <stdarg.h>
#include <unistd.h>

/**
 * _putchar - Writes a character to stdout.
 * @c: The character to be written.
 *
 * Return: 1 on success, -1 on error.
 */
int _putchar(char c)
{
    return write(1, &c, 1);
}

/**
 * _printf - Produces output according to a format.
 * @format: Format string with conversion specifiers.
 *
 * Return: Number of characters printed.
 */
int _printf(const char *format, ...)
{
    va_list args;
    int i = 0, len = 0;

    va_start(args, format);
    if (format == NULL)
        return -1;

    while (format[i] != '\0')
    {
        if (format[i] == '%' && format[i + 1] != '\0')
        {
            if (format[i + 1] == 'c')
            {
                char ch = va_arg(args, int);
                _putchar(ch);
                len++;
                i += 2;
                continue;
            }
            else if (format[i + 1] == 's')
            {
                char *str = va_arg(args, char *);
                if (str == NULL)
                    str = "(null)";
                while (*str != '\0')
                {
                    _putchar(*str);
                    len++;
                    str++;
                }
                i += 2;
                continue;
            }
            else if (format[i + 1] == '%')
            {
                _putchar('%');
                len++;
                i += 2;
                continue;
            }
        }
        
        _putchar(format[i]);
        len++;
        i++;
    }
    
    va_end(args);
    return len;
}

