int my_strlen(char* ptr) {
	int id;

	for (id=0; *(ptr+id) != '\0'; id++);

	return id;
}
