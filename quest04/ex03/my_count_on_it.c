/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
*/

#ifndef STRUCT_STRING_ARRAY
#define STRUCT_STRING_ARRAY
typedef struct s_string_array
{
    int size;
    char** array;
} string_array;
#endif

#ifndef STRUCT_INTEGER_ARRAY
#define STRUCT_INTEGER_ARRAY
typedef struct s_integer_array
{
    int size;
    int* array;
} integer_array;
#endif


integer_array* my_count_on_it(string_array* array)
{
	int* array2 = calloc(array->size, sizeof(int));
	integer_array* output = malloc(sizeof(integer_array));

	output->size = array->size;

	for (int i=0; i<array->size; i++) {
		array2[i] = strlen(*(array->array+i));
	}

	output->array = array2;

	return output;
}

/*
int main() {
	char* a[3] = {"Hello", "World", "!"};
	string_array b;
	integer_array* c;

	b.size = 3;
	b.array = a;

	c = my_count_on_it(&b);

	for(int i=0; i<3; i++) {
		printf("%d\n", c->array[i]);
	}
	return 0;
}
*/
