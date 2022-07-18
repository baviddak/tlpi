/* Implement readv() and writev() using read(), write() and suitable functions 
 * from the malloc package (Section 7.1.2). 
 */

/* Usage: ./my_readv.exe inputfile outputfile 
 * all the contents from input file are transferred over to output file but 
 * first are put into memory via my_readv and my_writev 
 */

#include <sys/stat.h>
#include <fcntl.h>

#include "tlpi_hdr.h"

struct iovec {
	void *iov_base;   /* start address of buffer */
	size_t iov_len;   /* number of bytes to transfer to/from buffer */
};

ssize_t my_readv(int fd, const struct iovec *iov, int iovcnt){
	
	/* Will have to use malloc and free for the read funciton */
	/* Create the iov struct */
	ssize_t total_size = 0;
	int num_read;
	
	for(int i=0;i<iovcnt;i++){
		num_read = read(fd,iov[i].iov_base, iov[i].iov_len);
		
		if(num_read  == -1){
			/* Read has failed. Return a -1 */
			return(-1);
		}
		else if(num_read == 0){
			/* End of file reached. Return the size accumulated so far */
			/* total_size += num_read; */
			return(0);
		}
		else if(num_read > 0){
			total_size += num_read;
			continue;
		}
	}
	
	return(total_size);
}

int main(int argc, char * argv[]){
	/* First argument is the file to be written to */
	
	if(argc != 2 || strcmp(argv[1], "--help") == 0){
		usageErr("%s input_file output_file\n", argv[0]);
	}
	
	int flags = O_RDONLY;
	int permissions = S_IRUSR | S_IWUSR;
	
	int fd = open(argv[1],flags, permissions);
	
	if(fd == -1){
		errExit("open");
	}
	
	int num_read;
	int total_requested = 0;
	
	struct iovec iov[6];
	iov[0].iov_len = 2;
	iov[1].iov_len = 4;
	iov[2].iov_len = 6;
	iov[3].iov_len = 8;
	iov[4].iov_len = 100;
	iov[5].iov_len = 270;
	
	for(int i=0;i<6;i++){
		iov[i].iov_base = malloc(iov[i].iov_len);
		total_requested += iov[i].iov_len;
	}
	
	if((num_read = my_readv(fd, iov, 6)) == -1){
		return(-1);
	}
	
	for(int i=0;i<6;i++){
		printf("buffer %d has the string: %s\n", i, (char *)iov[i].iov_base);
	}
	
	printf("The number of bytes that is available in the buffer is %d\n", total_requested);
	printf("The number of bytes read into memory (the buffer) is %d\n", num_read);
	close(fd);
	
	for(int i=0;i<6;i++){
		free(iov[i].iov_base);
	}
	/* --- */
	
	return(EXIT_SUCCESS);
}
