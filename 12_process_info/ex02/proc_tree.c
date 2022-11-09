/* Write a program that draws a tree showing the heirarchical parent-child 
 * relationships of all the processes on the system, going all the way back to 
 * init.
 */

/* Usage: ./proc_tree.exe */

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
	DIR *dirp;
	FILE *pid_fstream;
	struct dirent *direntp;
	struct stat *stat_buf = (struct stat *)(malloc(sizeof(struct stat)));
	const char *procdir="/proc";
	char filepath_buf[FILEPATH_MAX];
	char *linebuf;
	char *token;
	size_t len = 0;
	
	// open the /proc dir
	dirp = opendir(procdir);
	errno = 0;
	
	while((direntp = readdir(dirp)) != NULL){
		int ppid;
		int pid;
		char name[LINE_MAX];
		
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

		pid_fstream = fopen(filepath_buf, "r");
		if (pid_fstream == NULL) {
			printf("Couldn't open status file for %s\n", filepath_buf);
			continue;
		}

		// read in the line, parse the pid and ppid
		while (getline(&linebuf, &len, pid_fstream) != -1) {
			// get the real uid of the process
			token = strtok(linebuf, "\t");

			if (!strcmp(linebuf, "Name:")) {
				token = strtok(NULL, "\t");
				strcpy(name, token);
				printf("Name: %s", name);
			}
			else if (!strcmp(linebuf, "Pid:")) {
				token = strtok(NULL, "\t");
				pid = atoi(token);
				printf("Pid: %d\n", pid);
			}
			else if (!strcmp(linebuf, "PPid:")) {
				token = strtok(NULL, "\t");
				ppid = atoi(token);
				printf("PPid: %d\n", ppid);
				break;
			}
		}
		printf("\n");

	}
	free(stat_buf);
	return(EXIT_SUCCESS); 
}