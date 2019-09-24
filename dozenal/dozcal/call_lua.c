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
#include"errcodes.h"
#include"utility.h"
#include"conv.h"
#include"proc_date.h"
#include<lua5.2/lua.h>
#include<lua5.2/lauxlib.h>
#include<lua5.2/lualib.h>

void bail(lua_State *L, int err_code, char *filename);
int file_prefix(char **s, char *t);

int call_lua(char *s)
{
	const char *key; const char *val;
	char title[256];		/* title of the event */
	int thisdate = 0;		/* the date */
	int starttime = 0;	/* starting time, in Tims from midnight */
	int endtime = 0;		/* ending time, in Tims from midnight */
	char location[256];	/* the location of the event */
	char evclass[16];		/* e.g., "private" */
	char categories[256];/* categories event fits into; e.g., "business" */
	char attendees[256];/* attendees of the event */
	int cnt = 0;
	int numreturns = 1;
	int i;
	char *filename = NULL;
	char transp = 1;

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
		categories[0] = '\0'; attendees[0] = '\0';
		while (lua_next(L,-(1+numreturns - i))) {
			val = lua_tostring(L,-1);
			lua_pop(L,1);
			key = lua_tostring(L,-1);
			cnt += 1;
			if (strcmp(key,"TITLE") == 0) {
				strncpy(title,val,MAXLEN); 
			} else if (strcmp(key,"START_DATE") == 0) {
				thisdate = mkdaynum(proc_date((char *)val)) + 1;
			} else if (strcmp(key,"DUE_DATE") == 0) {
				thisdate = mkdaynum(proc_date((char *)val)); 
			} else if (strcmp(key,"START_TIME") == 0) {
				starttime = proc_time((char *)val); 
			} else if (strcmp(key,"DUE_TIME") == 0) {
				starttime = proc_time((char *)val); 
			} else if (strcmp(key,"END_TIME") == 0) {
				endtime = proc_time((char *)val); 
			} else if (strcmp(key,"LOCATION") == 0) {
				strncpy(location,val,MAXLEN); 
			} else if (strcmp(key,"CLASS") == 0) {
				strncpy(evclass,val,SHORTLEN); 
			} else if (strcmp(key,"CATEGORY") == 0) {
				strncpy(categories,val,MAXLEN); 
			} else if (strcmp(key,"TRANSPARENT") == 0) {
				transp = atoi(val);
			} else if (strcmp(key,"ATTENDEES") == 0) {
				strncpy(attendees,val,MAXLEN); 
			} else {
				fprintf(stderr,"dozcal:  error from lua "
					"script \"%s\":  unknown key \"%s\"\n",
					s,key);
				exit(LUA_ERROR);
			}
			if (cnt == 9) {
				add_event(starttime, endtime, thisdate, title, evclass, 
					categories, location, transp, attendees);
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
