// Simple single-client FIFO application.
//
// The 'server' reads from the FIFO and prints out the message 
// to stdout.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE 128

int main() {

	char *server_fifo_file = "/tmp/test_fifo_02";
	int perms = S_IRUSR | S_IWUSR | S_IWGRP;
	char buffer[BUFFER_SIZE];

	if (mkfifo(server_fifo_file, perms) != 0) {
		fprintf(stderr, "Error creating the FIFO in the reader.\n");
		fprintf(stderr, "%s\n", strerror(errno));
		return -1;
	}

	int server_fd = open(server_fifo_file, O_RDONLY);

	if (server_fd == -1) {
		fprintf(stderr, "Error opening FIFO file in the reader.\n");
		fprintf(stderr, "%s\n", strerror(errno));
		return -1;
	}


	int num_read;
	while(1) {
		num_read = read(server_fd, buffer, BUFFER_SIZE);

		if (num_read <= 0) {
			break;
		}
	}

	int num_written = write(STDOUT_FILENO, buffer, BUFFER_SIZE);
	if (num_written < 0){
		fprintf(stderr, "Error writing to STDOUT_FILENO\n");
		return -1;
	}

	close(server_fd);
	return 0;
}
