/* Write a program to verify that when a child's parent terminates, a call to 
 * getppid() returns 1 (the process ID of init - systemd in newer systems).
 */

/* Usage: ./child_init.exe */

#include "tlpi_hdr.h"

int main() {

	printf("The parent process ID is: %d\n", getpid());

	switch(fork()){
		case -1:
			// bad
		case 0:
			// The child process
			sleep(10);
			printf("The parent process ID after terminating is: %d\n", getppid());
			_exit(0);
		default:
			// Parent process continues
			_exit(0);
	}
	return(EXIT_SUCCESS);
}