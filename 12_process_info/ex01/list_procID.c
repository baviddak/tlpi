/* Write a program that lists the process ID and command name for all processes being run 
 * by the user named in the program's command-line argument. (You may find the userIdFromName() function 
 * from Listing 8-1, on page 159, useful.) This can be done by inspecting the Name: and Uid: lines of 
 * all of the /proc/PID/status files on the system. Walking through all of the /proc/PID directories 
 * on the system requires the use of readdir(3), which is described in Section 18.8. Make sure your 
 * program correctly handles the possibility that a /proc/PID directory disappears between the time 
 * that the program determines that the directory exists and the time that it tries to open the corresponding 
 * /proc/PID status file. 
 */

/* Usage: list_procID <username> */

#include <fcntl.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

#include "tlpi_hdr.h"
#include "ugid_functions.h"

#define FILEPATH_MAX 100
#define LINE_MAX 40
#define FILEBUF_MAX 200

int main(int argc, char *argv[]){
  int uid;
  int procuid;
  int status_fd;
  DIR *dirp;
  struct dirent *direntp;
  struct stat *stat_buf = (struct stat*)(malloc(sizeof(struct stat)));
  const char *procdir="/proc";
  char filepath_buf[FILEPATH_MAX];
  char linebuf[FILEBUF_MAX];
  char *token;
  char *line_token;
  
  uid = userIdFromName(argv[1]);
  
  dirp = opendir(procdir);
  errno = 0;
  
  while((direntp = readdir(dirp)) != NULL){
    
    if(strcmp(direntp->d_name, ".") == 0 || strcmp(direntp->d_name, "..") == 0){
      continue;
    }
    
    strcpy(filepath_buf, "/proc/");
    strcat(filepath_buf, direntp->d_name);
    lstat(filepath_buf, stat_buf);
    
    if(S_ISDIR(stat_buf->st_mode)){

      strcat(filepath_buf, "/status");
      status_fd = open(filepath_buf, O_RDONLY);
      if(status_fd == -1){
	printf("Couldn't open status file for %s\n", filepath_buf);
	close(status_fd);
	continue;
      }
      
      if(read(status_fd, linebuf, FILEBUF_MAX) == -1){errExit("read");}
      token = strtok(linebuf, "\n");
      
      while(token) {
	if(strncmp(token, "Uid", 3) == 0){
	  
	  /* printf("token is %s\n", token); */
	  
	  
	  line_token = strtok(token, "\t");
	  line_token = strtok(NULL, "\t");
	  
	  procuid = atoi(line_token);
	  
	  if(procuid == uid){
	    printf("file is %s\n", filepath_buf);
	    printf("Match!!\n");
	  }
	  break;
	}
	
	token = strtok(NULL, "\n");
	
      }
      close(status_fd);
    }
  }

  free(stat_buf);
  return(EXIT_SUCCESS); 
}
