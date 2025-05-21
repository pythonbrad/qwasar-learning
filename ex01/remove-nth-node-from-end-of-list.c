// #include <stdio.h>

#ifndef STRUCT_LISTNODE
#define STRUCT_LISTNODE
typedef struct s_listnode
{
    int val;
    struct s_listnode* next;
} listnode;
#endif

listnode* reverse_linked_list(listnode *node) {
	listnode* parent = 0;
	listnode* child;

	while ((child = node->next) != 0) {
		node->next = parent;
		parent = node;
		node = child;
	}

	node->next = parent;

	return node;
}

/*
**
** QWASAR.IO -- remove_nth_node_from_end_of_list
**
** @param {listnode*} param_1
** @param {int} param_2
**
** @return {listnode*}
**
*/

listnode* remove_nth_node_from_end_of_list(listnode* node, int n)
{
	listnode *head = reverse_linked_list(node);
	node = head;

	// Move to the node
	for (int i = 0; i < n-1; i++) {
		node = node->next;
	}

	// printf("--%d--\n", node->val);

	if (n == 1) {
		*head = *head->next;
	}

	head = reverse_linked_list(head);

	if (n > 1) {
		*node = *node->next;
	}

	return head;
}

/*
int main() {
	listnode a, b, c, d;
	listnode *node = &a;

	a.val = 1;
	a.next = &b;
	b.val = 2;
	b.next = &c;
	c.val = 3;
	c.next = &d;
	d.val = 4;

	remove_nth_node_from_end_of_list(&a, 1);

	while (node != 0) {
		printf("%d\n", node->val);

		node = node->next;
	}

	return 0;
}
*/
