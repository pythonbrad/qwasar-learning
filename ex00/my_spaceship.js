var path = process.argv[2] ?? '';

var direction = 'up';
var index = 0;
var x = 0;
var y = 0;

while (index < path.length) {
	if (path[index] == 'L') {
		if (direction == 'up') {
			direction = 'left'
		} else if (direction == 'left') {
			direction = 'down';
		} else if (direction == 'down') {
			direction = 'right';
		} else if (direction == 'right') {
			direction = 'up';
		}
	} else if (path[index] == 'R') {
		if (direction == 'up') {
			direction = 'right'
		} else if (direction == 'right') {
			direction = 'down';
		} else if (direction == 'down') {
			direction = 'left';
		} else if (direction == 'left') {
			direction = 'up';
		}
	} else if (path[index] == 'A') {
		if (direction == 'up') {
			y = y - 1;
		} else if (direction == 'left') {
			x = x - 1;
		} else if (direction == 'down') {
			y = y + 1;
		} else if (direction == 'right') {
			x = x + 1;
		}
	}

	console.log(x, y, direction, index, path[index])
	index++;
}

console.log("{x: "+x+", y: "+y+", direction: '"+direction+"'}");
