/* Write a program that lists the process ID and command name for all processes 
 * being run by the user named in the program's command-line argument. (You may 
 * find the userIdFromName() function from Listing 8-1, on page 159, useful.) 
 * This can be done by inspecting the Name: and Uid: lines of all of the 
 * /proc/PID/status files on the system. Walking through all of the /proc/PID 
 * directories on the system requires the use of readdir(3), which is described 
 * in Section 18.8. Make sure your program correctly handles the possibility 
 * that a /proc/PID directory disappears between the time that the program 
 * determines that the directory exists and the time that it tries to open the 
 * corresponding /proc/PID status file. 
 */

/* Usage: ./list_proc_id.exe <username> */

#include <fcntl.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>

#include "tlpi_hdr.h"
#include "ugid_functions.h"

#define FILEPATH_MAX 100
#define LINE_MAX 40
#define FILEBUF_MAX 200


struct uid_info {
   char type[50];
   char value[50];
};

int is_number(char *in_str) {

    int length = strlen (in_str);

    for (int i=0;i<length; i++) {
        if (!isdigit(in_str[i])) {
            // printf ("Entered input is not a number\n");
            return(-1);
        }
	}

    // printf ("Given input is a number\n");
	return(0);
}


int main(int argc, char *argv[]){
	int uid;
	int procuid;
	int status_fd;
	DIR *dirp;
	FILE *pid_fstream;
	struct dirent *direntp;
	struct stat *stat_buf = (struct stat *)(malloc(sizeof(struct stat)));
	const char *procdir="/proc";
	char filepath_buf[FILEPATH_MAX];
	char **pid_info;
	char *linebuf;
	char *token;
	char *line_token;
	size_t len = 0;

	// validate command
	if ( argc != 2 ) {
        usageErr("%s <username>", argv[0]);
    }
	
	// get the uid from username
	uid = userIdFromName(argv[1]);
	printf("The uid is %d", uid);
	
	// open the /proc dir
	dirp = opendir(procdir);
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

		// try to open the status file
		strcat(filepath_buf, "/status");
		// status_fd = open(filepath_buf, O_RDONLY);

		pid_fstream = fopen(filepath_buf, "r");
		if (pid_fstream == NULL) {
			printf("Couldn't open status file for %s\n", filepath_buf);
			continue;
		}

		// read in the line, parse the uid
		while (getline(&linebuf, &len, pid_fstream) != -1) {
			if (strstr(linebuf, "Name:")) {
				printf("%s\n", linebuf);
			}
			if (strstr(linebuf, "Uid:")) {
				printf("%s\n", linebuf);
				char * token = strtok(linebuf, " ");

				for (int i=0;i<2;i++) {
					printf( " %s\n", token ); 
					token = strtok(NULL, " ");
				}
		}

	}
	free(stat_buf);
	return(EXIT_SUCCESS); 
}