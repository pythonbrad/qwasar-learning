char* my_strcpy(char* dest, char* src) {
	char* p;

	p = mempcpy(dest, src, strlen(src));
	*p = '\0';

	return dest;
}
