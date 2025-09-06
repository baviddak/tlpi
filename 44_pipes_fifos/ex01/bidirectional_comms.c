/* Write a program that uses two pipes to enable bidirectional communication
 * between a parent and child process.
 */

#include <unistd.h>

#include "tlpi_hdr.h"

#define BUFFER_MAX 100

void convert_to_lower(char source[], char destination[], int size);

int main() {
  /* create a buffer to store the read in bytes */
  char buffer[BUFFER_MAX];
  char alt_buffer[BUFFER_MAX];

  /* 0 is the read end, 1 is the write end */
  int parent_to_child[2];
  int child_to_parent[2];

  ssize_t num_read;
  ssize_t num_written;

  if (pipe(parent_to_child) == -1) {
    errExit("pipe");
  }

  if (pipe(child_to_parent) == -1) {
    errExit("pipe");
  }

  switch (fork()) {
    case -1:
      /* Error */
      errExit("fork");
    case 0:
      /* Child process */

      if (close(parent_to_child[1]) == -1) {
        errExit("close");
      }
      if (close(child_to_parent[0]) == -1) {
        errExit("close");
      }

      /* Continuously read from the pipe, convert and send back the bits */
      for (;;) {
        num_read = read(parent_to_child[0], buffer, BUFFER_MAX);

        if (num_read == -1) {
          errExit("read");
        }

        convert_to_lower(buffer, alt_buffer, num_read);

        num_written = write(child_to_parent[1], alt_buffer, BUFFER_MAX);
        if (num_written == -1) {
          errExit("write");
        }
      }

      break;
    default:
      /* Parent process */
      if (close(parent_to_child[0]) == -1) {
        errExit("close");
      }
      if (close(child_to_parent[1]) == -1) {
        errExit("close");
      }

      /* Continuously read in from stdin, write to the pipe */
      for (;;) {
        /* Read in, pass the data to the child throught the pipe */

        num_read = read(STDIN_FILENO, buffer, BUFFER_MAX);

        if (num_read == -1) {
          errExit("read");
        }
        if (num_read == 0) {
          break;
        }

        num_written = write(parent_to_child[1], buffer, BUFFER_MAX);

        if (num_written == -1) {
          errExit("write");
        }

        /* Read back from child, pass the data to STDOUT */
        num_read = read(child_to_parent[0], buffer, BUFFER_MAX);

        if (num_read == -1) {
          errExit("read");
        }

        num_written = write(STDOUT_FILENO, buffer, BUFFER_MAX);

        if (num_written == -1) {
          errExit("write");
        }
      }
      break;
  }
}

void convert_to_lower(char source[], char destination[], int size) {
  int i = 0;

  for (i = 0; i < size; i++) {
    switch (source[i]) {
      case 'a':
        destination[i] = 'A';
        break;
      case 'b':
        destination[i] = 'B';
        break;

      case 'c':
        destination[i] = 'C';
        break;

      case 'd':
        destination[i] = 'D';
        break;

      case 'e':
        destination[i] = 'E';
        break;

      case 'f':
        destination[i] = 'F';
        break;

      case 'g':
        destination[i] = 'G';
        break;

      case 'h':
        destination[i] = 'H';
        break;

      case 'i':
        destination[i] = 'I';
        break;

      case 'k':
        destination[i] = 'K';
        break;

      case 'l':
        destination[i] = 'L';
        break;

      case 'm':
        destination[i] = 'M';
        break;

      case 'n':
        destination[i] = 'N';
        break;

      case 'o':
        destination[i] = 'O';
        break;

      case 'p':
        destination[i] = 'P';
        break;
      case 'q':
        destination[i] = 'Q';
        break;

      case 'r':
        destination[i] = 'R';
        break;

      case 's':
        destination[i] = 'S';
        break;

      case 't':
        destination[i] = 'T';
        break;

      case 'u':
        destination[i] = 'U';
        break;

      case 'v':
        destination[i] = 'V';
        break;

      case 'w':
        destination[i] = 'W';
        break;

      case 'x':
        destination[i] = 'X';
        break;

      case 'y':
        destination[i] = 'Y';
        break;

      case 'z':
        destination[i] = 'Z';
        break;

      default:
        destination[i] = source[i];
        break;
    }
  }
}