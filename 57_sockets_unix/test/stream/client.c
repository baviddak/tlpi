/* Simple client to send a stream socket message in the UNIX domain. */
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>

#include "common.h"

#define BUF_SIZE 128

int main() {

	/* 
	 * socket()
	 * connect()
	 * write()
	 * close()
	 */

	int sockfd;
	struct sockaddr_un addr;
	char buf[BUF_SIZE];
	snprintf(buf, sizeof(buf) - 1, "Yo this is a message!!");

	if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		fprintf(stderr, "Error creating socket\n");
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
		
	}

	memset(&addr, 0, sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	snprintf(addr.sun_path, sizeof(addr.sun_path) - 1, SOCK_FILEPATH);

	if (connect(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1){
		fprintf(stderr, "Error connecting to the socket\n");
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	write(sockfd, buf, sizeof(buf) - 1);
	
	exit(EXIT_SUCCESS);
}
