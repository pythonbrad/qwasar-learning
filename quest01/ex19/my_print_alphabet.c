void my_putchar(char c) {
	write(1, &c, 1);
}

void my_print_alphabet() {
	for (char c = 'a'; c <= 'z'; c++) {
		my_putchar(c);
	}

	my_putchar('\n');
}
