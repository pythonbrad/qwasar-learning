/*
#include <stdio.h>
#include <stdlib.h>
*/

int my_isspace(char c) {
	return c == ' ' || c == '\t';
}

/*
**
** QWASAR.IO -- my_strip
**
** @param {char*} param_1
**
** @return {char*}
**
*/

char* my_strip(char* str)
{
	char *temp = malloc(sizeof(char));
	int size = 1;

    // Skip start spaces
    while (my_isspace(*str)) str++;

	while (*str != '\0') {
		// Not space, or not double space and no space at the end.
		if (!my_isspace(*str) || !my_isspace(*(str+1)) && *(str+1) != '\0') {
			temp = realloc(temp, (size+1) * sizeof(char));
			temp[size-1] = *str;
			temp[size] = '\0';

			size++;
		}

		str++;
	}

	return temp;
}

/*
int main() {
	printf("%s\n", my_strip(" this        time it      will     be    more complex  . "));

	return 0;
}*/

