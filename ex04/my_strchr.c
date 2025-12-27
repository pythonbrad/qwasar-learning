char* my_strchr(char* haystack, char needle)
{
	while (*haystack != '\0' && *haystack != needle) {
		haystack++;
	}

	if (*haystack == needle) {
		return haystack;
	}

	return 0;
}
