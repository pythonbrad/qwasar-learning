/*
#include <stdio.h>
#include <stdlib.h>
*/

#ifndef STRUCT_STRING_ARRAY
#define STRUCT_STRING_ARRAY
typedef struct s_string_array
{
    int size;
    char** array;
} string_array;
#endif

int str_add(char** dest, char* src, int index) {
	for(int k=0; src[k] != '\0'; k++) {
		// allocate an additional memory for the character
		*dest = realloc(*dest, (index+2) * sizeof(char));
		(*dest)[index] = src[k];

		index++;
	}

	(*dest)[index] = '\0';

	return index;
}

char* my_join(string_array* array, char* sep)
{
	char* str;
	int i = 0, j, k;
	char* output;
	
	if (array->size == 0) {
		return 0;
	}

	output = calloc(0, sizeof(char));

	for(j=0; j < array->size; j++) {
		str = array->array[j];

		i = str_add(&output, str, i);

		if (j+1 == array->size) continue;
		i = str_add(&output, sep, i);
	}

	return output;
}

/*
int main() {
	char* a[4] = {"Hello", "World", "!", ""};
	string_array b;
	b.size = 4;
	b.array = a;

	printf("%s\n", my_join(&b, "blah"));

	return 0;
}
*/
