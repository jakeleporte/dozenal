/*
 * +AMDG
 */
/*
 * This document was begun on X Oct 11E9, the feast of St.
 * Francis Borgia; and it is humbly dedicated to him and to
 * the Immaculate Heart of Mary, for their prayers, and to
 * the Sacred Heart of Jesus for His mercy.
 */
/*
 * Converts lua programs inhaled through stdin to decimal so
 * the interpreter can run; also converts the results to
 * dozenal.
 *
 * (C) Copyright 2013  Donald P. Goodman III
 *
 * This file is part of dozlua.
 *
 * dozlua is free software:  you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any
 * later version.
 *
 * dozlua is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with dozlua.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<float.h>
#include"conv.h"
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#define MAXNUMLEN 500

char *decimalize_string();
char *dozenalize_string();

char *convstr;
char *luastr;
char *outstr;

int main(void)
{
	char buff[MAXNUMLEN];
	double buffer;
	char dozbuff[MAXNUMLEN];
	int error;
	char *currstring;
	int buffsize = MAXNUMLEN;
	int i;
	char c;
	lua_State *L;
	L = luaL_newstate();
	luaL_openlibs(L);

	/* redirect sdout */
	FILE *fp;
	char template[] = "dozlua_XXXXXX";
	int stdout_bk, fd;
	stdout_bk = dup(fileno(stdout));
	if ((fd = mkstemp(template)) == -1)
		exit(1);
	fp = fdopen(fd,"rw");
	dup2(fd,fileno(stdout));
	/**/
	if ((convstr = malloc(sizeof(char)*buffsize)) == NULL) {
		fprintf(stderr,"dozlua:  insufficient memory\n");
		exit(1);
	}
	for (i=0; (c=getchar())!=EOF; ++i) {
		if ((i + 1) >= (buffsize-1)) {
			buffsize *= 2;
			if ((convstr=realloc(convstr,(sizeof(char)*buffsize))) == NULL) {
				fprintf(stderr,"dozlua:  insufficient memory\n");
			}
		}
		convstr[i] = c;
	}
	convstr[i] = '\0';
	currstring = decimalize_string();
	error = luaL_loadbuffer(L,currstring,strlen(currstring) - 1,"")
		|| lua_pcall(L,0,LUA_MULTRET,0);
	if (error) {
		fprintf(stderr,"%s",lua_tostring(L,-1));
		lua_pop(L,1);
		exit(1);
	}
	lua_getglobal(L,"luadoz");
	lua_call(L,0,LUA_MULTRET);
	dup2(stdout_bk,fileno(stdout));
	fseek(fp,0,0);
	while ((c = getc(fp)) != EOF) {
		if (c != '*') {
			printf("%c",c);
		} else {
			i = 0;
			while (((c = getc(fp)) != '*'))
				buff[i++] = c;
			buff[i] = '\0';
			buffer = atof(buff);
			if (buffer == 0.0) {
				printf("*%s%c",buff,c);
			} else {
				dectodoz(dozbuff,atof(buff));
				dozbuff[i] = '\0';
				printf("%s",dozbuff);
				dozbuff[0] = '\0';
			}
		}
	}
	for (i = 1; i <= lua_gettop(L); i++) {
		printf("%s",dozenalize_string(lua_tostring(L,i)));
	}
	fflush(stdout);
	fclose(fp);
	unlink(template);
	free(luastr);
	free(outstr);
	free(convstr);
	lua_close(L);
}

char *dozenalize_string(char *decstr)
{
	char numconv[MAXNUMLEN];
	char dozenal[MAXNUMLEN];
	int fulllen;
	double decimal;
	int i = 0; int j = 0; int k = 0; int l = 0;

	fulllen = strlen(decstr);
	if (outstr == NULL) {
		if ((outstr = malloc(sizeof(char)*fulllen)) == NULL) {
			fprintf(stderr,"dozlua:  insufficient memory\n");
			exit(1);
		}
	}
	while (decstr[i] != '\0') {
		if (isdigit(decstr[i])) {
			while (isdigit(decstr[i]) || decstr[i] == '.') {
				numconv[j++] = decstr[i];
				i++;
			}
			i--;
			numconv[j] = '\0';
			decimal = atof(numconv);
			dectodoz(dozenal,decimal);
			dozenal[j] = '\0';
			j = strlen(dozenal);
			for (l = 0; l < j; l++) {
				if ((k + 1) > (fulllen-10)) {
					fulllen *= 2;
					if ((outstr=realloc(outstr,(sizeof(char)*fulllen)))==NULL) {
						fprintf(stderr,"dozlua:  insufficient memory\n");
					}
				}
				outstr[k++] = dozenal[l];
			}
			j = 0; numconv[0] = '\0';
		} else {
			if ((k + 1) > (fulllen-10)) {
				fulllen *= 2;
				if ((outstr=realloc(outstr,(sizeof(char)*fulllen))) == NULL) {
					fprintf(stderr,"dozlua:  insufficient memory\n");
				}
			}
			outstr[k++] = decstr[i];
		}
		i++;
	}
	outstr[k] = '\0';
	return outstr;
}

char *decimalize_string()
{
	char numconv[MAXNUMLEN];
	char decimal[MAXNUMLEN];
	double decnum;
	int fulllen;
	int i = 0; int j = 0; int k = 0; int l = 0;

	fulllen = strlen(convstr);
	if ((luastr = malloc(sizeof(char)*fulllen)) == NULL) {
		fprintf(stderr,"dozlua:  insufficient memory\n");
		exit(1);
	}
	while (convstr[i] != '\0') {
		if ((convstr[i] == '/') && (convstr[i+1] != ' ')) {
			while (convstr[++i] != '/')
				numconv[j++] = convstr[i];
			numconv[j] = '\0';
			decnum = doztodec(numconv);
			sprintf(decimal,"%f",decnum);
			j = strlen(decimal);
			for (l = 0; l < j; l++) {
				if ((k + 1) >= (fulllen-1)) {
					fulllen *= 2;
					if ((luastr=realloc(luastr,(sizeof(char)*fulllen)))==NULL) {
						fprintf(stderr,"dozlua:  insufficient memory\n");
					}
				}
				luastr[k++] = decimal[l];
			}
			j = 0; numconv[0] = '\0';
		} else {
			if ((k + 1) >= (fulllen-1)) {
				fulllen *= 2;
				if ((luastr=realloc(luastr,(sizeof(char)*fulllen))) == NULL) {
					fprintf(stderr,"dozlua:  insufficient memory\n");
				}
			}
			luastr[k++] = convstr[i];
		}
		i++;
	}
	luastr[k] = '\0';
	return luastr;
}
