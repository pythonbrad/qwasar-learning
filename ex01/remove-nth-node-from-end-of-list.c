/*
#include <stdio.h>
*/

#ifndef STRUCT_LISTNODE
#define STRUCT_LISTNODE
typedef struct s_listnode
{
    int val;
    struct s_listnode* next;
} listnode;
#endif

listnode* reverse_linked_list(listnode *node) {
	listnode* parent = NULL;
	listnode* child;

	while ((child = node->next) != NULL) {
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

	for (int i = 0; i < n; i++) {
		node = node->next;
		i++;
	}

	head = reverse_linked_list(head);

	if (n > 0) {
		*node = *(node->next);
	}

	return head;
}

/*
int main() {
	listnode a, b, c, d;

	a.val = 1;
	a.next = &b;
	b.val = 2;
	b.next = &c;
	c.val = 3;
	c.next = &d;
	d.val = 4;

	remove_nth_node_from_end_of_list(&a, 1);

	printf("a:%p b:%p c: %p d: %p\n", &a, &b, &c, &d);
	printf("%p %p %p %p\n", &a, a.next, a.next->next, a.next->next->next);
	printf("%d %d %d %d\n", a.val, a.next->val, a.next->next->val, 0);

	return 0;
}
*/
