/* Write a program ... that uses the semctl() SEM_INFO and SEM_STAT operations 
 * to obtain and display a list of all semaphore sets on the system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/sem.h>

int main () {

	int curr_semid;
	
	struct semid_ds sidds;
	struct seminfo sinfo;

	int maxsemid = semctl(0, 0, SEM_INFO, (struct seminfo *)&sinfo);

	if ( maxsemid == -1 ) {
		fprintf(stderr, "Error in semctl(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* fprintf(stdout, "The index of the highest used entry in the kernel's internal array is %d\n", maxsemid);
	fprintf(stdout, "The number of semaphore sets on the system is %d\n", sinfo.semusz);
	fprintf(stdout, "The number of semaphores on the system is %d\n", sinfo.semaem); */

	printf("maxind: %d\n\n", maxsemid);
	printf("index\tkey\toptime\tctime\tnsems\n\n");

	for (int i = 0; i <= maxsemid; i++ ) {
		
		curr_semid = semctl(i, 0, SEM_STAT, (struct semid_ds *)&sidds);
		if ( curr_semid == -1 ) {
			fprintf(stderr, "Error in semctl(): %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		printf("%4d\t0x%08lx\t%d\t%d\t%ld\n", curr_semid, (unsigned long) sidds.sem_perm.__key, sidds.sem_otime, sidds.sem_ctime, sidds.sem_nsems);
	}

	return 0;
}
