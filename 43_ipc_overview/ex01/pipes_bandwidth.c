/* 
 * Write a progam that measures the bandwidth provided by pipes. As command-line 
 * arguments, the program should accept the number of data blocks to be sent and 
 * the size of each data block. After creating a pipe, the program splts into 
 * two process: a child that writes the data blocks to the pipe as fast as 
 * possible, and a parent that reads the data blocks. After all data has been 
 * read, the parent should print the elapsed time reqired and the bandwidth 
 * (bytes transferred per second). Measure the bandwidth for different data 
 * block sizes.
 */

/* Usage: ./pipes_bandwidth.exe <number_of_blocks> <size_of_block_in_bytes> */

#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include "tlpi_hdr.h"

int main (int argc, char *argv[]) {

	int pfd[2]; // pfd[1]: write end, pfd[0]: read end
	char *send_buf;
	char *rec_buf;

	int size_of_block;
	int num_of_blocks;

	ssize_t n_read;
	ssize_t total_bytes_read = 0;
	ssize_t total_bytes_needed;

	int start_time;
	int end_time;

	if (pipe(pfd) == -1) {
		errExit("pipe");
	}

	// Validate the command line args
	if(argc != 3 || strcmp(argv[1], "--help") == 0){
		usageErr("%s \narg count is %d\n", argv[0], argc);
	}
	if ((num_of_blocks = atoi(argv[1])) == -1) {
		errExit("atoi");
	}
	if ((size_of_block = atoi(argv[2])) == -1){
		errExit("atoi");
	}
	total_bytes_needed = size_of_block * num_of_blocks;

	// Set up the send and recieve buffers
	send_buf = (char *)malloc(size_of_block * sizeof(char));
	rec_buf = (char *)malloc(size_of_block * sizeof(char));
	memset(send_buf, '.', size_of_block);
	
	/* Fork the process */
	switch(fork()) {
		case -1:
			errExit("fork");
		case 0: // Child Process - writes the data blocks to the pipe

			/* Close the read end */
			if (close(pfd[0]) == -1) {
				errExit("close");
			}

			/* Start the clock */
			start_time = clock();

			/* Write data to the pipe */
			for(int i = 0; i < num_of_blocks; i++) {
				if (write(pfd[1], send_buf, size_of_block) == -1) {
					errExit("write");
				}
			}

		default: // Parent Process - reads the data blocks

			/* Close the write end */
			if (close(pfd[1]) == -1) {
				errExit("close");
			}

			while (total_bytes_read < total_bytes_needed) {
				if ((n_read = read(pfd[0], rec_buf, size_of_block)) == -1) {
					errExit("read");
				}
				total_bytes_read += n_read;
			}
			end_time = clock();

			double total_time = ((double)(end_time - start_time)) / ((double)CLOCKS_PER_SEC);
			printf("The elapsed time is %f seconds.\n", total_time);
			printf("The bandwidth is %.0f bytes per second.\n", (double)total_bytes_read / total_time);
	}
	return 0;
}