#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>

int main () {
	/* Create a set of shared memory segments */

	const char *filename = "file_a.txt";

	key_t key_a = ftok(filename, 1);
	key_t key_b = ftok(filename, 2);
	key_t key_c = ftok(filename, 3);

	int shmseg_a = shmget(key_a, 128, IPC_CREAT);
	int shmseg_b = shmget(key_b, 256, IPC_CREAT);
	int shmseg_c = shmget(key_c, 512, IPC_CREAT);

	if ( shmseg_a == -1 || shmseg_b == -1 || shmseg_c == -1 ) {
		fprintf(stderr, "Error in shmget(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	fprintf(stdout, "Successfully created some shared memory segments\n");
	return 0;
}
