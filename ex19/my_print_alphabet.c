void my_print_alphabet() {
	for (char c = 'a'; c <= 'z'; c++) {
		write(1, &c, 1);
	}

	write(1, '\n', 1);
}
