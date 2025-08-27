/* 
 * Write a program that uses two pipes to enable bidirectional communication 
 * between a parent and child process. The parent process should loop reading a 
 * block of text from standard input and use one of the pipes to send the text 
 * to the child, which converts it to uppercase and sends it back to the parent 
 * via the other pipe. The parent reads the data coming back from the child and 
 * echoes it on standard output before continuing around the loop once more.
 */

/*
 * Warning: this is the worst code every literally!
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "tlpi_hdr.h"

#define BUFFER_MAX 120

char upper_case (char input)
 {
    switch(input){
        case 'a':
            return 'A';
        case 'b':
            return 'B';
        case 'c':
            return 'C';
        case 'd':
            return 'D';
        case 'e':
            return 'E';
        case 'f':
            return 'F';
        case 'g':
            return 'G';
        case 'h':
            return 'H';
        case 'i':
            return 'I';
        case 'j':
            return 'J';
        case 'k':
            return 'K';
        case 'l':
            return 'L';
        case 'm':
            return 'M';
        case 'n':
            return 'N';
        case 'o':
            return 'O';
        case 'p':
            return 'P';
        case 'q':
            return 'Q';
        case 'r':
            return 'R';
        case 's':
            return 'S';
        case 't':
            return 'T';
        case 'u':
            return 'U';
        case 'v':
            return 'V';
        case 'w':
            return 'W';
        case 'x':
            return 'X';
        case 'y':
            return 'Y';
        case 'z':
            return 'Z';
        default:
            return input;
    }
 }

void lower_to_upper(char *lower, char *upper, int size) {
    int i;

    for (i = 0; i < size; i++ ) {
        upper[i] = upper_case(lower[i]);
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

            // this does not have to be specific to the child - the parent and 
            // child have their own copy of local variables but can share file
            // descriptors
            // int num_read_child;
            printf("Entered the child process\n");

            /* Child process */
            if (close(parent_to_child_fd[1]) == -1) {
                // Close the write end of the parent to child pipe
                errExit("close");
            }
            printf("Successfully closed file descriptor 1 in child process\n");
            if (close(child_to_parent_fd[0]) == -1) {
                // Close the read end of the child to parent pipe
                errExit("close");
            }

            printf("Successfully closed file descriptor 2 in child process\n");
            
            for (;;) {
                // Read from the appropriate pipe end 
                num_read = read(parent_to_child_fd[0], BUFFER, BUFFER_MAX);

                if ( num_read == -1 ) {
                    errExit("read");
                }
                if ( num_read == 0 ) {
                    break;
                }

                printf("Read some data in the child\n");

                // Convert to upper case
                lower_to_upper(BUFFER, BUFFER_UPPER_CASE, BUFFER_MAX);


                if (write(child_to_parent_fd[1], BUFFER_UPPER_CASE, BUFFER_MAX) == -1) {
                    errExit("write");
                }

            }

        case 1:

            // int num_read_parent;
            printf("Entered the parent process\n");

            /* Parent process */
            if (close(parent_to_child_fd[0]) == -1) {
                // Close the read end of the parent to child pipe
                errExit("close");
            }

            printf("Successfully closed file descriptor 1 in parent process\n");
            if (close(child_to_parent_fd[1]) == -1) {
                // Close the write end of the child to parent pipe
                errExit("close");
            }

            printf("Successfully closed file descriptor 2 in parent process\n");

            // Read from stdin - pass to the child process
            for(;;) {
                num_read = read(STDIN_FILENO, BUFFER, BUFFER_MAX);

                // Write to the child
                if ( num_read == -1 ) {
                    errExit("read");
                }
                if ( num_read == 0 ) {
                    break;
                }
                
                printf("Read some data in the parent\n");

                if (write(parent_to_child_fd[1], BUFFER, BUFFER_MAX) == -1) {
                    errExit("write - yo");
                }

                // Read back from the child, print to STDOUT
                if (read(child_to_parent_fd[0], BUFFER, BUFFER_MAX) == -1) {
                    errExit("write");
                }

                printf("%s\n", BUFFER);

            }
    }
}