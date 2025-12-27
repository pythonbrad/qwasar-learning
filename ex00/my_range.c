/*
#include <stdio.h>
#include <stdlib.h>
*/

int* my_range(int min, int max)
{
	int* array;
	int* ptr;
	int size;

	if (min >= max) {
		return 0;
	}

	size = max - min;
	array = malloc(size * sizeof(int));
	ptr = array;

	for (int i=min; i<max; i++) {
		*ptr = i;
		ptr++;
	}

	return array;
}

/*
int main() {
	int min = -10;
	int max = 10;
	int* array = my_range(min, max);

	for(int i=0; i<(max-min); i++) {
		printf("%d\n", array[i]);
	}
	return 0;
}
*/
