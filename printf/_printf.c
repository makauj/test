#include <stdarg.h>
#include <unistd.h>

void my_itoa(long num, char *str, int base) {
    char *digits = "0123456789abcdef";
    char buf[64];
    int i = 0, j = 0, k = 0, is_negative = 0;

    if (num == 0) {
        str[j++] = '0';
        str[j] = '\0';
        return;
    }

    if (num < 0 && base == 10) {
        is_negative = 1;
        num = -num;
    }

    while (num != 0) {
        buf[i++] = digits[num % base];
        num /= base;
    }

    if (is_negative) {
        buf[i++] = '-';
    }

    for (k = i - 1; k >= 0; k--) {
        str[j++] = buf[k];
    }
    str[j] = '\0';
}

void my_ftoa(double num, char *str, int precision) {
    long int_part;
    double frac_part;
    char int_str[32], frac_str[32];
    int i, j;

    int_part = (long)num;
    frac_part = num - int_part;
    
    my_itoa(int_part, int_str, 10);

    i = 0;
    while (int_str[i] != '\0') {
        str[i] = int_str[i];
        i++;
    }

    str[i++] = '.';

    for (j = 0; j < precision; j++) {
        frac_part *= 10;
    }

    my_itoa((long)frac_part, frac_str, 10);

    j = 0;
    while (frac_str[j] != '\0') {
        str[i++] = frac_str[j++];
    }
    str[i] = '\0';
}

int my_printf(const char *format, ...) {
    va_list args;
    int count = 0;
    char buffer[128];
    const char *str;
    char c;
    double f;
    unsigned int x, o;
    unsigned long u;
    void *p;
    int i;

    va_start(args, format);

    while (*format) {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 'c':
                    c = (char) va_arg(args, int);
                    count += write(STDOUT_FILENO, &c, 1);
                    break;
                case 's':
                    str = va_arg(args, char *);
                    while (*str) {
                        count += write(STDOUT_FILENO, str, 1);
                        str++;
                    }
                    break;
                case 'f':
                    f = va_arg(args, double);
                    my_ftoa(f, buffer, 6);
                    for (i = 0; buffer[i] != '\0'; i++) {
                        count += write(STDOUT_FILENO, &buffer[i], 1);
                    }
                    break;
                case 'x':
                case 'X':
                    x = va_arg(args, unsigned int);
                    my_itoa(x, buffer, 16);
                    for (i = 0; buffer[i] != '\0'; i++) {
                        count += write(STDOUT_FILENO, &buffer[i], 1);
                    }
                    break;
                case 'i':
                case 'u':
                    u = va_arg(args, unsigned long);
                    my_itoa(u, buffer, 10);
                    for (i = 0; buffer[i] != '\0'; i++) {
                        count += write(STDOUT_FILENO, &buffer[i], 1);
                    }
                    break;
                case 'o':
                    o = va_arg(args, unsigned int);
                    my_itoa(o, buffer, 8);
                    for (i = 0; buffer[i] != '\0'; i++) {
                        count += write(STDOUT_FILENO, &buffer[i], 1);
                    }
                    break;
                case '%':
                    c = '%';
                    count += write(STDOUT_FILENO, &c, 1);
                    break;
                case 'p':
                    p = va_arg(args, void *);
                    my_itoa((unsigned long)p, buffer, 16);
                    for (i = 0; buffer[i] != '\0'; i++) {
                        count += write(STDOUT_FILENO, &buffer[i], 1);
                    }
                    break;
                default:
                    c = '%';
                    count += write(STDOUT_FILENO, &c, 1);
                    count += write(STDOUT_FILENO, format, 1);
                    break;
            }
        } else {
            count += write(STDOUT_FILENO, format, 1);
        }
        format++;
    }

    va_end(args);
    return count;
}

