/*
**
** QWASAR.IO -- my_array_uniq
**
**
** @param {Integer[]} param_1
** @return {integer[]}

**
*/


function my_array_uniq(data) {
	var x = 0;
	var output = [];

	while (x < data.length) {
		if (!output.includes(data[x])) {
			output.push(data[x]);
		}

		x++;
	}

	return output;
};
