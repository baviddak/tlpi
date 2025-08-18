/* 
 * Implement the siginterrupt() function described in Section 21.5 using 
 * sigaction().
 */

/* 
 * Usage:
 * 
 * ./my_siginterrupt.exe
 * In another terminal, send SIGUSR1 to the process (kill -s SIGUSR1 NNNN).
 * Observe that the read call is not interrupted, write some to the 
 * terminal and hit enter.
 */

#define _GNU_SOURCE
#define BUF_SIZE 20
#include <signal.h>
#include "signal_functions.h"
#include "tlpi_hdr.h"

/* If flag is true (1), then a handler for the signal sig will interrupt 
 * blocking system calls. If flag is false(0), then blocking system calls will 
 * be restarted after execution of a handler for sig.
 */
int my_siginterrupt(int sig, int flag) {

	// Get the current disposition of sig
	struct sigaction oldact;
	if (sigaction(sig, NULL, &oldact) == -1) {
		return -1;
	}

	// Set the new flags for the disposition	
	if (flag == 0) {
		oldact.sa_flags = oldact.sa_flags | SA_RESTART;
	} else if (flag == 1) {
		oldact.sa_flags = oldact.sa_flags & ~SA_RESTART;
	} else {
		return -1;
	}

	// Call sigaction() to update the disposition of the signal
	if (sigaction(sig, &oldact, NULL) == -1) {
		return -1;
	}
	
	return 0;
}

static void handler (int sig) {
	printf("Handler invoked\n"); // Un-safe print
}

int main() {

	// Print the PID 
	printf("PID: %ld\n", (long)getpid());
	fflush(stdout);
	
	// Set the disposition of SIGUSR1 to the handler
	struct sigaction sigusr1_action;
	sigusr1_action.sa_handler = handler;
	// sigusr1_action.sa_flags = SA_RESTART;
	if(sigaction(SIGUSR1, &sigusr1_action, NULL) != 0){
		err_exit("sigaction");
	}

	// Use my_siginterrupt to add or remove the SA_RESTART flag by setting 
	// interrupt_flags to 0 or 1
	int interrupt_flags = 0; 
	if (my_siginterrupt(SIGUSR1, interrupt_flags) == -1) {
		err_exit("my_siginterrupt");
	}

	// Read from STDIN (blocking system call)
	int num_read;
	char buf[BUF_SIZE];
	if ((num_read = read(STDIN_FILENO, buf, BUF_SIZE*sizeof(char))) > 0){
		printf("Read in %d bytes\n", num_read);
	}

	return(EXIT_SUCCESS);
}

