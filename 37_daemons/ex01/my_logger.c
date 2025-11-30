/* Write a program (similar to logger(1)) that uses syslog(3) to write arbitrary 
 * messages to the system log file. As well as accepting a single command-line 
 * argument containing the message to be logged, the program should permit an 
 * option to specity the level of the message.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <syslog.h>

// extern char *optarg;

#define LEVEL_SIZE 16

void print_usage_message(FILE *fs, const char *prg_name) {
	char *usage_message = "Usage: %s [-l level] message\n\nThe following options are available for level argument:\nLOG_EMERG\nLOG_ALERT\nLOG_CRIT\nLOG_ERR\nLOG_WARNING\nLOG_NOTICE\nLOG_INFO\nLOG_DEBUG\n";

	fprintf(fs, usage_message, prg_name);
}

int convert_string_to_level(const char *level_str) {

	if (strcmp(level_str, "LOG_EMERG") == 0) {
		return LOG_EMERG;
	} else if (strcmp(level_str, "LOG_ALERT") == 0) {
		return LOG_ALERT;
	} else if (strcmp(level_str, "LOG_CRIT") == 0) {
		return LOG_CRIT;
	} else if (strcmp(level_str, "LOG_ERR") == 0) {
		return LOG_ERR;
	} else if (strcmp(level_str, "LOG_WARNING") == 0) {
		return LOG_WARNING;
	} else if (strcmp(level_str, "LOG_NOTICE") == 0) {
		return LOG_NOTICE;
	} else if (strcmp(level_str, "LOG_INFO") == 0) {
		return LOG_INFO;
	} else if (strcmp(level_str, "LOG_DEBUG") == 0) {
		return LOG_DEBUG;
	} else {
		return -1;
	}
}

int main (int argc, char *argv[]) {

	int option = LOG_PID | LOG_PERROR;
	int facility = LOG_LOCAL0;
	int opt, level_arg;
	char level[LEVEL_SIZE];
	memset(&level, 0, sizeof(level));

	while((opt = getopt(argc, argv, "l:")) != -1) {
		switch(opt) {
			case 'l':
				snprintf(level, LEVEL_SIZE - 1, optarg);
				break;
			default:
				print_usage_message(stderr, argv[0]);
				exit(EXIT_FAILURE);

		}
	}

	/* Some transformation & debugging */
	level_arg = convert_string_to_level(level);

	/* Perform the logging */
	openlog(NULL, option, facility);
	syslog(level_arg, argv[optind]);
	closelog();

	exit(EXIT_SUCCESS);
}
