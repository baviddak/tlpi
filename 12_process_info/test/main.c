#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define MAX_PATH 128
#define MAX_BUFF 2048

#define PATHSTR "/proc/%ld/status"

int main (int argc, char *argv[]) {

	int status_fd;
	pid_t pid = getpid();
	char path[MAX_PATH];
	int flags = O_RDONLY;
	char buf[MAX_BUFF];
	memset(buf, 0, sizeof(buf));

	// char * heap_buf = (char *)malloc(4096);

	/* fprintf(stdout, "The size of the buffer is %ld\n", sizeof(path)); */
	memset(path, 0, sizeof(path));
	snprintf(path, sizeof(path) - 1, PATHSTR, (long) pid);

	if ((status_fd = open(path, flags)) < 0) {
		fprintf(stderr, "Error opening the status file.\n");
		exit(EXIT_FAILURE);
	}

	if (read(status_fd, buf, sizeof(buf) - 1 ) < 0) {
		fprintf(stderr, "Error in reading from status file.\n");
		exit(EXIT_FAILURE);
	}

	if (write(STDOUT_FILENO, buf, sizeof(buf)) < 0) {
		fprintf(stderr, "Error printing to standard out.\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
