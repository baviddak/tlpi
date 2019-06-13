#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

#include "tlpi_hdr.h"


#ifndef BUFFER_MAX
#define BUFFER_MAX 100
#endif

#ifndef COUNT
#define COUNT 20
#endif

/* Write a program that opens an existing file for writing with the O_APPEND flag, and then seeks to the beginning of the file before writing some data. Where does the data appear in the file? Why? */

/* Usage: write_beginning file_name input_text - input text is what is written to the file, file_name is the file to be written to  */

int main(int argc, char * argv[]){

  int fd;
  char buf[BUFFER_MAX];
  int num_written;

  if (argc != 2){
    usageErr ("%s file_name\n", argv[0]);}

  printf("Enter a string:\n");
  scanf("%100s", &buf);
  puts(buf);

  fd = open(argv[1], O_WRONLY | O_APPEND);

  if(fd == -1){
    errExit("open");}

  if(lseek(fd, 0, SEEK_SET) == -1){
    errExit("lseek");
  }

  num_written = write(fd, buf, strlen(buf));

  if(close(fd) == -1){
    errExit("close");}

  /* The O_APPEND flag will guaruntee that the 'seek' and the 'write' functions will occur atomically */
    
  
  return(EXIT_SUCCESS);
  
}

