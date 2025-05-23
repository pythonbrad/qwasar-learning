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
** Print a chrismas tree.
**
** @param {int} fwidth: the full width of the tree
** @param {int} width: the width of the tree
** @param {int} height: the height of the tree
**
** @return {void}
**
*/
void print_tree(int fwidth, int width, int height) {
	printf("fw:%d w:%d h:%d\n", fwidth, width, height);

	for (int j = width-(height-1)*2; j <= width; j+=2) {
		printf("%03d: ", j);

		for (int i = 0; i < (fwidth-j) / 2; i++) {
			printf(" ");
		}

		for (int i = 0; i < j; i++) {
			printf("*");
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
	int size = 0, width = 0, height = 0, step = 0;;

	if (argc < 2) return 0;

	size = atoi(argv[1]);
	width = 1;
	step = 3;

	for (int i = 0; i < size; i++) {
		if (i != 0 && i % 2 == 0) step++;

		width += step * 2;
		height = 4 + i;

		print_tree(101, width, height);
	}

	return 0;
}
