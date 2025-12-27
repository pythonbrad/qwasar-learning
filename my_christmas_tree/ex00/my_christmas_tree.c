#include <stdio.h>
#include <stdlib.h>

/*
** Print a chrismas tree.
**
** @param {int} fwidth: the width of the plan
** @param {int} width: the width of the tree
** @param {int} height: the height of the tree
**
** @return {void}
**
*/
void print_tree(int fwidth, int width, int height) {
	// printf("fw:%d w:%d h:%d\n", fwidth, width, height);

	// Determine the tree growing
	for (int w = width-(height-1)*2; w <= width; w+=2) {
		// printf("%03d: ", w);

		// Adjustment to have the tree at the middle of the plan
		for (int i = 0; i < (fwidth-w) / 2; i++) {
			printf(" ");
		}

		for (int i = 0; i < w; i++) {
			printf("*");
		}

		printf("\n");
	}
}
/*
** Print foot of a chrismas tree.
**
** @param {int} width: the width of the tree
** @param {int} size: size of the tree
**
** @return {void}
**
*/
void print_tree_foot(int width, int size) {
	for (int j = 0; j < size; j++) {
		for (int i = 0; i <= (width - 1 - size) / 2; i++) {
			printf(" ");
		}

		for (int i = 0; i < size; i++) {
			printf("|");
		}

		printf("\n");
	}
}

/*
** Return the width of the nth subtree.
**
** @param {int} size
**
** @return {int}
**
*/
int tree_width(int nth) {
	int width = 1, step = 3;

	for (int i = 0; i < nth; i++) {
		if (i != 0 && i % 2 == 0) step++;

		width += step * 2;
	}

	return width;
}

int main(int argc, char **argv) {
	int size = 0, fwidth = 0, width = 0, height = 0;

	if (argc < 2) return 0;

	size = atoi(argv[1]);
	fwidth = tree_width(size);

	for (int i = 0; i < size; i++) {
		height = 4 + i;
		width = tree_width(i+1);

		print_tree(fwidth, width, height);
	}

	print_tree_foot(fwidth, size);

	return 0;
}
