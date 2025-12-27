/*
**
** QWASAR.IO -- my_iterative_factorial
**
** @param {int} param_1
**
** @return {int}
**
*/

int my_iterative_factorial(int n)
{
	int out = 1;

	for (int i = n; i > 1; i--) {
		out = out * i;
	}

	return out;
}
