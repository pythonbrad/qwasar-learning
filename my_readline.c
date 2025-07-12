#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

// Max line of data to read.
int READLINE_READ_SIZE = 512;

// Copy the content from string to another.
//
// The destination should have a size greater than the source.
char* my_strcpy(char *dest, char *src) {
	int i = -1;

	if (src == NULL) return dest;

	while (src[++i] != '\0') {
		dest[i] = src[i];
	}

	return dest;
}

// Allocate a new memory and move the content of the previous.
char* my_realloc(char *ptr, int new_size) {
	char *temp = malloc(new_size * sizeof(char));

	temp = my_strcpy(temp, ptr);
	free(ptr);

	return temp;
}

// Readline the stream line per line.
char* my_readline(int fd) {
	int i = 0;
	char *buf = malloc(READLINE_READ_SIZE * sizeof(char));

	while (read(fd, buf+i, 1) > 0) {
		// Detect new line.
		if (buf[i++] == '\n') break;

		// Prevent overflow.
		if (i % (READLINE_READ_SIZE - 1) != 0) continue;

		// Add a null terminator for the memory reallocation.
		buf[i] = '\0';
		buf = my_realloc(buf, i + READLINE_READ_SIZE);
	}

	// Detect error or empty file.
	if (i == 0) {
		free(buf);

		return NULL;
	}

	// If line detected, remove the carrier return.
	if (buf[i-1] == '\n') buf[i-1] = '\0';

	return buf;
}
