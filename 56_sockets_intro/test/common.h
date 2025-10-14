#include <sys/un.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#define SOCK_PATH "/tmp/socket_path"

#define BUF_SIZE 128
