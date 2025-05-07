char* my_strcpy(char* dest, char* src) {
	char* dest2 = dest;

	while (*src != '\0') {
		*dest2 = *src;

		dest2++;
		src++;
	}

	*dest2 = '\0';

	return dest;
}
