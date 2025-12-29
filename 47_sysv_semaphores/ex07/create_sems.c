#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#define KEYFILE "keyfile"

int main () {

	key_t sem_key = ftok(KEYFILE, 333);
	mode_t new_mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;

	int sem_a = semget(sem_key, 4, IPC_CREAT | new_mode);

	if ( sem_a == -1 ) {
		fprintf(stderr, "Error in semget(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	fprintf(stdout, "Successfully created some semaphores\n");


	int sem_b = semget(IPC_PRIVATE, 2, 0);

	if ( sem_b == -1 ) {
		fprintf(stderr, "Error in semget(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	return 0;
}
