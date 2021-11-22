/* Write a program to verify that duplicated file descriptors share a file 
 * offset value and opn file status flags. 
 */

/* To create duplicate file descriptors, use dup()*/

/* Usage: offset_status_flags filename - filename is the name of the file which 
* we will create a file descriptor for, then create a duplicate file descriptor from
* that. We can then confirm that those two file descriptrs have the same status flags 
* and the same offset 
*/

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "tlpi_hdr.h"

int main (int argc, char * argv[]){
  int filed1, filed2;

  int open_flags = O_RDWR | O_CREAT | O_APPEND;
  int file_permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

  char * filename = argv[1];

  if((filed1 = open(filename, open_flags, file_permissions)) == -1){
    errExit("opening file %s", filename);
  }
  
  filed2 = dup(filed1);
  
  if(filed2 == -1){
    errExit("duplicating file descriptor 1");
  }

  if(lseek(filed1, 4, SEEK_CUR) == -1){
    errExit("lseek");
  }
  printf("the offset of the first file descriptor is %d\n", lseek(filed1, 0, SEEK_CUR));

  printf("the offset of the second file descriptor is %d\n", lseek(filed2, 0, SEEK_CUR));


  if(fcntl(filed2, F_SETFL, O_RDWR | O_CREAT ) == -1){
    errExit("fcntl");
  }

  printf("The status flags of the first file descriptor are: %d\n",fcntl(filed1, F_GETFL));

  printf("The status flags of the second file descriptor are: %d\n",fcntl(filed2, F_GETFL));
  
  return(EXIT_SUCCESS);
}
