/* Implement popen() and pclose(). */
#include "tlpi_hdr.h"

/* Rename these to my_popen and my_pclose to avoid a double definition error */

FILE *my_popen(const char *, const char *);
int my_pclose(FILE *);

int main() {


	/* Test our functions in main */


	return 0;
}

FILE *my_popen(const char *command, const char *mode) {

	/* Before anything, validate the mode*/
	if (strcmp(mode, "r") != 0 || strcmp(mode, "w") != 0) {
		return NULL;
	}

	/* Firstly, create a pipe */
	int pfd[2];

	if (pipe(pfd) == -1) {
		errExit("pipe");
	}




	/* Secondly, fork the process */


	/* Thirdly, from the child process, if the mode is r, 
	 * bind the write end of the pipe to the STDIN of the calling process?
	 * if the mode is w, bind the read end to .... 
	 */

	/* Create a new filestream */

}

int my_pclose(FILE *){

	/* Simply close the FD associated with this FILE stream */

}
