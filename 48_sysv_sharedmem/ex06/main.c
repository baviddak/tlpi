#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>

int main () {

	struct shminfo curr_info;
	struct shmid_ds smids;

	int id;
	int maxshmind = shmctl(0, SHM_INFO, (struct shmid_ds *)&curr_info);

	printf("key\t\tid\t\totime\t\tctime");

	for ( int i = 0; i <= maxshmind; i++ ) {
		id = shmctl(i, SHM_STAT, (struct shmid_ds *)&smids);

		if ( id == -1 ) {
			fprintf(stderr, "Error in shmctl(): %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		printf("%4d\t\t%8d\t\t%d\t\t%d\n", (unsigned long)smids.shm_perm.__key, id, smids.shm_ctime, smids.shm_atime);
	}

	exit(EXIT_SUCCESS);
}
