/* Implement setenv() and unsetenv() using getenv(), putenv() and, where 
 * necessary, code that directly modifies environ. Your version of unsetenv() 
 * should check to see whether there are multiple definitions of an environment 
 * variable, and remove them all (which is what the glic version of unsetenv() 
 * does). 
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>

#include "tlpi_hdr.h"

extern char **environ;

int index_of_equal(const char *name_value){
	int index = 0;
	char *p;

	for(p = name_value; *p != '='; p++){
		index++;
	}

	return(index);
}

int my_unsetenv(const char *name){
	/* Entered the my_unsetenv function */
	
	char **ep;
	char var_buf[100];
	int index;
	
	for(ep = environ; *ep != NULL; ep++){
		
		memset(var_buf, '\0', sizeof(var_buf));
		index = index_of_equal(*ep);
		strncpy(var_buf, *ep, index);
		
		if(strcmp(name, var_buf) == 0 && putenv(var_buf)){
			return(-1);
		}
	}
	return(0);
}

int main(){
	
	char **p;
	for(p = environ; *p != NULL; p++){
		puts(*p);
	}
	
	printf("--------------------------------\n\n");
	printf("--------------------------------\n\n");
	
	setenv("ENV_VAR_1", "this", 0);
	setenv("ENV_VAR_2", "that", 0);
	setenv("ENV_VAR_3", "the other thing", 0);
	
	for(p = environ; *p != NULL; p++){
		puts(*p);
	}
	
	printf("--------------------------------\n\n");
	printf("--------------------------------\n\n");
	
	my_unsetenv("ENV_VAR_2");
	/* putenv("ENV_VAR_1"); */
	
	for(p = environ; *p != NULL; p++){
		puts(*p);
	}
	
	printf("--------------------------------\n\n");
	printf("--------------------------------\n\n");
	
	return(EXIT_SUCCESS);
}

