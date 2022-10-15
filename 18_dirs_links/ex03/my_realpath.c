/* Implement realpath(). */

/* Usage: ./my_realpath.exe <symlinkpath> */


#include "tlpi_hdr.h"

#ifndef PATH_MAX
#define PATH_MAX 100
#endif // PATH_MAX

// char * my_realpath (const char *pathname, char *resolved_path) {
// 	// will have to check the i-node table

// }

int main (int argc, char *argv[]) {

	if (argc != 2) {
		// print usage error
		usageErr("Usage: ./my_realpath.exe <symlinkpath>");
	}

	char *symlink_path = argv[1];
	char my_realpath[PATH_MAX];

	realpath(symlink_path, my_realpath);

	printf("The real path is: %s\n", my_realpath);

	return (EXIT_SUCCESS);
}