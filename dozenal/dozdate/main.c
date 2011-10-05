/* +AMDG */

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SIZE 256

int main(int argc, char *argv[])
{
	char c;
	int opterr = 0;
	char *date; char *format;
	char *today = "today";
	char *now = "now";
	char buffer[SIZE];
	struct tm *thetime;
	time_t curtime;
	
	curtime = time(NULL);
	thetime = localtime(&curtime);

	while ((c = getopt(argc,argv,"vud:f:")) != -1) {
		switch (c) {
		case 'u':
			thetime = gmtime(&curtime);
			break;
		case 'd':
			date = optarg;
			break;
		case 'f':
			format = optarg;
			break;
		case 'v':
			printf("dozdate v3.1\n");
			printf("Copyright (C) 2011  Donald P. Goodman III\n");
			printf("License GPLv3+:  GNU GPL version 3 or "
			"later <http://gnu.org/licenses/gpl.html>\n");
			printf("This is free software:  you are free "
			"to change and redistribute it.  There is NO "
			"WARRANTY, to the extent permitted by law.\n");
			return 0;
			break;
		case '?':
			return 1;
			break;
		default:
			break;
		}
	}

	strftime(buffer,SIZE,format,thetime);
	printf("%s\n",buffer);
}
