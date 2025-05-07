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
	bool reversed;

	for (int i=1; i<ptr->size; i++) {
		if (i == 1) {
			reversed = ptr->array[0] > ptr->array[1];
			max = ptr->array[0];
		}
		
		if (ptr->array[i-1] > ptr->array[i] != reversed || max > ptr->array[i] != reversed) {
			return false;
		}

		if (max < ptr->array[i] != reversed) {
			max = ptr->array[i];
		}
	}

	return true;
}
