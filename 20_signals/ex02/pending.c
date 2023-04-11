/* Write a program that shows that when the disposition of a pending signal is 
 * changed to be SIG_IGN, the program never sees (catches) the signal.
 */

/* Usage: 
 * ./pending.exe &
 * kill -s SIGUSR1 NNNN
 * Observe the program never handled SIGUSR1
 */

#define _GNU_SOURCE
#include <signal.h>
#include "signal_functions.h"
#include "tlpi_hdr.h"

static volatile sig_atomic_t sig_usr1_cnt = 0;

static void handler(int sig) {
	if (sig == SIGUSR1){
		sig_usr1_cnt = 1;
	}
}

int main() {
	// Create a signal set with SIGUSR1
	sigset_t block_set, pending_set;
	sigaddset(&block_set, SIGUSR1);

	// Set the disposition of SIGUSR1 to the handler
	struct sigaction sigusr1_action;
	sigusr1_action.sa_handler = handler;
	if(sigaction(SIGUSR1, &sigusr1_action, NULL) != 0){
		err_exit("sigaction");
	}

	// Add SIGUSR1 to the blocked signal mask
	if (sigprocmask(SIG_BLOCK, &block_set, NULL) != 0){
		err_exit("sigprocmask");         
	}

	// Print the list of pending signals (should not contain SIGUSR1)
	if (sigpending(&pending_set) != 0){
		err_exit("sigpending");
	}
	printf("The following signals are pending: ");
	printSigset(stdout, "\t\t", &pending_set);

	// Constantly check pending signals list for SIGUSR1
	while(true){
		if(sigpending(&pending_set) == -1){
			err_exit("sigpending");
		}
		if (sigisemptyset(&pending_set)){
			continue;
		} else {
			if(sigismember(&pending_set, SIGUSR1)) {
				break;
			}
		}
	}

	// Set the disposition of SIGUSR1 to SIG_IGN. Comment this out and verify 
	// that the number is 1, or leave it in and verify the number is 0
	sigusr1_action.sa_handler = SIG_IGN;
	if(sigaction(SIGUSR1, &sigusr1_action, NULL) != 0){
		err_exit("sigaction");
	}

	// Unblock the signal
	if (sigprocmask(SIG_UNBLOCK, &block_set, NULL) != 0){
		err_exit("sigprocmask");
	}

	// Print the list of pending signals (should not contain SIGUSR1)
	if (sigpending(&pending_set) != 0){
		err_exit("sigpending");
	}
	printf("The following signals are pending: ");
	printSigset(stdout, "\t\t", &pending_set);

	// Print the number of times the SIGUSR1 signal was caught (should be 0)
	printf("The number of times the SIGUSR1 was received is: %d\n", sig_usr1_cnt);

	return(EXIT_SUCCESS);
}