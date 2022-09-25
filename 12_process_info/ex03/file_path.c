/* Write a program that lists all processes that have a particular file pathname 
 * open.
 */

/* Usage: ./file_path.exe <fullfilepath>*/

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

void print_str_len(char *in_str) {

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
	struct stat *stat_buf = (struct stat *)(malloc(sizeof(struct stat)));
	const char *procdir="/proc";
	const char *fd_dir="/fd/";
	char filepath_buf[FILEPATH_MAX];
	char *filepath;

	// check number of args and set filepath
	if ( argc != 2 ) {
        usageErr("%s <filepath>\n", argv[0]);
    }
	filepath = argv[1];
	
	// open the /proc dir
	dirp = opendir(procdir);
	if (dirp == NULL) {
		errExit("opendir");
	}
	errno = 0;

	while((direntp = readdir(dirp)) != NULL){
		
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

		// add the fd path
		strcat(filepath_buf, fd_dir);

		// traverse the /fd dir
		struct dirent *direntp_fd = (struct dirent *)(malloc(sizeof(struct dirent)));
		DIR *dirp_fd;
		dirp_fd = opendir(filepath_buf);
		
		while((direntp_fd = readdir(dirp_fd)) != NULL){ 

			char filepath_buf_fd[FILEPATH_MAX];
			char buffer[FILEPATH_MAX];
			strcpy(filepath_buf_fd, filepath_buf);

			// ignore this and parent folder
			if(strcmp(direntp_fd->d_name, ".") == 0 || strcmp(direntp_fd->d_name, "..") == 0){
				continue;
			}

			printf("The symlink full filename is: %s\n", strcat(filepath_buf_fd, direntp_fd->d_name));

			ssize_t bytes_written = readlink(filepath_buf_fd, buffer, FILEPATH_MAX);

			printf("The number of bytes written is: %ld\n", bytes_written);
			printf("The actual filename is: %s\n", buffer);

		}

	}
	free(stat_buf);
	return(EXIT_SUCCESS); 
}