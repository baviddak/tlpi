/* Simple client program to send a datagram */

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <unistd.h>

#include "common.h"

int main () {

	int sfd;
	struct sockaddr_un addr, cl_addr;
	char buf[BUF_SIZE];
	int flags = 0;
	ssize_t bytes_read;

	/* Create a socket file name with the PID */ 
	char cl_socket_file[BUF_SIZE];
	memset(cl_socket_file, 0, sizeof(cl_socket_file));
	snprintf(cl_socket_file, sizeof(cl_socket_file) - 1, "/tmp/socket_cl_file.%ld", (long) getpid());

	/* Create the socket */
	if ((sfd = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1) {
		fprintf(stderr, "Error creating the socket\n");
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
       	}	

	/* Set the contents of the socket address structure. */
	memset(&cl_addr, 0, sizeof(struct sockaddr_un));
	cl_addr.sun_family = AF_UNIX;
	snprintf(cl_addr.sun_path, sizeof(cl_addr.sun_path) - 1, cl_socket_file);

	/* Copy the contents of STDIN to the buffer */
	if ((bytes_read = read(STDIN_FILENO, buf, BUF_SIZE)) == -1) {
		fprintf(stderr, "Error in reading the contents of STDIN.\n");
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}


	/* Bind the socket to the address. */
	if (bind(sfd, (struct sockaddr *)&cl_addr, sizeof(struct sockaddr_un)) == -1) {
		fprintf(stderr, "Error binding the socket to the address\n");
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}


	memset(&addr, 0, sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	snprintf(addr.sun_path, sizeof(addr.sun_path) - 1, SOCKET_FILE);


	/* Write the buffer to the socket */
	if (sendto(sfd, buf, BUF_SIZE, flags, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1) {
		fprintf(stderr, "Error in sending data to the socket.\n");
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	// fprintf(stdout, "Successfully read %d bytes from the socket. Message %s\n", bytes_read, buf);

	if (remove(cl_socket_file) == -1) {
		fprintf(stderr, "Error removing the client socket file.\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);

}

