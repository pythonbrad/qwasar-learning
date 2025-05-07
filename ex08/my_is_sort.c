/*
**
** QWASAR.IO -- my_is_sort
**
** @param {integer_array*} param_1
**
** @return {bool}
**
*/
#include <stdbool.h>
#ifndef STRUCT_INTEGER_ARRAY
#define STRUCT_INTEGER_ARRAY
typedef struct s_integer_array
{
    int size;
    int* array;
} integer_array;
#endif


bool my_is_sort(integer_array* ptr)
{
	int max;

	for (int i=1; i<ptr->size; i++) {
		if (i == 1 || max < ptr->array[i]) {
			max = ptr->array[i];
		}

		if (ptr->array[i-1] > ptr->array[i] || max > ptr->array[i]) {
			return false;
		}
	}

	return true;
}
