/* +AMDG */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TRUE	0
#define FALSE	1

#define RIGHT	0
#define LEFT	1

int getprec(char *s);
int getassoc(char *s);

struct opprec {
	char operator;
	int precedence;
	int assoc;
} allops[] = {
	'^',4,RIGHT,
	'%',3,LEFT,
	'*',3,LEFT,
	'/',3,LEFT,
	'+',2,LEFT,
	'-',2,LEFT
};
int numops = 5;

int shunt(char *postfix, char *infix)
{
	int i; int j;
	char *token;
	char delim[2] = " ";
	char outstack[256][16]; int outind = 0;
	char opstack[256][16]; int opind = 0;
	char holder[16];

	token = strtok(infix,delim);
	while (token != NULL) {
		if (isnumber(token) == TRUE) {
			xpush(token,outstack,&outind);
		} else if (isfunction(token) == TRUE) {
			xpush(token,opstack,&opind);
		} else if (!strcmp(token,",")) {
		} else if (!strcmp(token,"!")) {
			xpush(token,outstack,&outind);
		} else if (isoperator(token) == TRUE) {
			if (opind > 0) {
				if (isoperator(opstack[opind-1]) == TRUE) {
					if (getassoc(token) == LEFT) {
						if (getprec(token) <= getprec(opstack[opind-1])) {
							xpop(holder,opstack,&opind);
							xpush(holder,outstack,&outind);
						}
					} else if (getassoc(token) == RIGHT) {
						if (getprec(token) < getprec(opstack[opind-1])) {
							xpop(holder,opstack,&opind);
							xpush(holder,outstack,&outind);
							holder[0] = '\0';
						}
					}
				}
			}
			xpush(token,opstack,&opind);
		} else if (isleftparen(token) == TRUE) {
			if (opind == 0) {
				xpush(token,opstack,&opind);
			} else if (isfunction(opstack[opind-1]) == FALSE) {
				xpush(token,opstack,&opind);
			}
		} else if (isrightparen(token) == TRUE) {
			xpop(holder,opstack,&opind);
			while ((!strstr(holder,"(")) && (isfunction(holder) == FALSE)) {
				xpush(holder,outstack,&outind);
				holder[0] = '\0';
				xpop(holder,opstack,&opind);
				if (opind < 0) {
					fprintf(stderr,"error:  mismatched parens\n");
				}
			}
			if (isfunction(holder) == TRUE) {
				xpush(holder,outstack,&outind);
			}
			holder[0] = '\0';
		} else {
			holder[0] = '\0';
			xpop(holder,opstack,&opind);
			xpush(holder,outstack,&outind);
		}
		token = strtok(NULL,delim);
	}
	while (opind > 0) {
		holder[0] = '\0';
		xpop(holder,opstack,&opind);
		xpush(holder,outstack,&outind);
	}
/* test it all out */
/*	for (i = 0; i < outind; ++i) {
		printf("OUTPUT STACK:  %s\n",outstack[i]);
	}
	for (i = 0; i < opind; ++i) {
		printf("OPERATOR STACK:  %s\n",opstack[i]);
	}*/
	postfix[0] = '\0';
	for (i = 0; i < outind; ++i) {
		strcat(postfix,outstack[i]);
		strcat(postfix," ");
	}
//	printf("%s\n",postfix);
	return 0;
}

int xpush(char *s, char stack[][16], int *index)
{
	strcpy(stack[*index],s);
	++(*index);
}

int xpop(char *holder, char stack[][16], int *index)
{
	--(*index);
	strcpy(holder,stack[*index]);
}

int isnumber(char *s)
{
	if ((*s == '0') || (*s == '1') || (*s == '2') || (*s == '3') ||
	(*s == '4') || (*s == '5') || (*s == '6') || (*s == '7') ||
	(*s == '8') || (*s == '9') || (*s == 'X') || (*s == 'E')) {
		return TRUE;
	}
	return FALSE;
}

int isoperator(char *s)
{
	char c;

	c = s[0];
	if ((c == '+') || (c == '-') || (c == '*') || (c == '/') ||
	(c == '^')) {
		return TRUE;
	}
	return FALSE;
}

int getprec(char *s)
{
	int i;
	char c;

	c = s[0];
	for (i = 0; i <= numops;  ++i) {
		if (allops[i].operator == c)
			return allops[i].precedence;
	}
}

int getassoc(char *s)
{
	int i;
	char c;

	c = s[0];
	for (i = 0; i <= numops;  ++i) {
		if (allops[i].operator == c)
			return allops[i].assoc;
	}
}

int isleftparen(char *s)
{
	char c;

	c = s[0];
	if (c == '(')
		return TRUE;
	return FALSE;
}

int isrightparen(char *s)
{
	char c;

	c = s[0];
	if (c == ')')
		return TRUE;
	return FALSE;
}

int isfunction(char *s)
{
	if (!strcmp(s,"sin"))
		return TRUE;
	if (!strcmp(s,"cos"))
		return TRUE;
	if (!strcmp(s,"tan"))
		return TRUE;
	if (!strcmp(s,"asin"))
		return TRUE;
	if (!strcmp(s,"acos"))
		return TRUE;
	if (!strcmp(s,"atan"))
		return TRUE;
	if (!strcmp(s,"atan2"))
		return TRUE;
	if (!strcmp(s,"sinh"))
		return TRUE;
	if (!strcmp(s,"cosh"))
		return TRUE;
	if (!strcmp(s,"tanh"))
		return TRUE;
	if (!strcmp(s,"log"))
		return TRUE;
	if (!strcmp(s,"logx"))
		return TRUE;
	if (!strcmp(s,"logb"))
		return TRUE;
	if (!strcmp(s,"dlg"))
		return TRUE;
	if (!strcmp(s,"recip"))
		return TRUE;
	if (!strcmp(s,"nl"))
		return TRUE;
	if (!strcmp(s,"v"))
		return TRUE;
	if (!strcmp(s,"gcf"))
		return TRUE;
	if (!strcmp(s,"lcm"))
		return TRUE;
	return FALSE;
}
