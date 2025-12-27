char* my_strrchr(char* haystack, char needle)
{
	char *ptr = 0;

	while (*haystack != '\0') {
		if (*haystack == needle) {
			ptr = haystack;
		}

		haystack++;
	}

	if (*haystack == needle) {
		ptr = haystack;
	}

	return ptr;
}
