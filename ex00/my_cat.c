#include <stdio.h>

int main(int argc, char** argv) {
	FILE* file;
	char c[2] = {0};

	for (int i=1; i < argc; i++) {
		file = fopen(argv[i], "rb");

		if (file == NULL) {
			return 1;
		}

		while (fread(c, sizeof(char), 1, file) > 0) {
			if (*c == EOF) {
				break;
			}

			printf("%s", c);
		}

		fclose(file);
	}

	return 0;
}
