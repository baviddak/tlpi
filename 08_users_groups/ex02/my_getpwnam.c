/* Implement getpwnam() using setpwent(), getpwent() and endpwent(). */

/* Usage: ./my_getpwnam.exe */

#include "tlpi_hdr.h"
#include <pwd.h>


void print_pwd(struct passwd *pr_pwd){
	if (pr_pwd != NULL) {
		printf("Login name:\t%s\n", pr_pwd->pw_name);
		printf("Encrypted pass:\t%s\n", pr_pwd->pw_passwd);
		printf("User ID:\t%d\n", pr_pwd->pw_uid);
		printf("Group ID:\t%d\n", pr_pwd->pw_gid);
		printf("Inital working directory:\t%s\n", pr_pwd->pw_dir);
		printf("Login shell: %s\n", pr_pwd->pw_shell);
		printf("\n");
		printf("----");
		printf("\n");
	} else {
		printf("pwd is NULL\n");
	}
}

struct passwd *my_getpwnam(const char *name){
	
	struct passwd *pwd;
	
	while((pwd = getpwent()) != NULL){

		if(strcmp(pwd->pw_name, name) == 0){
			endpwent(); /* Needed to reset the calls to getpwent */
			return pwd;
		}
	}

	endpwent();
	return NULL;
}

int main(int argc, char *argv[]){

	char * user_name1 = "david";
	char * user_name2 = "guest";
	char * user_name3 = "amanda"; /* Doesn't exist */
	
	struct passwd * pwd;

	// for david
	pwd = my_getpwnam(user_name1);
	print_pwd(pwd);
	
	// for amanda
	pwd = my_getpwnam(user_name3);
	print_pwd(pwd);
	
	// for guest
	pwd = my_getpwnam(user_name2);
	print_pwd(pwd);
	
	// for david
	pwd = my_getpwnam(user_name1);
	print_pwd(pwd);
	
	/* Actual call to the glibc function for reference */
	pwd = getpwnam(user_name3); 
	print_pwd(pwd);
	
	return(EXIT_SUCCESS);
}
