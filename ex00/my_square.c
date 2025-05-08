#include <stdio.h>
#include <stdlib.h>

void draw(int width, int height) {
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if (j == 0 && i == 0 || j == 0 && i+1 == width || j+1 == height && i == 0 || j+1 == height && i+1 == width) {
				printf("o");
				continue;
			} else if (j == 0 || j+1 == height) {
				printf("-");
			} else if (i == 0 || i+1 == width) {
				printf("|");
			} else {
				printf(" ");
			}
		}

		printf("\n");
	}
}

int main(int argc, char** argv) {
	int width = atoi(argv[1]);
	int height = atoi(argv[2]);

	draw(width, height);
	// draw(5, 3);
	// draw(5, 1);
	// draw(1, 1);
	// draw(1, 5);
	// draw(4, 4);

	return 0;
}
