/* 
 * Implement tee using I/O system calls. Implement the -a command-line option
 * which causes tee to append to the end of a file if it already exists. (Refer
 * to Appendix B)
 */

/* Usage: ./my_tee.exe [-a] output.txt < input.txt */

#include <sys/stat.h>
#include <fcntl.h>
#include <getopt.h>

#include "tlpi_hdr.h"

#ifndef BUFFER_MAX
#define BUFFER_MAX 1000
#endif

extern int optind;

int main(int argc, char * argv[]){
  
	int outputfd;
	int output_flags = O_WRONLY | O_CREAT | O_TRUNC;
	
	mode_t file_perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	ssize_t num_read;
	char buf[BUFFER_MAX];
	int opt;
	char * output_filename;
	
	if ( argc > 3 || strcmp(argv[1], "--help") == 0 ){
		usageErr("%s [-a] output_file < input_file", argv[0]);
	}

	while( (opt = getopt(argc, argv, ":a")) != -1 ){
		switch (opt) {
			case 'a':
				output_flags = O_WRONLY | O_CREAT | O_APPEND;
		}
	}

	if ( optind < argc ) {
		output_filename = argv[optind];
	}

	outputfd = open(output_filename, output_flags, file_perms);

	if ( outputfd == -1 ) {
		errExit("opening file %s", output_filename);
	}
	
	while ( (num_read = read(STDIN_FILENO, buf, BUFFER_MAX)) > 0 ){
		if ( write(outputfd, buf, num_read) != num_read ) {
			fatal("couldn't write whole buffer to output file");
		}
		if( write(STDOUT_FILENO, buf, num_read) != num_read ){
			fatal("couldn't write buffer to standard out");
		}
	}
	
	if (num_read == -1) {
		errExit("read");
	}
	
	/* close the output file descriptor */
	if ( close(outputfd) == -1 ) {
		errExit("close");
	}
	
	exit(EXIT_SUCCESS);
}
