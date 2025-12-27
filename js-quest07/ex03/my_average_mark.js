/*
**
** QWASAR.IO -- my_average_mark
**
**
** @param {String_integer[]} param_1
** @return {float}

**
*/


function my_average_mark(data) {
	var index = 0;
	var output = 0;

	while (index < data.length) {
		output = output + data[index]["integer"] / data.length;
		index++;
	}

	return output.toFixed(1);
};
