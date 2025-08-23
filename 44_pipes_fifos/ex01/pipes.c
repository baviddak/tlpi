/* 
 * Write a program that uses two pipes to enable bidirectional communication 
 * between a parent and child process. The parent process should loop reading a 
 * block of text from standard input and use one of the pipes to send the text 
 * to the child, which converts it to uppercase and sends it back to the parent 
 * via the other pipe. The parent reads the data coming back from the child and 
 * echoes it on standard output before continuing around the loop once more.
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "tlpi_hdr.h"

#define BUFFER_MAX 120


void lower_to_upper(char *lower, char *upper, int size) {

    // int i;
    for (int i = 0; i < size; i++ ) {
        switch(lower[i]) {
            case
        }        


    }

}

int main () {

    int num_read;

    /* 0 is the read end; 1 is the write end */

    /* Create our pipe file descriptors */
    int parent_to_child_fd[2];
    int child_to_parent_fd[2];

    /* Create the pipes */

    if (pipe(parent_to_child_fd) == -1) {
        errExit("pipe");
    }

    if(pipe(child_to_parent_fd) == -1) {
        errExit("pipe");
    }

    /* Buffer for the text read in */
    char BUFFER[BUFFER_MAX];
    char BUFFER_UPPER_CASE[BUFFER_MAX];

    switch(fork()) {
        case -1:
            errExit("fork");
        case 0:

            /* Child process */
            if (close(parent_to_child_fd[1]) == -1) {
                // Close the write end of the parent to child pipe
                errExit("close");
            }
            if (close(child_to_parent_fd[0] == -1)) {
                // Close the read end of the child to parent pipe
                errExit("close");
            }

            /* Close the*/

        case 1:

            /* Parent process */
            if (close(parent_to_child_fd[0]) == -1) {
                // Close the read end of the parent to child pipe
                errExit("close");
            }
            if (close(child_to_parent_fd[1] == -1)) {
                // Close the write end of the child to parent pipe
                errExit("close");
            }

            // Read from stdin - pass to the child process
            for(;;) {
                num_read = read(STDIN_FILENO, BUFFER, BUFFER_MAX);



                // Write to the child
                if (num_read == -1 ) {
                    errExit("read");
                }
                if (num_read == 0) {
                    break;
                }
                if (write(parent_to_child_fd[1]), BUFFER, BUFFER_MAX) == -1) {
                    errExit("write")
                }

                // Read back from the child, print to STDOUT
                if (read(child_to_parent_fd[0]), BUFFER, BUFFER_MAX) == -1) {
                    errExit("write")
                }





            }

    }

}