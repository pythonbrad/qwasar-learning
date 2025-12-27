/*
**
** QWASAR.IO -- my_fibonacci
**
** @param {int} param_1
**
** @return {int}
**
*/

int my_fibonacci(int n)
{
	if (n < 1) return -1;
	if (n == 1 || n == 2) return 1;

	return my_fibonacci(n-1) + my_fibonacci(n-2);
}
