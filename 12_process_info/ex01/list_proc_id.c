/* Write a program that lists the process ID and command name for all processes 
 * being run by the user named in the program's command-line argument. 
 */

/* Usage: ./list_proc_id.exe <username> */

#include <sys/stat.h>
#include <dirent.h>
#include <ctype.h>

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
	int uid;
	DIR *dirp;
	FILE *pid_fstream;
	struct dirent *direntp;
	struct stat *stat_buf = (struct stat *)(malloc(sizeof(struct stat)));
	const char *procdir="/proc";
	char filepath_buf[FILEPATH_MAX];
	char *linebuf;
	char *token;
	size_t len = 0;

	// validate command
	if ( argc != 2 ) {
        usageErr("%s <username>", argv[0]);
    }
	
	// get the uid from username
	uid = userIdFromName(argv[1]);
	printf("The uid is %d\n", uid);
	
	// open the /proc dir
	dirp = opendir(procdir);
	errno = 0;
	
	while((direntp = readdir(dirp)) != NULL){
		int procuid_r;
		char procname[LINE_MAX];
		char procuid[LINE_MAX];
		
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
				strcpy(procname, linebuf);
			}
			if (strstr(linebuf, "Uid:")) {
				strcpy(procuid, linebuf);

				// get the real uid of the process
				token = strtok(linebuf, "\t");
				token = strtok(NULL, "\t");
				procuid_r = atoi(token);

				// print if match
				if (procuid_r == uid){
					printf(procname);
					printf(procuid);
					printf("\n");
				}
			}
		}
	}
	free(stat_buf);
	return(EXIT_SUCCESS); 
}