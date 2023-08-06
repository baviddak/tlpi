/* Write a program to show that if the evp argument to timer_create() is 
 * specified as NULL, then this is equivalent to specifying evp as a pointer to 
 * a sigevent structure with sigev_notify set to SIGEV_SIGNAL, sigev_signo set 
 * to SIGALRM, and si_value.sival_int set to the timer ID.
 */

/* Usage: ./null_evp.exe N
 * Verify that the SIGALRM signal is recieved after N seconds
 */

#define _POSIX_C_SOURCE 199309
#include <signal.h>
#include <time.h>
#include "tlpi_hdr.h"

int main (int argc, char * argv[]) {

	// Validate the command line args
	if(argc != 2 || strcmp(argv[1], "--help") == 0){
		usageErr("%s \narg count is %d\n", argv[0], argc);
	}

	int seconds = atoi(argv[1]);
	if ((seconds <= 0) || seconds > 20) {
		errExit("atoi");
	}

	timer_t my_timer;
	int timer_flags = 0;

	struct itimerspec my_timeval;
	my_timeval.it_interval.tv_nsec = 0;
	my_timeval.it_interval.tv_sec = 0;
	my_timeval.it_value.tv_sec = seconds;

	// Setup a timer with the timer_create() call, with NULL as the evp arg
	if (timer_create(CLOCK_REALTIME, NULL, &my_timer) == -1) {
		errExit("timer_create");
	}

	// Arm the timer
	if (timer_settime(my_timer, timer_flags, &my_timeval, NULL) == -1) {
		errExit("timer_settime");
	}

	// Loop until the SIGALRM signal is recieved
	int prev_clock = clock();
	while(1){
		if (clock() - prev_clock  > CLOCKS_PER_SEC){
			printf("\nStill running...");
			prev_clock = clock();
		}
	}

	return 0;
}
