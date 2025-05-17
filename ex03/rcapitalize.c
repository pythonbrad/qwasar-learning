/*
#include <stdio.h>
#include <string.h>
*/

int is_end_of_word(char c) {
	return c == ' ' || c == '\t' || c == '\0';
}

int is_lower_letter(char c) {
	return c >= 'a' && c <= 'z';
}

int is_upper_letter(char c) {
	return c >= 'A' && c <= 'Z';
}

/*
**
** QWASAR.IO -- rcapitalize
**
** @param {char*} param_1
**
** @return {char*}
**
*/

char* rcapitalize(char *str)
{
	char *temp = strdup(str);
	char *ptr = temp;

	while (*ptr != '\0') {
		if (is_end_of_word(*(ptr+1))) {
			*ptr = is_lower_letter(*ptr) ? (*ptr-'a'+'A') : *ptr;
		} else {
			*ptr = is_upper_letter(*ptr) ? (*ptr-'A'+'a') : *ptr;
		}

		ptr++;
	}

	return temp;
}

/*
int main() {
	printf("%s\n", rcapitalize("   But... This iS not THAT COMPLEX"));
	return 0;
}
*/
