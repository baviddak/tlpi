#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <utmpx.h>
#include <unistd.h>
#include <string.h>
#include <paths.h>


int main () {

	/* Use the wtmp since utmp doesn't seem to exist */
	utmpxname(_PATH_WTMP);

	const char *actual_ttyname = ttyname(STDIN_FILENO);

	/* */
	struct utmpx *ut;
	struct utmpx searchut;
	memset(searchut.ut_line, 0, sizeof(searchut.ut_line));
	fprintf(stdout, "Test point 1, the size of ut_line is %d\n", sizeof(searchut.ut_line));

	snprintf(searchut.ut_line, sizeof(searchut.ut_line) - 1, actual_ttyname);
	fprintf(stdout, "Test point 2, successfully snprintf() was called.\n");

	/* */
	setutxent();

	/* Traverse the entries in the file for the right one */
	while ( (ut = getutxent()) != NULL ) {
		fprintf(stdout, "The ut_line field is %s\n", ut->ut_line);
	}
	fprintf(stdout, "Test point 3, post while loop\n");
	fprintf(stdout, "Test point 4, the output of ttyname is %s\n", actual_ttyname);

	/* */
	endutxent();

	// strncpy(returnname, ut->ut_user, sizeof(returnname) - 1);
	return 0;
}
