char* my_strstr(char* haystack, char* needle)
{
	char* start_ptr = NULL;
	char* curr_ptr = needle;

	if (*needle == '\0') {
		return haystack;
	}

	while (*haystack != '\0') {
		if (*haystack == *curr_ptr) {
			if (start_ptr == NULL) {
				start_ptr = haystack;
			}

			if (*(curr_ptr+1) == '\0') {
				return start_ptr;
			}

			curr_ptr++;
		} else {
			start_ptr = NULL;	
			curr_ptr = needle;	
		}
		
		haystack++;
	}

	return NULL;
}
