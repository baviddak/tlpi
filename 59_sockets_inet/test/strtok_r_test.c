/* Playground for strtok_r() */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_MAX 2048

int main (int argc, char *argv[]) {

	int flags = O_RDONLY;
	int opt;

	/* */
	if (argc < 2 || strcmp("--help", argv[1]) == 0 || strcmp("-h", argv[1]) == 0) {
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/* */
	const char *filename = argv[1];
	char contentbuf[BUF_MAX];
	memset(contentbuf, 0, sizeof(contentbuf));


	/* */
	int fd = open(filename, flags);
	ssize_t num_read = read(fd, contentbuf, sizeof(contentbuf) - 1);

	/* */
	const char *delim = "\n";	
	const char *delim2 = "=";
	char *saveptr, *saveptr2; // You can have as many save points as you want!
	char *token2, *subtoken;
	char *token = strtok_r(contentbuf, delim, &saveptr);

	/* */
	for (;;) {

		fprintf(stdout, "\n\n");

		if ( token == NULL ) {
			break;
		}
		fprintf(stdout, "Token: %s\n", token);
		fprintf(stdout, "Saveptr: %s\n", saveptr);

		/* */
		token2 = token;
		subtoken = strtok_r(token2, delim2, &saveptr2);
		for (;;) {

			if ( subtoken == NULL ) {
				break;
			}
			fprintf(stdout, "Second level token: %s\n", subtoken);
			subtoken = strtok_r(NULL, delim2, &saveptr2);
		}
		token = strtok_r(NULL, delim, &saveptr);

	}

	exit(EXIT_SUCCESS);
}
