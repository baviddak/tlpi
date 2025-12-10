/* Implement ttyname() */

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

char *my_ttyname(int fd) {

	/* Allocate some space on the heap for the return val */
	char *returnstr = (char *)malloc(256 * sizeof(char));
	memset(returnstr, 0, 256);

	/* Retrieve the device ID from the file descriptor. */
	struct stat sb;
	dev_t origin_devid;

	if ( fstat(fd, &sb) == -1 ) {
		fprintf(stderr, "Error in fstat: %s\n", strerror(errno));
		return NULL;
	}
	origin_devid = sb.st_rdev;

	/* Use the get attr function */
	char *searchdirs[] = {"/dev/", "dev/pts/"};
	DIR *devdirp;
	char *curr_file;
	struct dirent *drs;

	if ( (devdirp =  opendir(searchdirs[0])) == NULL ) {
		fprintf(stderr, "Error opening device directory: %s\n", strerror(errno));
		return NULL;
	}

	while ( (drs = readdir(devdirp)) != NULL ) {

		snprintf(returnstr, 256 - 1, "%s%s", searchdirs[0], drs->d_name);

		if ( stat(returnstr, &sb) == -1 ) {
			fprintf(stderr, "Error calling stat(): %s\n", strerror(errno));
			return NULL;
		}

		if ( origin_devid == sb.st_rdev ) {
			return returnstr;
		}
	}
	return NULL;
}

int main (int argc, char *argv[]) {

	/* Simple args check */
	if ( argc < 2 || strcmp(argv[1], "--help" ) == 0 ) {
		fprintf(stderr, "Usage: %s <tty_filename>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/* Open our test file */
	int flags = O_RDWR;
	int ttyfd = open(argv[1], flags);
	if ( ttyfd == -1 ) {
		fprintf(stderr, "Error in opening the file: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* Test our implementation */
	fprintf(stdout, "The filename is %s\n", my_ttyname(ttyfd));
	exit(EXIT_SUCCESS);
}
