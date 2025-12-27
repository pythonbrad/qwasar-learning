/*
**
** QWASAR.IO -- my_recursive_factorial
**
** @param {int} param_1
**
** @return {int}
**
*/

int my_recursive_factorial(int n)
{
	if (n < 2) return 1;

	return n * my_recursive_factorial(n-1);
}
