char* my_strchr(char* haystack, char needle)
{
	while (*haystack != needle && *haystack != '\0') {
		haystack++;
	}

	return haystack;
}
