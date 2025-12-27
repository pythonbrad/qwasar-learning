/*
**
** QWASAR.IO -- my_count_on_it
**
**
** @param {String[]} param_1
** @return {integer[]}

**
*/


function my_count_on_it(data) {
	var output = [];
	var index = 0;

	while (index < data.length) {
		output[index] = data[index].length;
		index++;
	}

	return output;
};
