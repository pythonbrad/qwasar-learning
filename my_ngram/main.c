#include <stdio.h>
#include <stdlib.h>

struct ngram_item {
	int occ;
	char c;
};

struct ngram {
	struct ngram_item* items;
	int size;
};

int main(int argc, char** argv) {
	struct ngram ng;
	char* str;
	int item_idx = 0;
	struct ngram_item temp_ngram_item;

	ng.size = 0;
	ng.items = NULL;

	// Evaluation
	for (int arg_idx = 1; arg_idx < argc; arg_idx++) {
		str = argv[arg_idx];

		while (*str != '\0') {
			for (item_idx = 0; item_idx < ng.size; item_idx++) {
				if (ng.items[item_idx].c != *str) continue;

				ng.items[item_idx].occ++;
				break;
			}

			if (item_idx == ng.size) {
				ng.items = realloc(ng.items, (ng.size+1) * sizeof(struct ngram_item));
				ng.items[ng.size].c = *str;
				ng.items[ng.size].occ = 1;

				ng.size++;
			}

			str++;
		}
	}

	// Sort
	for (int i = 0; i < ng.size; i++) {
		for (int j = 0; j < ng.size; j++) {
			if (ng.items[i].c > ng.items[j].c) continue;

			temp_ngram_item = ng.items[j];
			ng.items[j] = ng.items[i];
			ng.items[i] = temp_ngram_item;
		}
	}

	// Display
	for (item_idx = 0; item_idx < ng.size; item_idx++) {
		printf("%c:%d\n", ng.items[item_idx].c, ng.items[item_idx].occ);
	}

	free(ng.items);

	return 0;
}
