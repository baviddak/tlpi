/* Implement dup() and dup2() using fcntl() and, where necessary, close(). (You 
 * may ignore the fact that dup2() and fcntl() return different errno values for 
 * some error cases.) For dup2(), remember to handle the special case where 
 * oldfd equals newfd. In this case, you should check whether oldfd is valid, 
 * which can be done by, for example, checking if fcntl(oldfd, F_GETFL) 
 * succeeds. If oldfd is not valid, then the function should return -1 with 
 * errno set to EBADF. 
 */

#include <sys/stat.h>
#include <fcntl.h>

#include "tlpi_hdr.h"

/* The dup() call takes oldfd, an open file descriptor, and returns a new 
 * descriptor that refers to the same open file description. The new descriptor 
 * is guarunteed to be the lowest unused file descriptor. 
 */

/* Returns (new) file descriptor on success, or -1 on error */
int my_dup(int oldfd){

	/*initialize the return file descriptor*/
	int returnfd; 
	
	/* Check if the old file descriptor is valid - that is check if the file is
	 * open
	 */
	
	if(fcntl(oldfd, F_GETFL) == -1){
		usageErr("fcntl");
		return(-1);
	}
	
	/*duplicate the file descriptor, if the operation fails, return -1*/
	
	if ((returnfd = fcntl(oldfd, F_DUPFD, 0)) == -1){
		usageErr("fcntl");
		return(-1);
	}
	
	return(returnfd);
}

/* The dup2() system call makes a duplicate of the file descriptor given in 
 * oldfd using the descriptor number supplied in newfd. If the file descriptor 
 * specified in newfd is already open, dup2() closes it first. (Any error that 
 * occurs during this close is silently ignored.) The closing and reuse of newfd
 * are performed atomically, which avoids the possibility that newfd is reused 
 * between the two steps in a signalhandler or a parallelthread that allocates a 
 * file descriptor. 
 */

/* Returns (new) file descriptor on success, or -1 on error */
int my_dup2(int oldfd, int newfd){
	
	/*initialize the return file descriptor*/
	int returnfd;
	
	if (newfd == oldfd){
		errExit("oldfd == newfd");
	}
	
	if(fcntl(oldfd, F_GETFL) == -1){
		usageErr("fcntl");
		return(-1);
		errno = EBADF;
	}
	
	if(fcntl(newfd, F_GETFL) != -1){
		/* The new file descriptor is already in use*/
		close(newfd);
	}
	
	if((returnfd = fcntl(oldfd, F_DUPFD, newfd)) == -1){
		usageErr("fcntl");
		return(-1);
	}

	return(returnfd);
}

int main(int argc, char * argv[]){
	/*Here we will call the two functions to test them out*/
	
	return(EXIT_SUCCESS);
}

