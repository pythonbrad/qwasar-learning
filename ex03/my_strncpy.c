char* my_strncpy(char* dest, char* src, int n)
{
	char* dest2 = dest;
	
	while (n > 0 && *src != '\0') {
		*dest2 = *src;

		n--;
		src++;
		dest2++;
	}

	*dest2 = '\0';

	return dest;
}
