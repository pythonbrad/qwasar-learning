/*
**
** QWASAR.IO -- my_atoi
**
** @param {char*} param_1
**
** @return {int}
**
*/

int my_atoi(char* strn)
{
	int out = 0;
	int sign = 1;

	// Determine the sign
	if (*strn == '-') {
		sign = -1;
		strn++;
	} else if (*strn == '+') {
		sign = 1;
		strn++;
	}

	while(*strn != '\0') {
		if (*strn < '0' || *strn > '9') return 0;

		out = out * 10 + 9 - ('9' - *strn);
		strn++;
	}

	return sign * out;
}
