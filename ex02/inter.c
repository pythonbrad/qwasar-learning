/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
*/

/*
**
** QWASAR.IO -- inter
**
** @param {char*} param_1
** @param {char*} param_2
**
** @return {char*}
**
*/

char* inter(char* str_a, char* str_b)
{
	char* temp = malloc(sizeof(char));
	int length = 0;

	*temp = '\0';
	
	while (*str_a != '\0') {
		if (strchr(str_b, *str_a) != NULL) {
			temp = realloc(temp, (length+2) * sizeof(char));
			temp[length] = *str_a;
			temp[length+1] = '\0';

			length++;
		}

		str_a++;
	}

	return temp;
}

/*
int main() {
	printf("%s\n", inter("padinton", "paqefwtdjetyiytjneytjoeyjnejeyj"));

	return 0;
}
*/
