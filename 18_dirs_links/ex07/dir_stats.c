/* Write a program that uses nftw() to traverse a directory tree and finishes by 
 * printing out counts and percentages of the various types (regualar, 
 * directory, symbolic link, and so on) of files in the tree.
 */

/* Usage: ./dir_stats.exe <dirpath> */

#define _XOPEN_SOURCE 600
#include <ftw.h>
#include <sys/stat.h>

#include "tlpi_hdr.h"

struct file_types {
	int reg_count;	/* Regular file count */
	int dir_count;	/* Directory count */
	int char_count;	/* Character device count */
	int blk_count;	/* Block device count */
	int fifo_count;	/* FIFO or pipe count */
	int sock_count;	/* Socket count */
	int lnk_count;	/* Symbolic link count */
	int total;		/* total file count */
};

/* Global file_types struct */
static struct file_types dir_stat;

void print_stats() {
	// print the statistics in a pretty way

	double reg_p = ((double)dir_stat.reg_count / (double)dir_stat.total)*100;
	double dir_p = ((double)dir_stat.dir_count / (double)dir_stat.total)*100; 
	double char_p = ((double)dir_stat.char_count / (double)dir_stat.total)*100; 
	double blk_p = ((double)dir_stat.blk_count / (double)dir_stat.total)*100; 
	double fifo_p = ((double)dir_stat.fifo_count / (double)dir_stat.total)*100; 
	double sock_p = ((double)dir_stat.sock_count / (double)dir_stat.total)*100; 
	double lnk_p = ((double)dir_stat.lnk_count / (double)dir_stat.total)*100; 


	printf("Regular file count: %d (%.2f percent)\n",dir_stat.reg_count, reg_p);
	printf("Directory count: %d (%.2f percent)\n",dir_stat.dir_count, dir_p);
	printf("Char device count: %d (%.2f percent)\n",dir_stat.char_count, char_p);
	printf("Block device count: %d (%.2f percent)\n",dir_stat.blk_count, blk_p);
	printf("FIFO or pipe count: %d (%.2f percent)\n",dir_stat.fifo_count, fifo_p);
	printf("Socket count: %d (%.2f percent)\n",dir_stat.sock_count, sock_p);
	printf("Symbolic link count: %d (%.2f percent)\n",dir_stat.lnk_count, lnk_p);

}

static int 
dir_stats(const char *pathname, const struct stat *sbuf, int type, struct FTW *stwb) {

	// increment the count for the file type
	switch (sbuf->st_mode & S_IFMT) {
		case S_IFREG:
			dir_stat.reg_count += 1;
			dir_stat.total += 1;
			break;
		case S_IFDIR:
			dir_stat.dir_count += 1;
			dir_stat.total += 1;
			break;
		case S_IFCHR:
			dir_stat.char_count += 1;
			dir_stat.total += 1;
			break;
		case S_IFBLK:
			dir_stat.blk_count += 1;
			dir_stat.total += 1;
			break;
		case S_IFLNK:
			dir_stat.lnk_count += 1;
			dir_stat.total += 1;
			break;
		case S_IFIFO:
			dir_stat.fifo_count += 1;
			dir_stat.total += 1;
			break;
		case S_IFSOCK:
			dir_stat.sock_count += 1;
			dir_stat.total += 1;
			break;
		default:
			printf("Unrecognized type.\n");
	}

	return 0;
}

int main (int argc, char *argv[]) {

	// validate command
	if (argc != 2) {
		usageErr("%s <dirpath>", argv[0]);
	}

	char *dirpath = argv[1];

	// initalize the values to 0 for each type
	dir_stat.reg_count = 0;
	dir_stat.dir_count = 0;
	dir_stat.char_count = 0;
	dir_stat.blk_count = 0;
	dir_stat.fifo_count = 0;
	dir_stat.sock_count = 0;
	dir_stat.lnk_count = 0;

	int typeflags = FTW_PHYS; 
	// struct FTW ftwbuf;

	// call the nftw function
	if (nftw(dirpath, dir_stats, 3, typeflags) == -1) {
		exit(EXIT_FAILURE);
	}

	// print the statistics
	print_stats();

	return(EXIT_SUCCESS);
}