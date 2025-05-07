void my_print_reverse_alphabet() {
	for (char c = 'z'; c >= 'a'; c--) {
		write(1, &c, 1);
	}

	write(1, '\n', 1);
}
