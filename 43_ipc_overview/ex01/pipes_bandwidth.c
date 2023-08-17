/* Write a progam that measures the bandwidth provided by pipes. As command-line 
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
#include "tlpi_hdr.h"

int main (int argc, char *argv[]) {

	int pfd[2]; // pfd[1]: write end, pfd[0]: read end
	char **byte_blocks;
	int size_of_block;
	int num_of_blocks;

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

	// Create the block of data to write
	byte_blocks = (char **)malloc(num_of_blocks * sizeof(char *));
	for (int i = 0; i < num_of_blocks; i++) {

		// allocate space for a block
		byte_blocks[i] = (char *)malloc(size_of_block * sizeof(char));

		// use memset to fill
		memset(byte_blocks[i], 's', size_of_block);
	}

	return 0;
}