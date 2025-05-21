// #include <stdio.h>

/*
**
** QWASAR.IO -- reverse_linked_list
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


listnode* reverse_linked_list(listnode* node)
{
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
int main() {
	listnode a, b, c;

	a.val = 1;
	a.next = &b;
	b.val = 2;
	b.next = &c;
	c.val = 3;

	reverse_linked_list(&a);

	printf("a:%p b:%p c: %p\n", a.next, b.next, c.next);
	printf("a:%p b:%p c: %p\n", &a, &b, &c);

	return 0;
}
*/
