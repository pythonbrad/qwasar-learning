/*
#include <stdio.h>
#include <stdlib.h>
*/

char* my_spaceship(char* path)
{
	int x = 0, y = 0;
	char orientation = 'U';
	int step = 1;
	char* output = calloc(64, sizeof(char));

	while (*path != '\0') {
		switch (*path) {
			case 'R':
				switch (orientation) {
					case 'D':
						orientation = 'L';
						break;
					case 'L':
						orientation = 'U';
						break;
					case 'U':
						orientation = 'R';
						break;
					case 'R':
						orientation = 'D';
						break;
					default:
						continue;

				}
				break;
			case 'L':
				switch (orientation) {
					case 'D':
						orientation = 'R';
						break;
					case 'R':
						orientation = 'U';
						break;
					case 'U':
						orientation = 'L';
						break;
					case 'L':
						orientation = 'D';
						break;
					default:
						continue;

				}
				break;
			case 'A':
				switch (orientation) {
					case 'D':
						y = y + step;
						break;
					case 'R':
						x = x + step;
						break;
					case 'U':
						y = y - step;;
						break;
					case 'L':
						x = x - step;
						break;
					default:
						continue;

				}
				break;
			default:
				continue;
		}

		path++;
	}

	snprintf(output, 64, "{x: %d, y: %d, direction: '%s'}", x, y, orientation == 'U' ? "up" : "down");

	return output;
}

/*
int main() {
	printf("%s\n", my_spaceship("RAALALL"));
	printf("%s\n", my_spaceship("AAAA"));
	printf("%s\n", my_spaceship(""));
	printf("%s\n", my_spaceship("RAARA"));

	return 0;
}
*/
