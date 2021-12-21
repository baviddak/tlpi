/* Implement setenv() and unsetenv() using getenv(), putenv() and, where necessary, code 
 * that directly modifies environ. Your version of unsetenv() should check to see whether there 
 * are multiple definitions of an environment variable, and remove them all (which is what the 
 * glibc version of unsetenv() does). 
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>

#include "tlpi_hdr.h"

extern char **environ;

int my_setenv(const char *name, const char *value, int overwrite){

  /* Since local_name and local_value are allocated on the heap, we don't have to worry about the environment variables disappearing once the functions return */
  
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
  }else{
    if(getenv(name) == NULL){
      if(putenv(nv_pair) != 0){
	return(-1);
      }  
    }
  }
  return(0);
}

int main(int argc, char * argv[]){

  char **p;
  for(p = environ; *p != NULL; p++){
    puts(*p);
  }

  my_setenv("ENV_VAR_1", "bitch", 0); /* Will be added, then over written by last call */
  my_setenv("ENV_VAR_1", "okay", 0); /* Will not over write the first call */

  printf("--------------------------------\n\n");
  printf("--------------------------------\n\n");
  for(p = environ; *p != NULL; p++){
    puts(*p);
  }
  
  my_setenv("ENV_VAR_2", "dun matter", 1); /* Will simply be added */
  my_setenv("ENV_VAR_1", "this", 1); /* Will overwrite the first call */

  printf("--------------------------------\n\n");
  printf("--------------------------------\n\n");
  for(p = environ; *p != NULL; p++){
    puts(*p);
  }
  
  return(EXIT_SUCCESS);
}

