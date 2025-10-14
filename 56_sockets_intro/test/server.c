#include "common.h"

#define BACKLOG 5

int main() {

	// Initialize our data structures
	struct sockaddr_un addr;
	int server_fd, client_fd;
	ssize_t num_read;
	char buf[BUF_SIZE];


	// Call #1: socket()
	server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (server_fd == -1) {
		return -1;
	}

	// Why do we need this ?? 
	if (remove(SOCK_PATH) == -1 && errno != ENOENT) {
		return -1;
	}

	memset(&addr, 0, sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path) - 1);
	
	// Call #2: bind()
	if (bind(server_fd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1) {
		return -1;
	}


	// Call #3: listen()
	if (listen(server_fd, BACKLOG) == -1){
		return -1;
	}


	for (;;){

		client_fd = accept(server_fd, NULL, NULL);
		if (client_fd == -1) {
			return -1;
		}

		while ((num_read = read(client_fd, buf, BUF_SIZE)) > 0) {

			if (write(STDOUT_FILENO, buf, num_read) != num_read) {
				return -1;
			}
		}

		if (num_read == -1) {
			return -1;
		}

		if (close(client_fd) == -1) {
			return -1;
		}
	}

	return 0;
}
