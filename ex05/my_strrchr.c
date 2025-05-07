char* my_strrchr(char* haystack, char needle)
{
	char *ptr = NULL;

	while (*haystack != '\0') {
		if (*haystack == needle) {
			ptr = haystack;
		}

		haystack++;
	}

	return ptr;
}
