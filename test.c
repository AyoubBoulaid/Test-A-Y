// _printf.c

#include "main.h"
#include <stdio.h>
#include <unistd.h>

static char buffer[1024];
static int buffer_index = 0;

static void flush_buffer()
{
    if (buffer_index > 0)
    {
        write(STDOUT_FILENO, buffer, buffer_index);
        buffer_index = 0;
    }
}

static void add_char_to_buffer(char c)
{
    if (buffer_index >= sizeof(buffer))
        flush_buffer();
    buffer[buffer_index++] = c;
}

int _printf(const char *format, ...)
{
    va_list args;
    int char_count = 0;

    va_start(args, format);

    while (*format)
    {
        if (*format == '%')
        {
            format++;
            switch (*format)
            {
                case 'c': add_char_to_buffer(va_arg(args, int)); char_count++; break;
                case 's': { char *str = va_arg(args, char *); while (*str) add_char_to_buffer(*str++); char_count += strlen(str); } break;
                case 'd': case 'i':
                {
                    int num = va_arg(args, int);
                    char num_str[12]; snprintf(num_str, sizeof(num_str), "%d", num);
                    char *str = num_str; while (*str) add_char_to_buffer(*str++);
                    char_count += strlen(num_str);
                } break;
                case 'u':
                {
                    unsigned int num = va_arg(args, unsigned int);
                    char num_str[12]; snprintf(num_str, sizeof(num_str), "%u", num);
                    char *str = num_str; while (*str) add_char_to_buffer(*str++);
                    char_count += strlen(num_str);
                } break;
                case 'o':
                {
                    unsigned int num = va_arg(args, unsigned int);
                    char num_str[12]; snprintf(num_str, sizeof(num_str), "%o", num);
                    char *str = num_str; while (*str) add_char_to_buffer(*str++);
                    char_count += strlen(num_str);
                } break;
                case 'x': case 'X':
                {
                    unsigned int num = va_arg(args, unsigned int);
                    char hex_chars[16] = "0123456789abcdef";
                    if (*format == 'X') for (int i = 0; i < 16; i++) hex_chars[i] = toupper(hex_chars[i]);
                    char hex_str[9]; int i = 0;
                    do { hex_str[i++] = hex_chars[num & 0xf]; num >>= 4; } while (num > 0);
                    while (--i >= 0) add_char_to_buffer(hex_str[i]);
                    char_count += strlen(hex_str);
                } break;
                case '%': add_char_to_buffer('%'); char_count++; break;
                default: return -1;
            }
        }
        else
        {
            add_char_to_buffer(*format);
            char_count++;
        }
        format++;
    }

    va_end(args);
    flush_buffer();
    return char_count;
}
