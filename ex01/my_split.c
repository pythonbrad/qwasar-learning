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

char *my_strtok(char *str, char *sep) {
	char *ptra = str;
	char *ptrb = sep;
	
	while (*ptra != '\0' && *ptrb != '\0') {
		if (*ptra != *ptrb) {
			ptra = ++str;
			ptrb = sep;

			continue;
		}

		ptra++;
		ptrb++;
	}

	// If sep not found return end
	return (*ptrb == '\0') ? ptra : str;
}

char *my_strdup(char *str, char *end) {
	char *temp = 0;
	int size = 0;

	while (str != end) {
		temp = realloc(temp, (size + 2) * sizeof(char));
		temp[size] = *str;
		temp[size+1] = '\0';

		size++;
		str++;
	}

	return temp;
}

/*
**
** QWASAR.IO -- my_split
**
** @param {char*} param_1
** @param {char*} param_2
**
** @return {string_array*}
**
*/

string_array* my_split(char* str, char* sep)
{
	string_array* temp = malloc(sizeof(string_array));
	int seplen = my_strtok(sep, sep) - sep;

	temp->array = 0;
	temp->size = 0;

	while (*str != '\0' && *sep != '\0') {
		temp->array = realloc(temp->array, (temp->size+1) * sizeof(char *));

		// Save the start point
		temp->array[temp->size] = str;

		// Move to the next token
		str = my_strtok(str, sep);

		// Adjust the previous token
		temp->array[temp->size] = my_strdup(
			temp->array[temp->size],
			// Remove the delimiter
			(*str == '\0') ? str : (str-seplen)
		);

		temp->size++;
	}

	return temp;
}

/*
int main() {
	string_array *data = my_split("abc def gh!", " ");

	for (int i = 0; i < data->size; i++) {
		printf("%s\n", data->array[i]);
		free(data->array[i]);
	}
	
	free(data->array);
	free(data);

	return 0;
}
*/
