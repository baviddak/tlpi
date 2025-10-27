/* Simple server program to recieve a datagram message and print
 * to standard out.
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

#include "common.h"

int main () {

	int sfd, cl_sfd;
	struct sockaddr_un addr, cl_addr;
	char buf[BUF_SIZE];
	ssize_t bytes_read;

	/* Create the socket */
	if ((sfd = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1) {
		fprintf(stderr, "Error creating the socket\n");
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
       	}	

	/* Set the contents of the socket address structure. */
	memset(&addr, 0, sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	snprintf(addr.sun_path, sizeof(addr.sun_path) - 1, SOCKET_FILE);

	/* Remove the socket file. */
	if (remove(SOCKET_FILE) == -1) {
		if (errno != ENOENT) {
			fprintf(stderr, "Error removing the socket file.\n");
			exit(EXIT_FAILURE);
		}
	}

	/* Bind the socket to the address. */
	if (bind(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1) {
		fprintf(stderr, "Error binding the socket to the address\n");
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* Recieve a message from the client, then print to standard out */
	if ((bytes_read = recv(sfd, buf, BUF_SIZE, MSG_WAITALL)) == -1) {
		fprintf(stderr, "Error in reading from the socket.\n");
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	fprintf(stdout, "Successfully read %d bytes from the socket. Message %s\n", bytes_read, buf);

	exit(EXIT_SUCCESS);

}

