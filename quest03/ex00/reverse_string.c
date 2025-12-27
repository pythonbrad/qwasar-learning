char* reverse_string(char* ptr) {
	char* new_ptr = strdup(ptr);
	int i = strlen(new_ptr);
	int j = -1;

	while(i > 0) {
		i--;
		j++;

		*(new_ptr+i) = *(ptr+j);
	}

	return new_ptr;
}
