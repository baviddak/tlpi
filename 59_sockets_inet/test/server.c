/* This program is a stream socket server in the internet domain.
 * It should recieve connections from a client program 
 * on port 50005.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>

#define PORT_NUM "50005"
#define INT_LEN 48
#define HOST "192.168.0.16"

int main () {

	/* Find an address to bind to our socket */
	struct addrinfo hints;
	struct addrinfo *result, *rp;
	struct sockaddr_in claddr;
	char recv_buffer[INT_LEN];
	ssize_t num_read;
	int s, sfd, cfd;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags =  AI_NUMERICSERV;

	if ((s = getaddrinfo(HOST, PORT_NUM, &hints, &result)) != 0) {
		fprintf(stderr, "getaddrinfo failed: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}

	for (rp = result; rp != NULL; rp = rp->ai_next) {

		/* Try to create a new socket with the result */
		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

		if (sfd == -1){
			/* Try the next one */
			continue;
		}

		/* If we can successfully bind, exit the loop */
		if (bind(sfd, rp->ai_addr, sizeof(struct sockaddr_in)) == 0){
			fprintf(stdout, "Successfully found and binded to a socket!\n");
			break;
		}

		/* Successfully created the socket, but could not bind, so we close */
		close(sfd);

	}

	/* The search result, no longer needed */
	freeaddrinfo(result);

	if (rp == NULL) {
		fprintf(stderr, "No address succeeded.\n");
		exit(EXIT_FAILURE);
	}

	if (listen(sfd, 10) == -1) {
		fprintf(stderr, "Failed to set the socket as a listener.\n");
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}


	socklen_t addrlen = sizeof(struct sockaddr_in);

	for (;;) {
		cfd = accept(sfd, (struct sockaddr *)&claddr, &addrlen);
		if (cfd == -1) {
			fprintf(stderr, "Error in accepting the peer socket.\n");
			fprintf(stderr, "%s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		if ((num_read = read(cfd, recv_buffer, INT_LEN - 1)) < 0){
			fprintf(stderr, "Error in reading the thing.\n");
			fprintf(stderr, "%s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		puts(recv_buffer);
		break;

	}

	exit(EXIT_SUCCESS);
	
}
