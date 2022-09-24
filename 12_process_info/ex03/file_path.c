/* Write a program that lists all processes that have a particular file pathname 
 * open.
 */

/* Usage: ./file_path.exe <filepath>*/

#include <sys/stat.h>
#include <dirent.h>
#include <ctype.h>
#include <stddef.h>

#include "tlpi_hdr.h"
#include "ugid_functions.h"

#define FILEPATH_MAX 100
#define LINE_MAX 50

int is_number(char *in_str) {

    int length = strlen (in_str);

    for (int i=0;i<length; i++) {
        if (!isdigit(in_str[i])) {
            return(-1);
        }
	}
	return(0);
}

int main(int argc, char *argv[]){
	DIR *dirp;
	struct dirent *direntp;
	struct dirent **result;
	struct stat *stat_buf = (struct stat *)(malloc(sizeof(struct stat)));
	const char *procdir="/proc";
	const char *fd_dir="/fd";
	char filepath_buf[FILEPATH_MAX];
	char *filepath;
	ssize_t len;

	// check number of args and set filepath
	if ( argc != 2 ) {
        usageErr("%s <filepath>", argv[0]);
    }
	filepath = argv[1];
	
	// open the /proc dir
	dirp = opendir(procdir);
	if (dirp == NULL) {
		errExit("opendir");
	}
	errno = 0;

	printf("check1\n");
	
	while(readdir_r(dirp, direntp, result) == 0) {

		printf("check2\n");

		// if end of dir is reached
		if(result == NULL){
			break;
		}
		
		// ignore this and parent folder
		if(strcmp(direntp->d_name, ".") == 0 || strcmp(direntp->d_name, "..") == 0){
			continue;
		}

		// check if the folder is a number
		if(is_number(direntp->d_name) != 0){
			continue;
		}

		// construct the full filename
		strcpy(filepath_buf, "/proc/");
		strcat(filepath_buf, direntp->d_name);
		lstat(filepath_buf, stat_buf);

		// check if it is a directory
		if(S_ISDIR(stat_buf->st_mode) == 0){
			continue;
		}
		strcat(filepath_buf, fd_dir);
		struct dirent *direntp_fd = (struct stat *)(malloc(sizeof(struct dirent)));
		struct dirent **result_fd;
		DIR *dirp_fd;

		printf("%s\n",filepath_buf);

		// traverse the /fd dir
		dirp_fd = opendir(filepath_buf);
		
		while(readdir_r(dirp_fd, direntp_fd, result_fd) == 0) { 

			// if end of dir is reached
			if(result_fd == NULL){
				break;
			}

			printf("The symlink filename is: %s\n", direntp_fd->d_name);
		}
		
	}
	free(stat_buf);
	return(EXIT_SUCCESS); 
}