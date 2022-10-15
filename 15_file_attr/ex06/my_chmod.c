/* Write a program that uses stat() and chmod() to perform the equivalent of 
 * chmod a+rX.
 */

/* Usage: ./my_chmod.exe <pathname>*/

#include <ctype.h>
#include <sys/stat.h>

#include "tlpi_hdr.h"

int main (int argc, char *argv[]) {

	// validate command
	if ( argc != 2 ) {
        usageErr("%s <pathname>", argv[0]);
    }

	// get the file path
	char *pathname = argv[1];

	// allocate buffer and call stat
	struct stat *stat_buf = (struct stat *)malloc(sizeof(struct stat));

	if (stat(pathname, stat_buf) == -1) {
		errExit("stat");
	}

	// enable read permission on the file for all category of user on the file
	if (chmod(pathname, S_IRUSR | S_IRGRP | S_IROTH) == -1) {
		errExit("chmod");
	}

	// enable execute permission for all category of user if the file is a 
	// directory
	if (S_ISDIR(stat_buf->st_mode)) {
		if (chmod(pathname, S_IXUSR | S_IXGRP | S_IXOTH) == -1) {
			errExit("chmod");
		}
		return (EXIT_SUCCESS);
	}

	// enable execute permission for all category of user if execute permission 
	// is enabled for any category of user
	if (stat_buf->st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)) {
		if (chmod(pathname, S_IXUSR | S_IXGRP | S_IXOTH) == -1) {
			errExit("chmod");
		}
	}
	
	return (EXIT_SUCCESS);
}