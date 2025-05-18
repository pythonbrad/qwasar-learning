/*
#include <stdio.h>
*/

/*
**
** QWASAR.IO -- hidenp
**
** @param {char*} param_1
** @param {char*} param_2
**
** @return {int}
**
*/

int hidenp(char *stra, char *strb)
{
	char *ptra = stra;
	char *ptrb = strb;

	while (*ptra != '\0' && *ptrb != '\0') {
		// printf("%s %s\n", ptra, ptrb);
		if (*ptra != *ptrb) {
			ptra = stra;
			ptrb = ++strb;

			continue;
		}

		ptra++;
		ptrb++;
	}

	return *ptra == '\0';
}

/*
int main() {
	printf("%d\n", hidenp("abc", "ababababaabbacabababbc"));

	return 0;
}
*/
