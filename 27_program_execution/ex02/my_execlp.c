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
#include "tlpi_hdr.h"

extern char **environ;

/* int execve(const char *pathname, char *const argv[], char *const envp[]); */

int my_execlp(const char *filename, const char *arg, ... /* , (char *)NULL*/) {

	/* -------------------------------- */
	/* Step 0: Find the executable name */
	/* -------------------------------- */

	/* Track if we should use the PATH + filename or just filename */
	bool use_path = false;

	int pathname_len = strlen(filename);
	char path[pathname_len];
	strcpy(path, filename);

	char *file = strrchr(path, '/');
	if (file != NULL) {
		file++;
	} else {
		use_path = true;
		file = path;
	}
	printf("The file is: %s\n", file);
	printf("Use file is %d\n", use_path);


	/* --------------------------------- */
	/* Step 1: Build the argument vector */
	/* --------------------------------- */
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
	printf("arg size is %d\n", arg_size);

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

	/* ---------------------------------------------------------- */
	/* Step 2: Build the environment vector from the parent's env */
	/* ---------------------------------------------------------- */
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

	/* ---------------------------------------------------- */
	/* Step 3: Figure out the pathname and exec the process */
	/* ---------------------------------------------------- */

	if (use_path) {
		char *path_var = getenv("PATH");
		printf("The path is %s\n", path_var);
		const char s[2] = ":";
		char *token;

		/* get the first token */
		token = strtok(path_var, s);
		while( token != NULL ) {
			printf( "The token is %s\n", token );
			token = strtok(NULL, s);
			char *exec_file = malloc(strlen(token) + 1 + strlen(file));
			strcat(exec_file, token);
			strcat(exec_file, "/");
			strcat(exec_file, file);
			printf("The file to execute is: %s\n", exec_file);
			if (execve(exec_file, execve_argv, execve_envp) == -1) {
				printf("Had a failure, continuing\n");
			}
		}
	} else {
		execve(file, execve_argv, execve_envp);
	}

	return 0;
}

int main() {

	my_execlp("Tester", "asdf", "   fdsa","sde", (char *)NULL);
	my_execlp("/bin/Tester", "asdf", (char *)NULL);
	my_execlp("Tester", (char *)NULL);

	my_execlp("Tester", "asdf", "   fdsa","sde","   fdsa","sde", "   ert","rewq", (char *)NULL);
	int status;

	switch(fork()){
		case -1:
			errExit("fork");
		case 0:
			// parent
			wait(&status);

		default:
			my_execlp("./test.exe", "my arg", "another", (char *)NULL );
	}

	return(EXIT_SUCCESS);
}


// Notes

/* execlp() takes its environment from the parent
 * The specification of the executable would be PATH + filename
 * 
 * If the filename contains any slashes, you need to get the basename
 * Otherwise check that it exists in path
 */