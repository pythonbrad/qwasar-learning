int my_strcmp(char* a, char* b) {
	int i = 0;

	while (1) {
		if (a[i] != b[i]) {
			return a[i] > b[i] ? 1: -1;
		}
		
		if (a[i] == '\0') {
			break;
		}

		i++;
	}
}
