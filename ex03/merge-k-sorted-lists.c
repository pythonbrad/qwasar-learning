/*
#include <stdio.h>
#include <stdlib.h>
*/

/*
**
** QWASAR.IO -- merge_k_sorted_lists
**
** @param {listnode_array*} param_1
**
** @return {listnode*}
**
*/
#ifndef STRUCT_LISTNODE
#define STRUCT_LISTNODE
typedef struct s_listnode
{
    int val;
    struct s_listnode* next;
} listnode;
#endif

#ifndef STRUCT_LISTNODE_ARRAY
#define STRUCT_LISTNODE_ARRAY
typedef struct s_listnode_array
{
    int size;
    listnode **array;
} listnode_array;
#endif


listnode* merge_k_sorted_lists(listnode_array *data)
{
	listnode* state[data->size];
	
	listnode temp;
	listnode* temp_tail = &temp;
	
	int pivot;
	int* min;

	// Configure listnode state
	for (int i = 0; i < data->size; i++) {
		state[i] = data->array[i];
	}

	while (1) {
		pivot = -1;
		min = 0;
		
		// Determine the new min
		for (int i = 0; i < data->size; i++) {
			if (state[i] != 0 && (min == 0 || state[i]->val <= *min)) {
				min = &state[i]->val;
				pivot = i;
			}
		}

		if (pivot == -1) break;

		// printf("%d\n", *min);

		// Construct new listnodes
		temp_tail->next = malloc(sizeof(listnode));
		temp_tail = temp_tail->next;
		temp_tail->val = state[pivot]->val;
		temp_tail->next = 0;

		// Move the pivot state
		state[pivot] = state[pivot]->next;
	}

	return temp.next;
}

/*
int main() {
	listnode a1, a2, a3, b1, b2, b3, c1, c2;
	listnode_array data;
	listnode* out;

	// Node
	a1.val = 1;
	a1.next = &a2;
	a2.val = 4;
	a2.next = &a3;
	a3.val = 5;

	b1.val = 1;
	b1.next = &b2;
	b2.val = 3;
	b2.next = &b3;
	b3.val = 4;

	c1.val = 2;
	c1.next = &c2;
	c2.val = 6;

	// Data
	data.size = 3;
	data.array = malloc(data.size * sizeof(listnode));

	*(data.array) = &a1;
	*(data.array+1) = &b1;
	*(data.array+2) = &c1;

	//
	out = merge_k_sorted_lists(&data);

	for (listnode* tail = out; tail != 0; tail = tail->next) {
		printf("%d\n", tail->val);
	}

	return 0;
}
*/
