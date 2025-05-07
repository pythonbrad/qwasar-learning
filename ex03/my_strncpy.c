char* my_strncpy(char* dest, char* src, int n)
{
	char* p;
	
	p = mempcpy(dest, src, n);
	*p = '\0';

	return dest;
}

