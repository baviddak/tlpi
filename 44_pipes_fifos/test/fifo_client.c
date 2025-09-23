// Make sure to start the Server program first, which will initialize the 
// FIFO.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define BUFFER_MAX 128

int main() {

	char *fifo_file = "/tmp/test_fifo_02";
	int perms = S_IRUSR | S_IWUSR | S_IRGRP;


	int fd = open(fifo_file, O_WRONLY);

	char buffer[BUFFER_MAX];

	snprintf(buffer, BUFFER_MAX, "This is some random text yall!!!");

	if (fd == -1){
		fprintf(stderr, "Error opening the FIFO in the writer\n");
		fprintf(stderr, "%s\n", strerror(errno));
		return -1;
	}

	int num_written = write(fd, buffer, BUFFER_MAX);


	return 0;
}
