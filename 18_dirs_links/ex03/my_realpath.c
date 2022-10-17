/* Implement realpath(). */

/* Usage: ./my_realpath.exe <symlinkpath> */

#include <sys/stat.h>
#include <limits.h>

#include "tlpi_hdr.h"

#ifndef PATH_MAX
#define PATH_MAX 100
#endif // PATH_MAX

char * my_realpath (const char *pathname, char *resolved_path) {
	int num_bytes;

	// will have to check the i-node table
	struct stat *stat_buf = (struct stat *)malloc(sizeof(struct stat));

	// get the i-node
	if (lstat(pathname, stat_buf) == -1) {
		err_exit("lstat");
	}

	// check if it is a symlink
	if (!S_ISLNK(stat_buf->st_mode)) {
		fatal("Not a symbolic link");
	}

	// copy symlink string to by resolved_path
	num_bytes = readlink(pathname, resolved_path, PATH_MAX);

	// null-terminate the string
	resolved_path[num_bytes] = '\0';

	return resolved_path;
}

int main (int argc, char *argv[]) {

	if (argc != 2) {
		// print usage error
		usageErr("Usage: ./my_realpath.exe <symlinkpath>");
	}

	char *symlink_path = argv[1];
	char realpath[PATH_MAX];

	// test our function
	my_realpath(symlink_path, realpath);
	printf("The real path is: %s\n", realpath);

	return (EXIT_SUCCESS);
}