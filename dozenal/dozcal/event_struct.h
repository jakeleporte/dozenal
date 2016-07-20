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

struct event {
	int id;					/* idnum of the event entry */
	char title[256];		/* title of the event */
	int thisdate;			/* the date */
	int starttime;			/* starting time, in Tims from midnight */
	int endtime;			/* ending time, in Tims from midnight */
	char location[256];	/* the location of the event */
	int relatedto;			/* idnum of other events or todos */
	char evclass[16];		/* e.g., "private" */
	char categories[256];/* categories event fits into; e.g., "business" */
	char transp;			/* '0' if opaque, 1 if transp */
};

struct todo {
	char item[256];
	char todoclass[16];
	char categories[256];/* categories todo fits into; e.g., "business" */
	int duedate;
	int duetime;
	int priority;			/* higher numbers have higher priority */
	char location[256];
	int completed;			/* '0' if not completed, 1 if completed */
	int pergross;			/* 0-144 completed amount */
};
