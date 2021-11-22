/* Implement readv() and writev() using read(), write() and suitable functions 
 * from the malloc package (Section 7.1.2). 
 */

/* Usage: my_readv_writev inputfile outputfile - all the contents from input file 
 * are transferred over to output file but first are put into memory via my_readv 
 * and my_writev 
 */


#include <sys/stat.h>
#include <fcntl.h>

#include "tlpi_hdr.h"

struct iovec{
  void *iov_base;   /* start address of buffer */
  size_t iov_len;   /* Number of bytes to transfer to/from buffer */
};

ssize_t my_writev(int fd, const struct iovec *iov, int iovcnt){
  int num_written;
  int total_written = 0;

  for (int i=0; i<iovcnt; i++){    
    if((num_written = write(fd, iov[i].iov_base, iov[i].iov_len)) == -1){
      printf("write has returned -1\n");
      return(-1);
    }
    if(num_written < iov[i].iov_len){
      printf("The number of bytes written is less than the desired.\n");
      return(-1);
    }
    total_written += num_written;
    num_written = 0;
  }
  return(total_written);
}

int main(int argc, char * argv[]){
  /* First argument is the file to be written to  */

  if(argc != 2 || strcmp(argv[1], "--help") == 0){
    usageErr("%s input_file output_file\n", argv[0]);
  }

  ssize_t num_written;
  int num_to_write = 0;

  int flags = O_RDWR | O_APPEND | O_CREAT | O_TRUNC;
  int permissions = S_IRUSR | S_IWUSR;
  
  int fd = open(argv[1],flags, permissions);

  /* Set up the iov struct */
  struct iovec iov[4];
  char elem_0[] = "My love for you is strong.\n I am the one\n";
  char elem_1 = 'x';
  int elem_2 = 1234;
  char elem_3[] = "When will we know the path\n";


  iov[0].iov_base = elem_0;
  iov[0].iov_len = sizeof(elem_0);

  iov[1].iov_base = &elem_1;
  iov[1].iov_len = sizeof(elem_1);

  iov[2].iov_base = &elem_2;
  iov[2].iov_len = sizeof(elem_2);

  iov[3].iov_base = elem_3;
  iov[3].iov_len = sizeof(elem_3);
  

  for(int i=0;i<4;i++){
    num_to_write += iov[i].iov_len;
  }
  printf("The number of bytes to write to the file is %d\n", num_to_write);
  if((num_written = my_writev(fd, iov, 4)) == -1){
    errExit("write");
  }
  if(num_written < num_to_write){
    printf("The number of bytes written to the file is less that what was desired.\n");
    return(-1);
  }
  
  printf("The number of bytes written to the file is %zd\n", num_written);
  close(fd);
  
  return(EXIT_SUCCESS);
}
