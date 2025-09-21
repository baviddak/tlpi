/* writer.c*/

/* 
 * This program is used to test my implementation of popen.
 * This program simply writes some random text to it's stdout
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* stdout is a file pointer that can be used */

int main() {

	char *write_string = "This is some text that I am writing!!\n";

	fwrite(write_string, sizeof(char), strlen(write_string), stdout);

	return 0;
}
