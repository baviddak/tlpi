/* 
 * This is a helper program to assist in testing out my popen 
 * implementation. This program reads from it's stdin and writes
 * to a specific file? 
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUFFER_MAX 128

int main () {

	int flags = O_RDWR | O_APPEND | O_CREAT;
	int perms = S_IRUSR | S_IWUSR;

	int fd = open("reader_output.txt", flags, perms);

	size_t num_read;
	ssize_t num_written;
	char buffer[BUFFER_MAX];

	while (1) {
		num_read = fread(buffer, sizeof(char), BUFFER_MAX, stdin);

		if (num_read <= 0) {
			fprintf(stderr, "%s\n", strerror(errno));
			break;
		}

		num_written = write(fd, buffer, strlen(buffer));

		if (num_written <= 0) {
			fprintf(stderr, "%s\n", strerror(errno));
			break;
		}

	}

	return 0;
}
