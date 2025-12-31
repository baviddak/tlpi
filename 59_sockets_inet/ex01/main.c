#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define FILESZ_MAX 2048
#define LINE_MAX 512

/* Structure definitions */
struct rlbuf {
	int pointer;
	char content_buf[FILESZ_MAX];
};

/* Statically allocated data */
static char line_buf[LINE_MAX];

/* Function prototypes */
int readline_buf_init(int, struct rlbuf *);
char *readline_buf(struct rlbuf *);

/* main */
int main ( int argc, char *argv[] ) {

	/* */
	if ( argc != 2 || strcmp(argv[1], "--help") == 0 ) {
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	struct rlbuf newbuf;
	const char *pathname = argv[1];
	int fd = open(pathname, O_RDONLY);

	/* */
	if ( readline_buf_init(fd, &newbuf) != 0 ) {
		fprintf(stderr, "Error in readline_buf_init()\n");
		exit(EXIT_FAILURE);
	}

	fprintf(stdout, "Line 1: %s\n", readline_buf(&newbuf));
	fprintf(stdout, "Line 2: %s\n", readline_buf(&newbuf));
	fprintf(stdout, "Line 3: %s\n", readline_buf(&newbuf));
	fprintf(stdout, "Line 4: %s\n", readline_buf(&newbuf));
	fprintf(stdout, "Line 5: %s\n", readline_buf(&newbuf));

	exit(EXIT_SUCCESS);
}

int readline_buf_init ( int fd, struct rlbuf *rlb ) {
	
	/* Initialize the data structure */
	rlb->pointer = 0;
	memset(rlb->content_buf, 0, sizeof(rlb->content_buf));
	memset(line_buf, 0, sizeof(line_buf));

	struct stat sb;
	if ( fstat(fd, &sb) != 0 ) {
		/* fstat() failed */
		return -1;
	}

	/* Fail if the file is bigger than our max buffer size */
	int file_sz = sb.st_size;
	if ( file_sz > FILESZ_MAX ) {
		return -1;
	}

	/* */
	if ( read(fd, rlb->content_buf, sizeof(rlb->content_buf)) <= 0 ) {
		return -1;
	}

	return 0;
}

char *readline_buf( struct rlbuf *rlb ) { 

	/* reset the line buffer*/
	memset(line_buf, 0, sizeof(line_buf));

	int line_buf_p = 0;

	for (int i = rlb->pointer; rlb->content_buf[i] != '\n' && i < sizeof(rlb->content_buf); i++ ) {
		line_buf[line_buf_p] = rlb->content_buf[i];
		line_buf_p++;
	}

	if ( rlb->pointer + line_buf_p < sizeof(rlb->content_buf) ) {
		rlb->pointer = rlb->pointer + line_buf_p + 1;
	} else {
		rlb->pointer = 0;
	}

	return line_buf;
}

