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

	// allocate the stat buffer
	struct stat *stat_buf = (struct stat *)malloc(sizeof(struct stat));

	// call stat
	if (stat(pathname, stat_buf) == -1) {
		errExit("stat");
	}

	// get the user and group ID of file owner
	uid_t f_uid = stat_buf->st_uid;
	gid_t f_gid = stat_buf->st_gid;

	// get the st_mode
	mode_t f_mode = stat_buf->st_mode;
	int f_mode_mask = 0;

	if (p_euid == 0) {
		// process is privileged - all access is granted
		return  0;
	} 
	else if (p_euid == f_uid) {
		// effective user ID of the process is the same as the user ID (owner) 
		// of the file - access is granted according to the owner permissions on 
 		// the file

		// check f_mode against S_IRUSR, S_IWUSR, S_IXUSR
		if (f_mode & S_IRUSR) {
			f_mode_mask += R_OK;
		}
		if (f_mode & S_IWUSR) {
			f_mode_mask += W_OK;
		}
		if (f_mode & S_IXUSR) {
			f_mode_mask += X_OK;
		}

		// check file permission mask against mode
		if (f_mode_mask == mode){
			printf("Mask of file (%d) is the same as mode (%d)\n", f_mode_mask, mode);
			return 0;
		} else {
			printf("Mask of file (%d) not equal to mode (%d)\n", f_mode_mask, mode);
			return -1;
		}

	}
	else if (p_egid == f_gid) {
		// effective group ID of the process matches the group ID (group owner) 
		// of the file - access is granted according to the group permissions on 
		// the file
		
		// check f_mode against S_IRGRP, S_IWGRP, S_IXGRP
		if (f_mode & S_IRGRP) {
			f_mode_mask += R_OK;
		}
		if (f_mode & S_IWGRP) {
			f_mode_mask += W_OK;
		}
		if (f_mode & S_IXGRP) {
			f_mode_mask += X_OK;
		}

		// check file permission mask against mode
		if (f_mode_mask == mode){
			printf("Mask of file (%d) is the same as mode (%d)\n", f_mode_mask, mode);
			return 0;
		} else {
			printf("Mask of file (%d) not equal to mode (%d)\n", f_mode_mask, mode);
			return -1;
		}

	} else {
		// access is granted according to the other permissions on the file

		// check f_mode against S_IROTH, S_IWOTH, S_IXOTH
		if (f_mode & S_IROTH) {
			f_mode_mask += R_OK;
		}
		if (f_mode & S_IWOTH) {
			f_mode_mask += W_OK;
		}
		if (f_mode & S_IXOTH) {
			f_mode_mask += X_OK;
		}

		// check file permission mask against mode
		if (f_mode_mask == mode){
			printf("Mask of file (%d) is the same as mode (%d)\n", f_mode_mask, mode);
			return 0;
		} else {
			printf("Mask of file (%d) not equal to mode (%d)\n", f_mode_mask, mode);
			return -1;
		}
	}
}

int main (int argc, char *argv[]) {

	// validate command
	if ( argc != 3 ) {
		usageErr("%s [-frwx] <pathname>", argv[0]);
	}

	// set variables
	char *pathname = argv[2];
	printf("pathname: %s\n", pathname);
	int mode = 0;
	int opt;

	// get options
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

	// test our function
	int ans = access_eff(pathname, mode);
	printf("Return: %d\n", ans);

	return (EXIT_SUCCESS);
}