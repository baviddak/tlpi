/* Write a program, analogous to cp(1), that uses mmap() and memcpy() calls
 * (instead of read() or write()) to copy a source file to a destination file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>

int main (int argc, char *argv[]) {

	if ( argc < 3 || strcmp(argv[1], "--help") == 0 ) {
		fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/* Get the file descriptor of the source file */
	int source_flags = O_RDONLY;
	int source_fd;

	if ( (source_fd = open(argv[1], source_flags)) == -1 ) {
		fprintf(stderr, "Error in open(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* Get the size of source file */
	struct stat sb;
	
	if ( fstat(source_fd, &sb) == -1 ) {
		fprintf(stderr, "Error in fstat(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* Open or create the destination file, truncate it to size */
	int dest_flags = O_RDWR | O_CREAT;
	mode_t dest_mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;
	int dest_fd;

	if ( (dest_fd = open(argv[2], dest_flags, dest_mode)) == -1 ) {
		fprintf(stderr, "Error in open(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if ( ftruncate(dest_fd, sb.st_size) == -1 ) {
		fprintf(stderr, "Error in ftruncate(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* Create the memory mapping for the source file */
	int source_prot = PROT_READ;
	int source_mmap_flags = MAP_PRIVATE;
	char *srcaddr;

	srcaddr = mmap(NULL, sb.st_size, source_prot, source_mmap_flags, source_fd, 0);
	if ( srcaddr == MAP_FAILED ) {
		fprintf(stderr, "Error in mmap(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* Create the memory mapping for the destination file */
	int dest_prot = PROT_WRITE | PROT_READ;
	int dest_mmap_flags = MAP_SHARED;
	char *destaddr;

	destaddr = mmap(NULL, sb.st_size, dest_prot, dest_mmap_flags, dest_fd, 0);
	if ( destaddr == MAP_FAILED ) {
		fprintf(stderr, "Error in mmap(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	/* Copy the content over to the destination using memcpy() */
	memcpy(destaddr, srcaddr, sb.st_size);

	exit(EXIT_SUCCESS);
}
