/*
**
** QWASAR.IO -- my_first_struct
**
** @param {integer_array*} param_1
**
** @return {void}
**
*/
#ifndef STRUCT_INTEGER_ARRAY
#define STRUCT_INTEGER_ARRAY
typedef struct s_integer_array
{
    int size;
    int* array;
} integer_array;
#endif


void my_first_struct(integer_array* ptr)
{
	printf("%d\n", ptr->size);

	for(int i=0; i < ptr->size; i++) {
		printf("%d\n", ptr->array[i]);
	}

}
