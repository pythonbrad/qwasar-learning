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
void print_tree(int width, int start, int end) {
	int middle = width / 2;

	printf("w:%d s:%d e:%d\n", width, start, end);

	for (int j = start; j < end; j++) {
		for (int i = 0; i <= middle * 2; i++) {
			if (i < middle - j) {
				printf(" ");
			} else if (i > middle + j) {
				// pass
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
	int size = 0, width = 0, start = 0, end = 0, step = 0;;

	if (argc < 2) return 0;

	size = atoi(argv[1]);
	width = 1;
	step = 3;

	for (int i = 0; i < size; i++) {
		if (i != 0 && i % 2 == 0) step++;

		width += step * 2;
		start += pascal(i);
		end = start + 4 + i;

		print_tree(width, start, end);
	}

	return 0;
}
