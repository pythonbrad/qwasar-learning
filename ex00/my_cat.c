#include <stdio.h>

int main(int argc, char** argv) {
	FILE* file;
	char c;

	for (int i=1; i < argc; i++) {
		file = fopen(argv[i], "r");

		if (file == NULL) {
			return 1;
		}

		while (1) {
			c = fgetc(file);

			if (c == EOF) {
				break;
			}

			printf("%c", c);
		}

		fclose(file);
	}

	printf("\n");

	return 0;
}
