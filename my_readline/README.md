# Welcome to My Readline
***

## Task
The task consisted to implement the `my_readline` function.
A function who read the stream one line at the time.

## Description

To solve this task, i wrote a code to read the stream, until i got an end of line `\n` or an `EOF`. The data are saved in a buffer of n-512 (by default). In case the initla block is full, it will be extended of an additional 512 bytes.

If the file is empty, it will return `NULL`.
Note that, the `\n` will be removed in the output.

## Installation

No installation is needed.

## Usage

```c
#include <stdio.h>

/* my_readline implementation */

int main() {
	int fd = open("/proc/cpuinfo", O_RDONLY);
	char *buf = NULL;

	while((buf = my_readline(fd)) != NULL) {
		printf("%s\n", buf);
		free(buf);
	}

	close(fd);

	return 0;
}
```

### The Core Team

Brady Fomegne


<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px' /></span>
