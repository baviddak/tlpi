#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/shm.h>
#include <time.h>

int main( int argc, char *argv[] ) {
	

	if ( argc != 2 || strcmp(argv[1], "--help") == 0 ) {
		fprintf(stderr, "Usage: %s <shared_mem_id>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	struct shmid_ds smids;
	int shmid = atoi(argv[1]);

	if ( shmctl( shmid, SHM_STAT, (struct shmid_ds *)&smids) == -1 ) {
		fprintf(stderr, "Error in shmctl(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	printf("Key: %ld\n", (unsigned long) smids.shm_perm.__key);
	printf("Uid: %d\n", smids.shm_perm.uid);
	printf("Size (bytes): %d\n", smids.shm_segsz);
	printf("Last attach time: %s", ctime(&smids.shm_atime));
	printf("Creation time: %s", ctime(&smids.shm_ctime));

	exit(EXIT_SUCCESS);
}
