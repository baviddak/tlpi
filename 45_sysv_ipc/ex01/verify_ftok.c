#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/ipc.h>

#include "tlpi_hdr.h"

int main(int argc, char *argv[]) {


	/* Validate the input arguments */
	if (argc != 3) {
		printf("Usage: ./verify_ftok <pathname> <project_num>\n");
		return -1;
	}


	/* Allocate the stat buffer */
	struct stat stat_buffer;

	/* Generate the key */
	key_t created_key = ftok(argv[1], atoi(argv[2]));

	printf("The created key is %x\n", created_key);

	if (stat(argv[1], &stat_buffer) == -1) {
		errExit("stat");
	}


	/* Print stat info */
	printf("project number: %x\n", argv[2]);
	printf("st_dev: %x\n", stat_buffer.st_dev);
	printf("st_ino: %x\n", stat_buffer.st_ino);
	printf("st_mode: %x\n", stat_buffer.st_mode);
	printf("st_nlink: %x\n", stat_buffer.st_nlink);
	printf("st_uid: %x\n", stat_buffer.st_uid);
	printf("st_gid: %x\n", stat_buffer.st_gid);
	printf("st_rdev: %x\n", stat_buffer.st_rdev);
	printf("st_size: %x\n", stat_buffer.st_size);
	printf("st_blksize: %d\n", stat_buffer.st_blksize);
	printf("st_blocks: %d\n", stat_buffer.st_blocks);
	printf("st_atime: %d\n", stat_buffer.st_atime);
	printf("st_mtime: %d\n", stat_buffer.st_mtime);
	printf("st_ctime: %d\n", stat_buffer.st_ctime);


	return 0;
}
