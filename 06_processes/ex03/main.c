/* Implement setenv() and unsetenv() using getenv(), putenv() and, where 
 * necessary, code that directly modifies environ. Your version of unsetenv() 
 * should check to see whether there are multiple definitions of an environment 
 * variable, and remove them all (which is what the glic version of unsetenv() 
 * does). 
 */

/* Usage: ./my_envlib.exe > output.txt */

#define _GNU_SOURCE
#include <stdlib.h>

#include "tlpi_hdr.h"
#include "my_envlib.h"

void test_my_setenv(){
	printf("Test my_setenv():\n\n");

	printf("--------------------------------\n");
	printf("Environment before set:\n");
	printf("--------------------------------\n");
	my_printenv();
	
	my_setenv("ENV_VAR_1", "brap", 0); /* Will be added, then over written by last call */
	my_setenv("ENV_VAR_1", "okay", 0); /* Will not over write the first call */
	
	printf("--------------------------------\n");
	printf("Environment after set:\n");
	printf("--------------------------------\n");
	my_printenv();
	
	my_setenv("ENV_VAR_2", "yoyo", 1); /* Will simply be added */
	my_setenv("ENV_VAR_1", "this", 1); /* Will overwrite the first call */
	
	printf("--------------------------------\n");
	printf("Environment after second set:\n");
	printf("--------------------------------\n");
	my_printenv();

}

void test_my_unsetenv(){
	printf("Test my_unsetenv():\n\n");
	
	/* set some test vars */
	setenv("ENV_VAR_1", "this", 0);
	setenv("ENV_VAR_2", "that", 0);
	setenv("ENV_VAR_3", "other", 0);
	
	printf("--------------------------------\n");
	printf("Environment before unset:\n");
	printf("--------------------------------\n");
	my_printenv();
	
	/* unset ENV_VAR_2 */
	my_unsetenv("ENV_VAR_2");
	/* putenv("ENV_VAR_1"); */

	printf("--------------------------------\n");
	printf("Environment after unset:\n");
	printf("--------------------------------\n");
	my_printenv();
}

int main(){
	test_my_setenv();
	test_my_unsetenv();
	
	return(EXIT_SUCCESS);
}

