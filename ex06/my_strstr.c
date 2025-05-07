char* my_strstr(char* haystack, char* needle)
{
	int checkpoint = 0;
	char* curr_ptr = needle;

	// empty string
	if (*needle == '\0') {
		return haystack;
	}

	while (*haystack != '\0' && *curr_ptr != '\0') {
		if (*haystack == *curr_ptr) {
			curr_ptr++;
			checkpoint++;
		} else {
			curr_ptr = needle;
			haystack = haystack - checkpoint;
			checkpoint = 0;
		}
		
		haystack++;
	}

	if (*curr_ptr != '\0') {
		return 0;
	}

	return haystack - checkpoint;
}
