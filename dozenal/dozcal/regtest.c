/* +AMDG */

#include<stdio.h>
#include<regex.h>

int main()
{
	regex_t regone; char *patone = "hello|\\(.*\\)|";
	char *s = "hello|whatup|";
	regmatch_t pmatch[2]; size_t nmatch = 2;
	int result;

	regcomp(&regone,patone,0);
	result = regexec(&regone,s,nmatch,pmatch,0);
	if (result == 0)
		printf("Hurray!\n");
	printf("|%.*s|\n",pmatch[0].rm_eo - pmatch[0].rm_so);
	return 0;
}
