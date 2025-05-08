/*
#include <unistd.h>
*/

#ifndef STRUCT_STRING_ARRAY
#define STRUCT_STRING_ARRAY
typedef struct s_string_array
{
    int size;
    char** array;
} string_array;
#endif


void my_putstr(char* string_ptr) {
	while (*string_ptr != '\0') {
		write(1, string_ptr, 1);
		string_ptr++;
	}

	write(1, "\n", 1);
};

void my_print_words_array(string_array* array_ptr)
{
	for (int i=0; i < array_ptr->size; i++) {
		my_putstr(*(array_ptr->array+i));
	}
}

/*
int main() {
	char* a[3] = {"Hello", "World", "!"};
	string_array b;
	b.size = 3;
	b.array = a;

	my_print_words_array(&b);
	return 0;
}
*/
