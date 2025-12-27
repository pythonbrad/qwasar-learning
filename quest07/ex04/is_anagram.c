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
	// ASCII: 32 -> 126
	int freq[94] = {0};

	while (*str_a != '\0' || *str_b != '\0') {
		freq[*str_a - 32]++;
		freq[*str_b - 32]++;

		str_a++;
		str_b++;
	}

	// Check the parity
	for (int i = 0; i < 94; i++) {
		if (freq[i] % 2) return 0;
	}

	return 1;
}

/*
int main() {
	printf("%d\n", is_anagram("ad", "bc"));

	return 0;
}
*/
