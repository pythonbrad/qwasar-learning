/*
**
** QWASAR.IO -- my_map_mult_two
**
**
** @param {Integer[]} param_1
** @return {integer[]}

**
*/


function my_map_mult_two(data) {
	var index = 0;

	while (index < data.length) {
		data[index] = data[index] * 2;
		index++;
	}

	return data;
};
