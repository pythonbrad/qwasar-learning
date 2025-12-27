void my_putstr(char* ptr) {
	while (*ptr != '\0') {
		write(1, ptr, 1);
		ptr++;
	};
}
