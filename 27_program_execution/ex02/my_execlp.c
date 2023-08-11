/* Use execve() to implement execlp(). You will need to use the stdarg(3) API to 
 * handle the variable-length argument list supplied to execlp(). You will also 
 * need to use functions in the malloc package to allocate space for the 
 * argument and environmment vectors. Finally, note that an easy way of checking 
 * whether a file exists in a particular directory and is executable is simply 
 * to try execing the file.
*/

#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "tlpi_hdr.h"

extern char **environ;

int my_execlp(const char *filename, const char *arg, ... /* , (char *)NULL*/) {
	
	/* Find the executable name */
	bool use_path = false;	/* Track if we should use the PATH + filename or 
							 * just filename 
							 */
	char *path = (char *)malloc(strlen(filename) * sizeof(char));
	strcpy(path, filename);

	char *file = strrchr(path, '/');
	if (file != NULL) {
		file++;
	} else {
		use_path = true;
		file = path;
	}

	/* Build the argument vector */
	va_list vl1;
	va_list vl2;

	va_start(vl1, arg);
	va_copy(vl2, vl1);

	char *next_arg;
	int arg_size = 0;
	
	if (arg != (char *)NULL) {
		arg_size++;
		while((next_arg = va_arg(vl1, char *)) != (char *)NULL) {
			arg_size++;
		}
	}

	va_end(vl1);

	char **execve_argv = (char **)malloc((arg_size + 2) * sizeof(char *));
	execve_argv[0] = (char *)malloc(strlen(file) * sizeof(char));
	strcpy(execve_argv[0], file);

	if (arg != (char *)NULL) {
		execve_argv[1] = (char *)malloc(strlen(arg) * sizeof(char));
		strcpy(execve_argv[1], arg);

		for (int i = 2; i < arg_size + 1; i++) {
			next_arg = va_arg(vl2, char *);
			execve_argv[i] = (char *)malloc(strlen(next_arg) * sizeof(char));
			strcpy(execve_argv[i], next_arg);
		}
	}

	/* Argument vector must be NULL terminated */
	execve_argv[arg_size + 1] = NULL;

	/* Build the environment vector from the parent's env */
	char **ep;
	char **execve_envp;
	int ep_size = 0;
	for (ep = environ; *ep != NULL; ep++) {
		ep_size++;
	}
	execve_envp = malloc((ep_size + 1) * sizeof(char *));

	int i = 0;
	for (ep = environ; *ep != NULL; ep++) {
		execve_envp[i] = (char *)malloc(strlen(*ep) * sizeof(char));
		strcpy(execve_envp[i], *ep);
		i++;
	}
	execve_envp[ep_size] = NULL;

	/* Figure out the pathname and exec the process */
	if (use_path) {
		char *path_var = getenv("PATH");
		const char s[2] = ":";
		char *token;

		/* Needed for checking if executable. */
		struct stat stat_buf;

		token = strtok(path_var, s);
		while( token != NULL ) {
			token = strtok(NULL, s);

			/* Construct the path to the executable. */
			char *exec_file = malloc(strlen(token) + 1 + strlen(file));
			strcat(exec_file, token);
			strcat(exec_file, "/");
			strcat(exec_file, file);

			if (stat(exec_file, &stat_buf) == -1) {
				errExit("stat");
			}
			if (stat_buf.st_mode & S_IXUSR) {
				return execve(exec_file, execve_argv, execve_envp);
			}
		}
	} else {
		return execve(file, execve_argv, execve_envp);
	}
	return -1;
}

int main() {

	int status;

	switch(fork()){
		case -1:
			errExit("fork");
		case 0:
			/* Un-comment only one of these to test my_execlp(). */
			status = my_execlp("./test.exe", "my arg", "another", "rewq", "wert", (char *)NULL );
			// status = my_execlp("./test.exe", (char *)NULL );
			// status = my_execlp("python3", "--version", (char *)NULL );
			// status = my_execlp("gcc", "--help", (char *)NULL );
		default:
			// parent
			wait(&status);
			printf("The exit status is: %d\n", status);
	}
	return(EXIT_SUCCESS);
}
