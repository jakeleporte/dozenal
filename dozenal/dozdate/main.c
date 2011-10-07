/* +AMDG */

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define SIZE 256
#define MAXNUM 1000

int main(int argc, char *argv[])
{
	char c;
	int opterr = 0;
	char *date; char *format;
	char seps[SIZE][SIZE];
	char buffer[SIZE];
	char finans[MAXNUM] = "";
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
	tokenize(buffer);
	printf("%s\n",buffer);
	tgmify(buffer,thetime);
	printf("%s\n",buffer);
}

int tokenize(char *s)
{
	char *tok = NULL;
	int i; int j = 0;
	char *tokchars = " ,.:;\t\n\'\"!#$%^&*()%";
	char number[MAXNUM];
	char num[MAXNUM];

	strcpy(num,s);
	tok = strtok(num,tokchars);
	while (tok != NULL) {
		for (i=0; *(tok+i) != '\0'; ++i)
			number[i] = *(tok+i);
		number[i] = '\0';
		for (i=0; number[i] == '0'; ++i);
		if (isdigit(number[i]))
			dectodoz(number+i,(double) atoi(number));
		insert(number,s,tok);
		number[0] = '\0';
		tok = strtok(NULL,tokchars);
	}
	return 0;
}

int insert(char *number, char *theans, char *tok)
{
	int i,j;
	size_t len1, len2;
	char *spot;
	int newspot;

	len1 = strlen(tok);
	len2 = strlen(number);
	spot = strstr(theans,tok);
	newspot = theans - spot;
	if (len1 > len2) {
		memmove(number+(len1-len2),number,len2+1);
		for(i=0; i<(len1-len2); ++i)
			number[i] = '0';
		len2 = strlen(number);
	}
	memcpy(spot,number,len2);
	return 0;
}

int sectotim(char *s, struct tm *thetime)
{
	int tim;
	char tmp[SIZE];
	char tmp2[SIZE];
	int minutes;
	int seconds;

	strftime(tmp,SIZE,"%S",thetime);
	strftime(tmp2,SIZE,"%M",thetime);
	minutes = atoi(tmp2) * 60;
	seconds = atoi(tmp);
	tim = (minutes + seconds) * 5.76;
	dectodoz(s,(double)tim);
	return 0;
}

int tgmify(char *s, struct tm *thetime)
{
	int i,j;
	char tmp[SIZE];
	char tmp2[SIZE];
	size_t len;

	len = strlen(s);
	for (i=0; s[i] != '\0'; ++i) {
		if (s[i] == '@') {
			for (j=i; !isalpha(s[j]) && (j-i) <= 4; ++j);
			switch (s[j]) {
			case 't':
				sectotim(tmp,thetime);
				tgminsert(s,tmp,j-i);
				break;
			case 'H':
				strftime(tmp,SIZE,"%H",thetime);
				dectodoz(tmp,(double)atoi(tmp));
				tgminsert(s,tmp,j-i);
				break;
			case 'T':
				strftime(tmp,SIZE,"%H",thetime);
				dectodoz(tmp,(double)atoi(tmp));
				sectotim(tmp2,thetime);
				strcat(tmp,";");
				strcat(tmp,tmp2);
				tgminsert(s,tmp,j-i);
				break;
			default:
				fprintf(stderr,"dozdate:  no valid TGM "
				"conversion unit found\n");
				exit(1);
				break;
			}
		}
	}
	return 0;
}

int tgminsert(char *full, char *insert, int inspoint)
{
	size_t len, lenfull;
	int i, j;

	len = strlen(insert);
	lenfull = strlen(full);
	for (i=0; full[i] != '@'; ++i);
	memmove(full+i+len-inspoint,full+i+1,lenfull+1);
	memcpy(full+i,insert,len);
	return 0;
}
