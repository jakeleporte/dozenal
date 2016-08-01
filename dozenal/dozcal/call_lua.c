/*
 * +AMDG
 */
/*
 * This document was begun on 5 July 1200, the feast of St.
 * Anthony Mary Zaccaria, C, and it is humbly dedicated to
 * him and to the Immaculate Heart of Mary for their
 * prayers, and to the Sacred Heart of Jesus for His mercy.
 *
 * dozcal:  keeps a calendar with a specific internal format
 * in dozenal
 *
 * (C) Copyright 2016  Donald P. Goodman III
 *
 * This file is part of dozcal.
 *
 * dozcal is free software:  you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any
 * later version.
 *
 * dozcal is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with dozcal.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include"errcodes.h"
#include<lua5.2/lua.h>
#include<lua5.2/lauxlib.h>
#include<lua5.2/lualib.h>

void bail(lua_State *L, int err_code, char *filename);

int call_lua(char *s)
{
	const char *key; const char *val;
	int evto = 0;			/* 0 for event, 1 for todo */
	char title[256];		/* title of the event */
	int thisdate = 0;		/* the date */
	int starttime = 0;	/* starting time, in Tims from midnight */
	int endtime = 0;		/* ending time, in Tims from midnight */
	int relatedto = 0;	/* idnum of other events or todos */
	char location[256];	/* the location of the event */
	char evclass[16];		/* e.g., "private" */
	char categories[256];/* categories event fits into; e.g., "business" */
	char transp = 0;		/* '0' if opaque, 1 if transp */
	int cnt = 0;
	int numreturns = 1;
	int priority = 0;
	int compflag = 0;
	int pergross = 0;
	int i;
	char *filename = NULL;

	lua_State *L;
	L = luaL_newstate();
	luaL_openlibs(L);
	if (file_prefix(&filename,s) == -1) {
		fprintf(stderr,"dozcal:  Lua script \"%s\" not found in "
			"either current directory or \"$HOME/.dozcal/\"; "
			"skipping...\n",s);
		lua_close(L);
		free(filename);
		return 0;
	}
	luaL_loadfile(L,filename);
	lua_pcall(L,0,0,0);
	lua_getglobal(L,"dozcal_return_ev_num");
	lua_pcall(L,0,1,0);
	numreturns = (int)lua_tonumber(L,-1);
	lua_getglobal(L,"dozcal_return_ev");
	if (lua_pcall(L,0,numreturns,0))
		bail(L,LUA_ERROR,s);
	lua_pushnil(L);
	for (i = 0; i < numreturns; ++i) {
		title[0] = '\0'; location[0] = '\0'; evclass[0] = '\0';
		categories[0] = '\0';
		while (lua_next(L,-(1+numreturns - i))) {
			val = lua_tostring(L,-1);
			lua_pop(L,1);
			key = lua_tostring(L,-1);
			cnt += 1;
			if (strcmp(key,"TITLE") == 0) {
				strncpy(title,val,MAXLEN); 
			} else if (strcmp(key,"START_DATE") == 0) {
				thisdate = mkdaynum(proc_date(val)) + 1;
			} else if (strcmp(key,"DUE_DATE") == 0) {
				thisdate = mkdaynum(proc_date(val)); 
			} else if (strcmp(key,"START_TIME") == 0) {
				starttime = proc_time(val); 
			} else if (strcmp(key,"DUE_TIME") == 0) {
				starttime = proc_time(val); 
			} else if (strcmp(key,"END_TIME") == 0) {
				endtime = proc_time(val); 
			} else if (strcmp(key,"LOCATION") == 0) {
				strncpy(location,val,MAXLEN); 
			} else if (strcmp(key,"CLASS") == 0) {
				strncpy(evclass,val,SHORTLEN); 
			} else if (strcmp(key,"CATEGORY") == 0) {
				strncpy(categories,val,MAXLEN); 
			} else if (strcmp(key,"PRIORITY") == 0) {
				priority = (int)doztodec(val);
			} else if (strcmp(key,"PERGROSS") == 0) {
				pergross = (int)doztodec(val);
			} else if (strcmp(key,"COMPFLAG") == 0) {
				compflag = atoi(val);
			} else {
				fprintf(stderr,"dozcal:  error from lua "
					"script \"%s\":  unknown key \"%s\"\n",
					s,key);
				exit(LUA_ERROR);
			}
			if (cnt == 7) {
				add_event(starttime, endtime, thisdate, title, evclass, 
					categories, location);
				cnt = 0;
			}
		}
		lua_pushnil(L);
	}
	lua_close(L);
	free(filename);
	return 0;
}

void bail(lua_State *L, int err_code, char *filename)
{
	fprintf(stderr,"dozcal:  lua script \"%s\" failed "
		"with the following error:\n\t%s\n",filename,
		lua_tostring(L,-1));
	exit(err_code);
}
	
int file_prefix(char **s, char *t)
{
	char *home;
	int preflen;
	char *prefix = "/.dozcal/";
	char *nohomepref = "./";

	home = getenv("HOME");
	if (home != NULL) {
		preflen = strlen(home) + strlen(prefix) + 1;
	} else {
		preflen = strlen(prefix) + 4;
	}
	if ((*s = malloc((preflen + strlen(t) + 1) * 
	sizeof(char))) == NULL) {
		fprintf(stderr,"dozcal:  insufficient memory to hold "
			"the configuration file name\n");
		exit(INSUFF_MEM);
	}
	**s = '\0';
	strcat(*s,nohomepref); strcat(*s,t);
	if (file_exist(*s)) {
		return 0;
	} else {
		if (home != NULL) {
			**s = '\0';
			strcat(*s,home); strcat(*s,prefix); strcat(*s,t);
			if (file_exist(*s)) {
				return 0;
			}
		}
	}
	return -1;
}

int file_exist(char *s)
{
	struct stat buffer;
	return (stat(s,&buffer) == 0);
}
