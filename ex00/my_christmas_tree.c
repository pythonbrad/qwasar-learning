#include <stdio.h>
#include <stdlib.h>

/*
** Return the factorial of n.
**
** @param {int}
**
** @return {int}
**
*/
int fact(int n) {
	int out = 1;

	for (int i = 0; i < n; i++) {
		out = out * (n - i);
	};

	return out;
}

/*
** Return the nth value of the pascal table.
**
** @param {int} middle: the middle position of the tree
** @param {int} start: the number of row to skip
** @param {int} end: the last row of the tree
**
** @return {void}
**
*/
void print_tree(int middle, int start, int end) {
	// printf("m:%d s:%d e:%d\n", middle, start, end);

	for (int j = start; j < start+end; j++) {
		for (int i = 1; i <= middle * 2; i++) {
			if (i < middle - j || i > middle + j) {
				printf(" ");
			} else {
				printf("*");
			}
		}

		printf("\n");
	}
}

/*
** Return the nth value of the pascal table.
**
** @param {int} n
**
** @return {int}
**
*/
int pascal(int n) {
	int i = 0, j = 0;

	if (n == 0) return 0;

	// Go to the nth position
	for (j = 2; n > 0; j++) {
		for (i = 1; i <= j - 1 && n > 0; i++) {
			n--;
		}
	}

	j--;
	i--;

	// printf("C(%d, %d)\n", j, i);

	return fact(j) / (fact(i) * fact(j-i));
}

int main(int argc, char **argv) {
	int size = 0, middle = 0, start = 0, end = 0;

	if (argc < 2) return 0;

	size = atoi(argv[1]);
	middle = size * 4;

	for (int i = 0; i < size; i++) {
		start += pascal(i);
		end = 4 + i;

		print_tree(middle, start, end);
	}

	return 0;
}
