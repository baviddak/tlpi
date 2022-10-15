/* The access() system call checks permissions using the process's real user and 
 * group IDs. Write a corresponding function that performs the checks according 
 * to the process's effective user and group IDs.
 */

/* Usage: ./access_effective.exe [-frwx] <pathname>*/

#include <ctype.h>
#include <sys/stat.h>

#include "tlpi_hdr.h"

int access_eff (const char *pathname, int mode) {

	// get effective group and user ID of this process
	uid_t p_euid = geteuid();
	gid_t p_egid = getegid();

	struct stat *stat_buf = (struct stat *)malloc(sizeof(struct stat));

	// call stat
	if (stat(pathname, stat_buf) == -1) {
		errExit("stat");
	}

	// get the user and group ID of file owner
	uid_t f_uid = stat_buf->st_uid;
	gid_t f_gid = stat_buf->st_gid;

	if (p_euid == 0) {
		// process is privileged
		printf("process is privileged\n");
	} 
	else if (p_euid == f_uid) {
		// effective user ID of the process is the same as the user ID (owner) 
		// of the file
		printf("effective user ID of the process is the same as the user ID (owner) of the file\n");
	}
	else if (p_egid == f_gid) {
		// effective group ID of the process matches the group ID (group owner) 
		// of the file
		printf("effective group ID of the process matches the group ID (group owner) of the file\n");

	} else {
		printf("use other\n");

	}
	return 0;
}

int main (int argc, char *argv[]) {

	// validate command
	if ( argc != 3 ) {
        usageErr("%s [-frwx] <pathname>", argv[0]);
    }

	char *pathname = argv[1];
	printf("pathname: %s\n", pathname);
	int mode = 0;
	int opt;

	while ((opt = getopt(argc, argv, "frwx")) != -1) {
		switch (opt) {
			case 'f':
				mode += F_OK;
				break;
			case 'r':	
				mode += R_OK;
				break;
			case 'w':
				mode += W_OK;
				break;
			case 'x':
				mode += X_OK;
				break;
			default:
				fatal("Unexpected case in options");
		}
	}

	return (EXIT_SUCCESS);
}

/* Notes:
 * ------
 * 1. If the process is privileged, all access is granted.
 * 2. If the effective user ID of the process is the same as the user ID (owner) 
 * of the file, then the access is granted according to the owner permissions on 
 * the file. For example, read access is granted if the owner-read permission 
 * bit is turned on in the file permissions mask; otherwirse, read access is 
 * denied.
 * 3. If the effective group ID of the process or any of the process supp. group 
 * IDs matches the group ID (group owner) of the file, then the access is 
 * granted according to the group permissions on the file.
 * 4. Otherwise, the access is granted according to the other permissions on the 
 * file.
 * 
 * The checks against owner, group, and the other permissions are done in order, 
 * and checking stops as soon as the applicable rule is found.
 * 
 * access():
 * ---------
 * The access() system call checks the accessibility of the file specified in 
 * pathname based on a process's real user and group IDs (and supplementary 
 * group IDs). 
 * It returns 0 if all permissions in mode are granted, otherwise returns -1.
 * 
 * Algorithm:
 * ----------
 * 1. Find the effective and group ID of the current process. (use geteuid, 
 * getegid)
 * 2. Get the user ID (owner) and group ID (group owner) of the file, and 
 * compare (from the i-node )
 * 2. Get the i-node of the file specified in pathname and inspect the st_mode
 * thing
 * 3. Follow the rules laid out in the notes (once a rule is fullfilled, 
 * checking stops)
 */