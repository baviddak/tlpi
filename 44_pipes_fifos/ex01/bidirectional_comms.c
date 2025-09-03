#include <unistd.h>

#include "tlpi_hdr.h"

#define BUFFER_MAX 100


/* Note: try creating a Stream interface in C */


void convert_to_lower(char source[], char destination[], int size) {

	int i = 0;

	for ( i = 0; i < size ; i++) {
		
		switch(source[i]) {

			case 'a': 
				destination[i] = 'A';
			case 'b': 
				destination[i] = 'B';

			case 'c':
				destination[i] = 'C';

			case 'd':
				destination[i] = 'D';

			case 'e':
				 destination[i] = 'E';

			case 'f':
				 destination[i] = 'F';

			case 'g':
				 destination[i] = 'G';

			case 'h':
				 destination[i] = 'H';

			case 'i':
				 destination[i] = 'I';

			case 'k':
				 destination[i] = 'K';

			case 'l':
				 destination[i] = 'L';

			case 'm':
				 destination[i] = 'M';

			case 'n':
				 destination[i] = 'N';

			case 'o':
				 destination[i] = 'O';

			case 'p':
				 destination[i] = 'P';

			case 'r':
				 destination[i] = 'R';

			case 's':
				 destination[i] = 'S';

			case 't':
				 destination[i] = 'T';

			case 'u':
				 printf("u was hit\n");
				 destination[i] = 'U';

			case 'v':
				 destination[i] = 'V';

			case 'w':
				 destination[i] = 'W';

			case 'x':
				 destination[i] = 'X';

			case 'y':
				 destination[i] = 'Y';

			case 'z':
				 destination[i] = 'Z';

			default:
				destination[i] = source[i];
		}

	}

	printf("%s\n", destination);
	
}

int main () {

	/* create a buffer to store the read in bytes */
	char buffer[BUFFER_MAX];
	char alt_buffer[BUFFER_MAX];


	/* 0 is the read end, 1 is the write end */
	int parent_to_child[2];
	int child_to_parent[2];

	ssize_t num_read;
	ssize_t num_written;


	if (pipe(parent_to_child) == -1) {
		errExit("pipe");
	}

	if (pipe(child_to_parent) == -1) {
		errExit("pipe");
	}


	switch(fork()) {

		case -1:
			/* Error */
			errExit("fork");
		case 0:
			/* Child process */


			if (close(parent_to_child[1]) == -1) {
				errExit("close");
			}
			if (close(child_to_parent[0]) == -1) {
				errExit("close");
			}

			/* Continuously read from the pipe, convert and send back the bits */
			for (;;) {

				num_read = read(parent_to_child[0], buffer, BUFFER_MAX);

				if (num_read == -1) {
					errExit("read");
				}

				convert_to_lower(buffer, alt_buffer, num_read);

				num_written = write(child_to_parent[1], alt_buffer, BUFFER_MAX);
				if (num_written == -1) {
					errExit("write");
				}


			}

			break;
		default:
			/* Parent process */
			if (close(parent_to_child[0]) == -1) {
				errExit("close");
			}
			if (close(child_to_parent[1]) == -1) {
				errExit("close");
			}


			/* Continuously read in from stdin, write to the pipe */
			for (;;) {


				/* Read in, pass the data to the child throught the pipe */

				num_read = read(STDIN_FILENO, buffer, BUFFER_MAX);

				if (num_read == -1) {
					errExit("read");
				}
				if (num_read == 0) {
					break;
				}

				num_written = write(parent_to_child[1], buffer, BUFFER_MAX);

				if (num_written == -1){
					errExit("write");
				}


				/* Read back from child, pass the data to STDOUT */
				num_read = read(child_to_parent[0], buffer, BUFFER_MAX);

				if (num_read == -1) {
					errExit("read");
				}

				num_written = write(STDOUT_FILENO, buffer, BUFFER_MAX);

				if (num_written == -1) {
					errExit("write");
				}


			}



			break;
	}

}
