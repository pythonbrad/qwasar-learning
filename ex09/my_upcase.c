char* my_upcase(char* ptr)
{
	char* new_ptr = strdup(ptr);
	char* new_ptr2 = new_ptr;

	while (*new_ptr2 != '\0') {
		if (*new_ptr2 >= 'a' && *new_ptr2 <= 'z') {
			*new_ptr2 = *new_ptr2 - 32;
		}
		new_ptr2++;
	}

	return new_ptr;
}
