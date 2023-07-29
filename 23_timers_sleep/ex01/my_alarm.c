/* Although alarm() is implemented as a system call within the Linux kernel,
 * this is redundant. Implement alarm() using setitimer(). 
 */

/* Usage:
 * ./my_alarm.exe N (N is the number of seconds to wait in for the alarm, 20 max)
 * Observe that the program exists after N seconds.
 */

#include <signal.h>
#include <sys/time.h>
#include <time.h>
#include "tlpi_hdr.h"

unsigned int my_alarm(unsigned int seconds){
    int which = ITIMER_REAL;
    struct itimerval new_val;
    struct itimerval old_val;

    new_val.it_value.tv_sec = (time_t)seconds;
    new_val.it_value.tv_usec = 0;
    
    if (setitimer(which, &new_val, &old_val) == -1) {
        return 0;
    } else {
        return (unsigned int)old_val.it_value.tv_sec;
    }
}

int main(int argc, char * argv[]) {

    // Validate the command line args
    if(argc != 2 || strcmp(argv[1], "--help") == 0){
		usageErr("%s \narg count is %d\n", argv[0], argc);
	}

    int seconds = atoi(argv[1]);
    if ((seconds <= 0) || seconds > 20) {
        errExit("atoi");
    }

    my_alarm(seconds);

    int prev_clock = clock();

    while(1){
        if ((clock() - prev_clock) / CLOCKS_PER_SEC > 1){
            printf("\nStill running...");
            prev_clock = clock();
        }
    }
}
