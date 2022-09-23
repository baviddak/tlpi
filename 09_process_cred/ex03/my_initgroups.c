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

int my_initgroups(const char *user, gid_t group) {

	gid_t new_grouplist[SG_SIZE];
	size_t new_size = 1;

	new_grouplist[0] = group;

	// build a list of the user's supp group IDs
	struct group *grp;

	while ((grp = getgrent()) != NULL) {

		int i = 0;
		char *p = grp->gr_mem[i];

		while (p != NULL) {

			if (strcmp(p, user) == 0) {
				// match
				new_grouplist[new_size] = grp->gr_gid;
				new_size++;
			}

			i++;
			p = grp->gr_mem[i];
		}
	}

	// call setgroups with the new group list 
	return setgroups(new_size, new_grouplist);
}

int main() {

	gid_t suppGroups[SG_SIZE];

	int return_val;

	// call getgroups
	return_val = getgroups(SG_SIZE, suppGroups);
	if (return_val == -1) {
		errExit("getgroups");
	}

	printf("The return value is: %d\n", return_val);

	for (int i=0; i<return_val; i++) {
		printf("Group list %d: %d\n", i, suppGroups[i]);
	}

	// test my_initgroups
	char * my_name = "david";
	gid_t add_group = 300;

	if (my_initgroups(my_name, add_group) == -1) {
		errExit("initgroups");
	}
	
	// call getgroups
	return_val = getgroups(SG_SIZE, suppGroups);
	if (return_val == -1) {
		errExit("getgroups");
	}

	printf("The return value is: %d\n", return_val);

	for (int i=0; i<return_val; i++) {
		printf("Group list %d: %d\n", i, suppGroups[i]);
	}

	return (EXIT_SUCCESS);
}