int my_string_index(char* haystack, char needle) {
	for (int id = 0; *(haystack+id) != '\0'; id++) {
		if (*(haystack+id) == needle) {
			return id;
		}
	}

	return -1;
}
