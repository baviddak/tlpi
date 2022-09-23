/* Implement initgroups() using setgroups() and library functions for retrieving
 * information from the password and group files (Section 8.4). Remember that a
 * process must be privledged in order to be able to call setgroups()
 */

/* Usage: ./my_initgroups.exe */

#define _GNU_SOURCE

#include <unistd.h>
#include <sys/fsuid.h>
#include <limits.h>
#include <grp.h>
#include <pwd.h>

#include "ugid_functions.h"
#include "tlpi_hdr.h"

#define SG_SIZE (NGROUPS_MAX + 1)

// int my_initgroups(const char *user, gid_t group) {

// 	// get the 
	
// }

int main() {

	// gid_t suppGroups[SG_SIZE];

	// int return_val;

	// call getgroups
	// return_val = getgroups(SG_SIZE, suppGroups);
	// if (return_val == -1) {
	// 	errExit("getgroups");
	// }

	// printf("The return value is: %d\n", return_val);

	// for (int i=0; i<return_val; i++) {
	// 	printf("Group list %d: %d\n", i, suppGroups[i]);
	// }

	// create a new group list (add a random group)
	// gid_t *new_grouplist = (gid_t *)malloc((return_val+1)*sizeof(gid_t));
	// new_grouplist[return_val] = 300;

	// try to set groups 
	// return_val = setgroups(return_val+1, new_grouplist);
	// if (return_val == -1) {
	// 	errExit("setgroups");
	// }

	// test initgroups
	// char * my_name = "guest";
	// gid_t add_group = 300;

	// if (initgroups(my_name, add_group) == -1) {
	// 	errExit("initgroups");
	// }

	// call getgroups
	// return_val = getgroups(SG_SIZE, suppGroups);
	// if (return_val == -1) {
	// 	errExit("getgroups");
	// }

	// printf("The return value is: %d\n", return_val);

	// for (int i=0; i<return_val; i++) {
	// 	printf("Group list %d: %d\n", i, suppGroups[i]);
	// }

	// test initgroups
	// printf("---------------------------\n");
	// printf("Test users groups functions\n");
	// printf("---------------------------\n");

	// char * my_name = "david";

	// struct passwd *my_pw = getpwnam(my_name);
	// struct group *my_gr = getgrnam(my_name);
	// printf("My uid and gid: %d, %d\n",my_pw->pw_uid, my_pw->pw_gid);
	// printf("My gr_gid: %d\n",my_gr->gr_gid);

	// char * guest_name = "guest";

	// struct passwd *guest_pw = getpwnam(guest_name);
	// struct group *guest_gr = getgrnam(guest_name);
	// printf("Guest uid and gid: %d, %d\n",guest_pw->pw_uid, guest_pw->pw_gid);
	// printf("Guest gr_gid: %d\n",guest_gr->gr_gid);

	char * guest_name = "guest";
	struct group *grp;

	while ((grp = getgrent()) != NULL) {
		printf("Group id is: %d\n", grp->gr_gid);

		char **p = grp->gr_mem;
		// while (*p != NULL) {
		// 	printf("\tMember is: %s\n", *p);
		// 	p++;
		// }
	}

	endgrent();

	// if (initgroups(my_name, add_group) != -1) {
	// 	errExit("initgroups");
	// }

	return (EXIT_SUCCESS);
}