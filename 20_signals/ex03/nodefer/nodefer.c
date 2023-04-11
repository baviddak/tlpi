/* Write programs that verify the effect of the SA_RESETHAND and SA_NODEFER 
 * flags when establishing a signal handler with sigaction().
 */

/* Usage: 
 * ./nodefer.exe &
 * kill -s SIGUSR1 NNNN
 * kill -s SIGUSR1 NNNN
 * Observe the program exits and prints the handler count
 */

#define _GNU_SOURCE
#include <signal.h>
#include "signal_functions.h"
#include "tlpi_hdr.h"

static volatile sig_atomic_t sig_usr1_cnt = 0;

/* This handler must be invoked twice, thereby incrementing the count to 2, in 
 * order for the program to exit. This can only happen if the SA_NODEFER flag is 
 * used in setting the disposition of the signal. 
 */
static void handler(int sig) {
	if (sig == SIGUSR1){
		sig_usr1_cnt++;
	}
	for(;;){
		if (sig_usr1_cnt > 1) {
			// Non-safe printf
			printf("Exiting the program, signal count is %d\n", sig_usr1_cnt);
			exit(0);
		}
		continue;
	}
}

int main() {
	// Set the disposition of the SIGUSR1 signal with the SA_NODEFER flag.
	struct sigaction sigusr1_action;
	sigusr1_action.sa_handler = handler;
	sigusr1_action.sa_flags = SA_NODEFER; 
	
	if(sigaction(SIGUSR1, &sigusr1_action, NULL) != 0){
		err_exit("sigaction");
	}

	// Wait some time to recieve the signal twice
	for(;;){
		continue;
	}

	printf("This point should never be reached!");
	return(EXIT_SUCCESS);
}