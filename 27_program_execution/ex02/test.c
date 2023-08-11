/* Build with "gcc test.c -o test.exe" */

#include <stdlib.h>
#include <stdio.h>

extern char **environ;

int main(int argc, char *argv[]){

	printf("This is the child process!\n");

	printf("The args are:\n");
	for (int i = 0; i < argc; i++){
		printf("%d: %s\n", i, argv[i]);
	}

	char ** ep;
	printf("The env is:\n");
	for (ep = environ; *ep != NULL; ep++){
		printf("%s\n", *ep);
	}
	return 0;
}