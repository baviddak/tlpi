/* Write programs that verify the effect of the SA_RESETHAND and SA_NODEFER 
 * flags when establishing a signal handler with sigaction().
 */

/* Usage: 
 * ./resethand.exe &
 * kill -s SIGABRT NNNN
 * Observe nothing happens
 * kill -s SIGABRT NNNN
 * Observe the program aborts
 */

#define _GNU_SOURCE
#include <signal.h>
#include "signal_functions.h"
#include "tlpi_hdr.h"

static volatile sig_atomic_t sig_usr1_cnt = 0;

/* This handler will be called once, in place of the default action of the 
 * SIGABRT default action, which is to abort the process. The next time the 
 * signal is recieved, it will abort. In this way, we can prove the 
 * effectiveness of setting the SA_RESETHAND flag in the sigaction() call.
 */
static void handler(int sig) {
	if (sig == SIGABRT){
		sig_usr1_cnt++;
	}
	return;
}

int main() {
	// Set the disposition of the SIGABRT signal with the SA_RESETHAND flag.
	struct sigaction sigusr1_action;
	sigusr1_action.sa_handler = handler;
	sigusr1_action.sa_flags = SA_RESETHAND; 
	
	if(sigaction(SIGABRT, &sigusr1_action, NULL) != 0){
		err_exit("sigaction");
	}

	// Wait some time to recieve the signal twice
	for(;;){
		continue;
	}

	printf("This point should never be reached!");
	return(EXIT_SUCCESS);
}