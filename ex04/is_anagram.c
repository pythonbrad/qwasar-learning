/*
#include <stdio.h>
*/

/*
**
** QWASAR.IO -- is_anagram
**
** @param {char*} param_1
** @param {char*} param_2
**
** @return {int}
**
*/

int is_anagram(char* str_a, char* str_b)
{
	char diff;

	while (*str_a != '\0' || *str_b != '\0') {
		diff = diff + *str_a++ - *str_b++;
	}

	return diff == 0;
}

/*
int main() {
	printf("%d\n", is_anagram("abcdef", "fabcde"));

	return 0;
}
*/
