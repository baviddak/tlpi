/* Implement initgroups() using setgroups() and library functions for retrieving
 * information from the password and group files (Section 8.4). Remember that a
 * process must be privledged in order to be able to call setgroups()
 */

/* Usage: ./my_initgroups.exe */


#define _GNU_SOURCE
#include <unistd.h>
#include <sys/fsuid.h>
#include <limits.h>
#include "ugid_functions.h"   /* userNameFromId() & groupNameFromId() */
#include "tlpi_hdr.h"

#define SG_SIZE (NGROUPS_MAX + 1)


// int my_initgroups(const char *user, gid_t group) {
	
// }

int main() {

	uid_t ruid, euid, suid, fsuid;
    gid_t rgid, egid, sgid, fsgid;
    gid_t suppGroups[SG_SIZE];
    char *p;

    if (getresuid(&ruid, &euid, &suid) == -1) {
		errExit("getresuid");
	}
    if (getresgid(&rgid, &egid, &sgid) == -1) {
		errExit("getresgid");
	}

	printf("GID: ");
    p = groupNameFromId(rgid);
    printf("real=%s (%ld); ", (p == NULL) ? "???" : p, (long) rgid);
    p = groupNameFromId(egid);
    printf("eff=%s (%ld); ", (p == NULL) ? "???" : p, (long) egid);
    p = groupNameFromId(sgid);
    printf("saved=%s (%ld); ", (p == NULL) ? "???" : p, (long) sgid);
    p = groupNameFromId(fsgid);
    printf("fs=%s (%ld); ", (p == NULL) ? "???" : p, (long) fsgid);
    printf("\n");

	return (EXIT_SUCCESS);
}