/* Write a program to demonstrate that after a vfork(), the child process can 
 * close a file descriptor (e.g. descriptor 0) without affecting the 
 * corresponding file descriptor in the parent.
 */

/* Usage: ./vfork*/

#include <unistd.h>
#include <stdlib.h>
#include "tlpi_hdr.h"

#define BUF_SIZE 20

int main() {

    printf("The stdout fd is: %d\n", STDOUT_FILENO);
    printf("The stdin fd is: %d\n", STDIN_FILENO);
    printf("The stderr fd is: %d\n", STDERR_FILENO);

    char buf[BUF_SIZE];

    switch(vfork()) {
        case -1:
            errExit("vfork");
        case 0:
            // The child process - close the fd 0
            _exit(close(0));
        default:
            // The parent - check that fd 0 is still open 
            sleep(5);
            printf("Please enter a few characters: \n");
            if (read(0, buf, BUF_SIZE*sizeof(char)) == -1) {
                printf("There was an issue reading!");
            } else {
                printf("The fd 0 is still open.\n");
                printf("Buffer is %s\n", buf);
            }
    }

    return(EXIT_SUCCESS);
}