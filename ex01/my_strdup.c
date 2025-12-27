/*
#include <stdio.h>
#include <stdlib.h>
*/

char* my_strdup(char* input)
{
	int i = 0;
	char* output = calloc(0, sizeof(char));

	while (input[i] != '\0') {
		output = realloc(output, (i+2) * sizeof(char));
		output[i] = input[i];

		i++;
	}

	output[i] = '\0';

	return output;
}

/*
int main() {
	printf("%s\n", my_strdup("Hello"));
	return 0;
}
*/
