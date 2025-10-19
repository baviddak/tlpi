/* Simple program to test getopt() function. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

#define MAX_NAME 128

struct person {
	char name[MAX_NAME];
	char last_name[MAX_NAME];
	int age;
};


int main (int argc, char *argv[]) {

	int opt;
	struct person me;
	memset(&me, 0, sizeof(struct person));

	while ((opt = getopt(argc, argv, "n:l:a:")) != -1){
		switch (opt) {
			case 'n':
				snprintf(me.name, MAX_NAME, optarg);
				break;
			case 'l':
				snprintf(me.last_name, MAX_NAME, optarg);
				break;
			case 'a':
				me.age = atoi(optarg);
				break;
			default:
				fprintf(stderr, "Error in setting command line arguments\n");
				return -1;
				break;
		}
	}

	printf("My first name is %s\n", me.name);
	printf("My last name is %s\n", me.last_name);
	printf("My age is %d\n", me.age);
	return 0;
}

