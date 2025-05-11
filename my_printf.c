#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>


char base_to_symbol(int value, char base) {
	char* oct_symbols = "01234567";
	char* dec_symbols = "0123456789";
	char* hex_symbols = "0123456789abcdef";
	char* cap_hex_symbols = "0123456789ABCDEF";

	if (base == 'o') {
		return oct_symbols[value];
	} else if (base == 'd') {
		return dec_symbols[value];
	} else if (base == 'x') {
		return hex_symbols[value];
	} else if (base == 'X') {
		return cap_hex_symbols[value];
	}

	return value;
}

int char_to_base(char base) {
	if (base == 'o') {
		return 8;
	} else if (base == 'x') {
		return 16;
	} else if (base == 'X') {
		return 16;
	}
	
	return 10;
}

int my_shift_insert(char** dest, char c, int idx, int length) {
	// length + new char + '\0'
	*dest = realloc(*dest, (length+2) * sizeof(char));

	// shift
	for (int i = length; i > idx; i--) {
		(*dest)[i] = (*dest)[i-1];
	}

	// insert
	(*dest)[idx] = c;

	// add string terminator
	(*dest)[length+1] = '\0';

	return length + 1;
}

int my_itoa(char** dest, long value, char base) {
	int rem;
	int sign = 1;
	int length = 0;
	int dividend = char_to_base(base);

	if (value == 0) {
		my_shift_insert(dest, '0', 0, length++);
	} else if (value < 0) {
		sign = -1;
		value = -value;
	}

	while (value > 0) {
		rem = value % dividend;
		value = value / dividend;

		my_shift_insert(dest, base_to_symbol(rem, base), 0, length++);
	}

	if (sign < 0) {
		my_shift_insert(dest, '-', 0, length++);
	}

	return length;
}

char* my_strchr(char* str, char c) {
	while (*str != c && *str != '\0') str++;

	return str;
}

int my_strlen(char* str) {
	return my_strchr(str, '\0') - str;
}

int print_dec(int arg) {
	char* s = NULL;
	int size = my_itoa(&s, arg, 'd');
	
	return write(1, s, size);
}

int print_oct(unsigned int arg) {
	char* s = NULL;
	int size = my_itoa(&s, arg, 'o');
	
	return write(1, s, size);
}

int print_unsigned_int(unsigned int arg) {
	char* s = NULL;
	int size = my_itoa(&s, arg, 'd');
	
	return write(1, s, size);
}

int print_hex(unsigned int arg) {
	char* s = NULL;
	int size = my_itoa(&s, arg, 'x');
	
	return write(1, s, size);
}

int print_cap_hex(unsigned int arg) {
	char* s = NULL;
	int size = my_itoa(&s, arg, 'X');
	
	return write(1, s, size);
}

int print_chr(char arg) {
	return write(1, &arg, 1);;
}

int print_str(char* arg) {
	if (arg == NULL) {
		return write(1, "(null)", 6);
	}

	return write(1, arg, my_strlen(arg));
}

int print_ptr(void* arg) {
	char* s = NULL;
	int size;

	if (arg == NULL) {
		return write(1, "(nil)", 5);
	}

	size = my_itoa(&s, (long) arg, 'x');
	
	return write(1, "0x", 2) + write(1, s, size);
}

int my_printf(char* restrict format, ...) {
	va_list ap;
	int size = 0;

	va_start(ap, format);

	while (*format != '\0') {
		if (*format == '%') {
			while (*my_strchr("cdopsuxX%", *++format) == '\0') {
				if (*format == '\0') return -1;
			};

			switch (*format) {
				case 'c':
					size += print_chr((char) va_arg(ap, unsigned int));
					break;
				case 'd':
					size += print_dec(va_arg(ap, int));
					break;
				case 'o':
					size += print_oct(va_arg(ap, unsigned int));
					break;
				case 'p':
					size += print_ptr(va_arg(ap, void*));
					break;
				case 's':
					size += print_str(va_arg(ap, char*));
					break;
				case 'u':
					size += print_unsigned_int(va_arg(ap, unsigned int));
					break;
				case 'x':
					size += print_cap_hex(va_arg(ap, unsigned int));
					break;
				case 'X':
					size += print_cap_hex(va_arg(ap, unsigned int));
					break;
				case '%':
					size += write(1, "%", 1);
					break;
				default:
					// TODO
					break;
			}

			// We move after the conversion specifier
			format++;
			continue;
		}

		size += write(1, format++, 1);
	}

	va_end(ap);

	return size;
}

/*
int main() {
	char ptr[6] = "hello\0";

	printf("size: %d\n", my_printf("Hello %%s=%s\n", ptr));
	printf("size: %d\n", printf("Hello %%s=%s\n", ptr));
	printf("size: %d\n", my_printf("Hello %%s=%s\n", NULL));
	printf("size: %d\n", printf("Hello %%s=%s\n", NULL));
	printf("size: %d\n", my_printf("Hello %%c=%c\n", *ptr));
	printf("size: %d\n", printf("Hello %%c=%c\n", *ptr));
	printf("size: %d\n", my_printf("Hello %%c=%c\n", NULL));
	printf("size: %d\n", printf("Hello %%c=%c\n", NULL));
	printf("size: %d\n", my_printf("Hello %%p=%p\n", *ptr));
	printf("size: %d\n", printf("Hello %%p=%p\n", *ptr));
	printf("size: %d\n", my_printf("Hello %%p=%p\n", NULL));
	printf("size: %d\n", printf("Hello %%p=%p\n", NULL));
	printf("size: %d\n", my_printf("Hello %%d=%d\n", 0));
	printf("size: %d\n", printf("Hello %%d=%d\n", 0));
	printf("size: %d\n", my_printf("Hello %%d=%d\n", INT_MAX));
	printf("size: %d\n", printf("Hello %%d=%d\n", INT_MAX));
	printf("size: %d\n", my_printf("Hello %%d=%d\n", INT_MIN));
	printf("size: %d\n", printf("Hello %%d=%d\n", INT_MIN));
	printf("size: %d\n", my_printf("Hello %%o=%o\n", UINT_MAX));
	printf("size: %d\n", printf("Hello %%o=%o\n", UINT_MAX));
	printf("size: %d\n", my_printf("Hello %%x=%x\n", UINT_MAX));
	printf("size: %d\n", printf("Hello %%x=%x\n", UINT_MAX));
	printf("size: %d\n", my_printf("Hello %%u=%u\n", UINT_MAX));
	printf("size: %d\n", printf("Hello %%u=%u\n", UINT_MAX));;

	return 0;
}
*/
