/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
*/


int unique_insert(char **dest, char *str, int length) {
	while (*str != '\0') {
		if (strchr(*dest, *str) == 0) {
			*dest = realloc(*dest, (length+2) * sizeof(char));
			(*dest)[length] = *str;
			(*dest)[length+1] = '\0';

			length++;
		}

		str++;
	}

	return length;
}

/*
**
** QWASAR.IO -- my_union
**
** @param {char*} param_1
** @param {char*} param_2
**
** @return {char*}
**
*/

char* my_union(char* str_a, char* str_b)
{
	char* temp = malloc(sizeof(char));
	int length = 0;

	*temp = '\0';

	length = unique_insert(&temp, str_a, length);
	length = unique_insert(&temp, str_b, length);

	return temp;
}

/*
int main(int argc, char **argv) {
	printf("%s\n", my_union("zpadinton", "paqefwtdjetyiytjneytjoeyjnejeyj"));

	return 0;
}
*/
