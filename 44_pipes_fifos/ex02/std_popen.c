#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () { 


	char *buffer = "This is the string that I would like to write to the thing!!\nHey what a cool thing\n";

	FILE *fp = popen("./reader", "w");
	size_t num_written;

	num_written = fwrite(buffer, sizeof(char), strlen(buffer) + 1, fp);



	return 0;
}
