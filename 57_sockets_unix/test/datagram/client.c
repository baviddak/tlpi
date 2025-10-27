/* Simple client program to send a datagram */

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <unistd.h>

#include "common.h"

int main () {

	int sfd, cl_sfd;
	struct sockaddr_un addr, cl_addr;
	char buf[BUF_SIZE];
	int flags = 0;
	ssize_t bytes_read, bytes_sent;

	/* Create the socket */
	if ((sfd = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1) {
		fprintf(stderr, "Error creating the socket\n");
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
       	}	

	/* Set the contents of the socket address structure. */
	memset(&addr, 0, sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	snprintf(addr.sun_path, sizeof(addr.sun_path) - 1, "/tmp/socket_client_file");


	/* Copy the contents of STDIN to the buffer */
	if ((bytes_read = read(STDIN_FILENO, buf, BUF_SIZE)) == -1) {
		fprintf(stderr, "Error in reading the contents of STDIN.\n");
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}


	/* Remove the socket file if it exists. */
	//if (remove(SOCKET_FILE) == -1) {
	//	if (errno != ENOENT) {
	//		fprintf(stderr, "Error removing existing socket file\n");
	//		exit(EXIT_FAILURE);
	//	}
	//}


	/* Bind the socket to the address. */
	if (bind(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1) {
		fprintf(stderr, "Error binding the socket to the address\n");
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* Write the buffer to the socket */
	if (send(sfd, buf, BUF_SIZE, flags) == -1) {
		fprintf(stderr, "Error in sending data to the socket.\n");
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	// fprintf(stdout, "Successfully read %d bytes from the socket. Message %s\n", bytes_read, buf);

	exit(EXIT_SUCCESS);

}

