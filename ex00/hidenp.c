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
	while (*stra != '\0' && *strb != '\0') {
		if (*stra == *strb) {
			stra++;
		}

		strb++;
	}

	return *stra == '\0';
}