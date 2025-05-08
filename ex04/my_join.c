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
		// allocate memory for the separator
		output = realloc(output, (i+1) * sizeof(char));

		for(k=0; str[k] != '\0'; k++) {
			// allocate an additional memory for the character
			output = realloc(output, (i+2) * sizeof(char));
			output[i] = str[k];

			i++;
		}

		output[i] = *sep;
		i++;
	}

	if (i > 0) {
		output[i-1] = '\0';
	}

	return output;
}

/*
int main() {
	char* a[4] = {"Hello", "World", "!", ""};
	string_array b;
	b.size = 4;
	b.array = a;

	printf("%s\n", my_join(&b, "-"));

	return 0;
}
*/
