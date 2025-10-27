/* Simple server program using UNIX domain stream sockets to 
 * return an incremented number.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>

#define BUF_SIZE 128

#include "common.h"

int main(int argc, char *argv[]) {

	struct sockaddr_un addr, cl_addr;
	int sockfd;
	int cl_sockfd;
	char buf[BUF_SIZE];
	socklen_t sl;


	/* Check if the file exists, using fstat? */
	if (remove(SOCK_FILEPATH) == -1) {
		if (errno != ENOENT) {
			fprintf(stderr, "Unable to remove pre-existing socket file.\n");
			exit(EXIT_FAILURE);
		}
	}

	if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		fprintf(stderr, "Error creating new socket");
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	memset(&addr, 0, sizeof(struct sockaddr_un));

	/* Set some socket address parameters */
	addr.sun_family = AF_UNIX;
	snprintf(addr.sun_path, sizeof(addr.sun_path) - 1, SOCK_FILEPATH);

	/* Bind the socket with the address */
	if (bind(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1 ) {
		fprintf(stderr, "Error binding socket.\n");
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if (listen(sockfd, 5) == -1) {
		fprintf(stderr, "Error in the listen call.\n");
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* Read and print to STDOUT */
	if ((cl_sockfd = accept(sockfd, (struct sockaddr *)&cl_addr, &sl)) == -1) {
		fprintf(stderr, "Error accepting the connection.\n");
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if (read(cl_sockfd, buf, BUF_SIZE) > 0) {
		fprintf(stdout, "We read this from the client: %s\n", buf);
	}

	exit(EXIT_SUCCESS);
}
