#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define PORT_NUM "50005"
#define HOST "192.168.0.16"
#define INT_LEN 48

int main() {

	/* Set some parameters */
	int sockfd;
	char send_buffer[INT_LEN];
	memset(&send_buffer, 0, INT_LEN);
	snprintf(send_buffer, INT_LEN - 1, "Here is some info and data from client\n");

	/* socket, connect, write */
	struct addrinfo hints, *rp, *result;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_flags = AI_NUMERICSERV;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;
	hints.ai_addr = NULL;
	hints.ai_canonname = NULL;
	hints.ai_next = NULL;

	int s = getaddrinfo(HOST, PORT_NUM, &hints, &result);
	if (s != 0) {
		fprintf(stderr, "getaddrinfo failed.\n");
		fprintf(stderr, "s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}


	socklen_t addrlen = sizeof(struct sockaddr_in);

	for (rp = result; rp != NULL; rp = rp->ai_next) {
		/* Try to connect on the socket */

		if ((sockfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol)) == -1) {
			fprintf(stderr, "Error in creating the socket.\n");
			fprintf(stderr, "%s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		/* We have successfully created the socket, try to connect */

		if (connect(sockfd, (struct sockaddr *)rp->ai_addr, addrlen) == -1) {
			fprintf(stderr, "Error in connecting to peer socket.\n");
			fprintf(stderr, "%s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		break;
		
	}
	

	if (write(sockfd, send_buffer, INT_LEN) < 0) {
		fprintf(stderr, "Error in writing to the socket\n");
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}


	exit(EXIT_SUCCESS);
}
