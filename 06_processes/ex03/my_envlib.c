#include <stdlib.h>
#include <string.h>

#include "my_envlib.h"
#include "tlpi_hdr.h"

extern char **environ;

static int index_of_equal(const char *name_value){
	int index = 0;
	char *p;

	for(p = name_value; *p != '='; p++){
		index++;
	}

	return(index);
}

void my_printenv() {
	char **p;
	for(p = environ; *p != NULL; p++){
		puts(*p);
	}
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

int my_setenv(const char *name, const char *value, int overwrite){
	
	/* Since local_name and local_value are allocated on the heap, we don't have to
	* worry about the environment variables disappearing once the functions return
	*/

	char * nv_pair = (char *)malloc(sizeof(name) + sizeof(value) + sizeof(char));
	char * equal = "=";
	strcpy(nv_pair, name);
	strcat(nv_pair, equal);
	strcat(nv_pair, value);
	
	/* Do not change the environment variable if it already exists and the override is 0 */
	
	if(overwrite != 0){
		if(putenv(nv_pair) != 0){
			return(-1);
		}
	} else {
		if(getenv(name) == NULL){
			if(putenv(nv_pair) != 0){
				return(-1);
			}
		}
	}

	return(0);
}