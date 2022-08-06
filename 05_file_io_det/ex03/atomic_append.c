/* 
 * 
*/

/* Usage: ./atomic_append.exe filename num-bytes [x] 
 * 
 */



#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>

#include "tlpi_hdr.h"

// typedef enum boolean { false, true } bool;

int main(int argc, char *argv[]){
	int opt;
	int open_flags = O_CREAT | O_RDWR | O_APPEND;
	bool seek = false;
	
	char *filename = argv[1];
	int buf_size =  atoi(argv[2]);
	
	/* There is a bug here that causes argv[2] to be the filename when the -x 
	 * option is specified, and it works correctly when it is not specified 
	 */
	
	/* The bug seems to be that getopt modifies the actual argument vector */
	while((opt = getopt(argc, argv, "x")) != -1){
		if(opt == 'x'){
			seek = true;
			open_flags = O_CREAT | O_RDWR;
		}
	}
	
	if(seek == true){
		printf("The x option has been specified!\n");
	}
	
	int num_written;
	int fd;
	char *buf;
	printf("The buffer size is %d\n", buf_size);
	
	buf = (char *)malloc(buf_size);
	
	fd = open(filename, open_flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	
	if(fd == -1){
		errExit("open");
	}
	
	if(seek == true && lseek(fd, 0, SEEK_END) == -1){
		errExit("lseek");
	}
	
	num_written = write(fd, buf, buf_size);
    printf("Number of bytes written is %d\n", num_written);
    
	if(num_written == -1){
		errExit("write");
	}
    
    if(close(fd) == -1){
		errExit("close");
	}
    
    free(buf);
    return(EXIT_SUCCESS);
}


/* The write function will check how many bytes are written to the file each 
 * time it does a write. If you append 1000000 bytes 2 times atomically then you 
 * are guarunteed to get a file that is (original file size) + 2000000. If you 
 * run these two appends in parallel and non-atomic then you will get a file 
 * that is (original file size) + 1000000 because once the first 1000000 bytes 
 * is written then it will stop, even thought the two processes are constantly 
 * pre-empting each other. 
 */
