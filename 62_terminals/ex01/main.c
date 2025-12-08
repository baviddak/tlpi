/* Implement isatty(). */

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

int my_isatty (int fd) {

	struct termios tp;

	if ((tcgetattr(fd, &tp) == -1) && errno == ENOTTY) {
		return 0;
	} else {
		return 1;
	}

}

int main (int argc, char *argv[]) {

	/* Basic args check */
	if (argc != 2 || strcmp(argv[1], "--help") == 0) {
		fprintf(stderr, "Usage: ./my_isatty <filename>\n");
		exit(EXIT_FAILURE);
	}

	/* Get a file descriptor */
	int flags = O_RDWR;
	const char *filename = argv[1];
	int fd = open(filename, flags);

	/* Test with our function */
	int result = my_isatty(fd);
	if (result) {
		fprintf(stdout, "This is a terminal device.\n");
	} else {
		fprintf(stdout, "This is not a terminal device.\n");
	}

	return 0;
}
