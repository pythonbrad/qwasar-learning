// #include <stdio.h>

/*
**
** QWASAR.IO -- remove_duplicates_from_sorted_list
**
** @param {listnode*} param_1
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


listnode* remove_duplicates_from_sorted_list(listnode* node)
{
	listnode *head = node;

	while (node->next != 0) {
		if (node->val == node->next->val) {
			*node = *node->next;
		} else {
			node = node->next;
		}
	}

	return head;
}

/*
int main() {
	listnode a, b, c, d;
	listnode *node;

	a.val = 1;
	b.val = 2;
	c.val = 2;
	d.val = 4;

	a.next = &b;
	b.next = &c;
	c.next = &d;

	node = remove_duplicates_from_sorted_list(&a);

	while (node != NULL) {
		printf("%d\n", node->val);
		node = node->next;
	}

	return 0;
}
*/
