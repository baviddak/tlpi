/* Implement abort(). */

/* Usage: ./my_abort.exe */

#define _GNU_SOURCE
#include <signal.h>
#include "tlpi_hdr.h"

void my_abort() {

	// Abort signal set and action
	sigset_t abrt_set;
	struct sigaction abrt_act;

	// Override blocking of SIGABRT (remove from the block mask)
	if (sigemptyset(&abrt_set) == -1) {
		err_exit("sigemptyset");
	}
	if (sigaddset(&abrt_set, SIGABRT) == -1) {
		err_exit("sigaddset");
	}
	if (sigprocmask(SIG_UNBLOCK, &abrt_set, NULL) == -1) {
		err_exit("sigprocmask");
	}

	// Raise the SIGABRT (at this point the program should terminate)
	raise(SIGABRT);

	// Reset the handling of SIGABRT to SIG_DFL to guarantee termination
	abrt_act.sa_handler = SIG_DFL;
	if (sigaction(SIGABRT, &abrt_act, NULL) == -1) {
		err_exit("sigaction");
	}

	// Raise another SIGABRT
	raise(SIGABRT);
}

static void handler(int sig) {
	// do something trivial and return
	printf("Handler called\n"); // Un-safe printf
}

int main() {

	// Set the disposition of the SIGABRT to some trivial handler 
	struct sigaction abrt_act;
	abrt_act.sa_handler = handler;
	if (sigaction(SIGABRT, &abrt_act, NULL) == -1) {
		err_exit("sigaction");
	}

	// Block the delivery of the SIGABRT signal 
	sigset_t block_set;
	if (sigemptyset(&block_set) == -1) {
		err_exit("sigemptyset");
	}
	if (sigaddset(&block_set, SIGABRT) == -1) {
		err_exit("sigaddset");
	}
	if (sigprocmask(SIG_BLOCK, &block_set, NULL) == -1) {
		err_exit("sigprocmask");
	}

	// Call my_abort()
	my_abort();

	// The program should terminate after the handling of SIGABRT, or a goto 
	// statement can cause the program to return here
	printf("We should never see the print!\n");
	return(EXIT_SUCCESS);
}