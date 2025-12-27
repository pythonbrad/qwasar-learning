// #define TEST

#ifdef TEST
#include <stdio.h>
#endif
/*
**
** QWASAR.IO -- my_iterative_pow
**
** @param {int} param_1
** @param {int} param_2
**
** @return {int}
**
*/

int my_iterative_pow(int n, int pow)
{
	int out = 1;

	if (n < 1) {
		return 0;
	} else if (n == 1) {
		return 1;
	}

	while (pow-- != 0) {
		out = out * n;
	}

	return out;
}

#ifdef TEST
int main() {
	printf("%i\n", my_iterative_pow(2, 4));

	return 0;
}
#endif
