/*
**
** QWASAR.IO -- my_recursive_pow
**
** @param {int} param_1
** @param {int} param_2
**
** @return {int}
**
*/

int my_recursive_pow(int n, int p)
{
	if (n < 1) return 0;

	if (p == 0) return 1;

	return n * my_recursive_pow(n, p-1);
}
