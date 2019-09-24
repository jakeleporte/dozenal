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

#include"errcodes.h"

struct event {
	int id;						/* idnum of the event entry */
	char title[MAXLEN+1];	/* title of the event */
	int thisdate;				/* the date */
	int starttime;				/* starting time, in Tims from midnight */
	int endtime;				/* ending time, in Tims from midnight */
	char location[MAXLEN+1];	/* the location of the event */
	int relatedto;				/* idnum of other events or todos */
	char evclass[SHORTLEN+1];			/* e.g., "private" */
	char categories[MAXLEN+1];/* categories; e.g., "business" */
	char transp;				/* '0' if opaque, 1 if transp */
	char attendees[MAXLEN+1]; /* list of attendees */
	char url[MAXLEN+1];		/* URL associated with event */
};

struct todo {
	char item[MAXLEN+1];
	char todoclass[SHORTLEN+1];
	char categories[MAXLEN+1];/* categories todo fits into; e.g., "business" */
	int duedate;
	int duetime;
	int priority;			/* higher numbers have higher priority */
	char location[MAXLEN+1];
	int completed;			/* '0' if not completed, 1 if completed */
	int pergross;			/* 0-144 completed amount */
};

struct globopts {
	char opt[36];
	int r;
	int g;
	int b;
	int colconst;
};

#define	NOCOLOR				0
#define	WHOLEBG				1
#define	CALBG					2
#define	EVENTBG				3
#define	TODOBG				4
#define	CALTITLEFORE		5
#define	CALTITLEBACK		6
#define	CALWEEKFORE			7
#define	CALWEEKBACK			8
#define	CALFORE				9
#define	CALBACK				10
#define	TODOTITLEFORE		11
#define	TODOTITLEBACK		12
#define	TODOLINEFORE		13
#define	TODOLINEBACK		14
#define	TODOFORE				15
#define	TODOBACK				16
#define	EVTITLEFORE			17
#define	EVTITLEBACK			18
#define	EVLINEFORE			19
#define	EVLINEBACK			20
#define	EVFORE				21
#define	EVBACK				22
#define	TITLEFORE			23
#define	TITLEBACK			24
#define	BOTFORE				25
#define	BOTBACK				26
#define	WARNINGFORE			27
#define	WARNINGBACK			28
#define	INACTIVEBORDFORE	29
#define	INACTIVEBORDBACK	30
#define	ACTIVEBORDFORE		31
#define	ACTIVEBORDBACK		32
#define	WHOLEEVBG			33
#define	WHOLETODOBG			34
#define	COL_WHOLEBG				101
#define	COL_CALBG					102
#define	COL_EVENTBG				103
#define	COL_TODOBG				104
#define	COL_CALTITLEFORE		105
#define	COL_CALTITLEBACK		106
#define	COL_CALWEEKFORE			107
#define	COL_CALWEEKBACK			108
#define	COL_CALFORE				109
#define	COL_CALBACK				110
#define	COL_TODOTITLEFORE		111
#define	COL_TODOTITLEBACK		112
#define	COL_TODOLINEFORE		113
#define	COL_TODOLINEBACK		114
#define	COL_TODOFORE				115
#define	COL_TODOBACK				116
#define	COL_EVTITLEFORE			117
#define	COL_EVTITLEBACK			118
#define	COL_EVLINEFORE			119
#define	COL_EVLINEBACK			120
#define	COL_EVFORE				121
#define	COL_EVBACK				122
#define	COL_TITLEFORE			123
#define	COL_TITLEBACK			124
#define	COL_BOTFORE				125
#define	COL_BOTBACK				126
#define	COL_WARNINGFORE			127
#define	COL_WARNINGBACK			128
#define	COL_INACTIVEBORDFORE	129
#define	COL_INACTIVEBORDBACK	130
#define	COL_ACTIVEBORDFORE		131
#define	COL_ACTIVEBORDBACK		132
#define	COL_WHOLEEVBG			133
#define	COL_WHOLETODOBG			134
