void my_putchar(char c) {
	write(1, &c, 1);
}

void my_print_reverse_alphabet() {
	for (char c = 'z'; c >= 'a'; c--) {
		my_putchar(c);
	}

	my_putchar('\n');
}
