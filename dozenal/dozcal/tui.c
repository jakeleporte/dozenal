/* + AMDG */

#include<stdio.h>
#include<ncurses.h>
#include<time.h>
#include<string.h>
#include"event_struct.h"
#include"julday.h"
#include"utility.h"
#include"conv.h"

extern char **evlines; extern int numevs;
extern char **todolines; extern int numtodos;
extern struct event *event_list;
extern int recordnums;
extern struct todo *todo_list;
extern int todonums;

WINDOW *switch_win(WINDOW *cal,WINDOW *ev, WINDOW *todo, 
	WINDOW *currwin, WINDOW *evtitle, WINDOW *todotitle);

int build_tui(char *ev_form,char *date_form,char *time_form)
{
	int mon = 9; int year = 2016;
	WINDOW *calendar,*eventswin,*todowin,*evtitle,*todotitle,
		*evconts,*todoconts,*win;
	const int cheight = 10; const int cwidth = 24;
	int eheight, ewidth, theight, twidth;
	int datenum;
	int currday = 1;
	int c;
	int x, y;
	int evpos = 0; int todopos = 0;
	int numrecs;

	initscr(); cbreak(); noecho(); keypad(stdscr,TRUE); curs_set(0);
	refresh();
	getmaxyx(stdscr,y,x);
	ewidth = x - cwidth - 2;
	eheight = y - 8;
	/* title bar */
	make_titlebar();
	/* event window, event title, and content pad */
	eventswin = newwin(y-3,x-cwidth,1,0);
	evtitle = newwin(2,x-cwidth-2,2,1);
	evconts = newpad((3*y),ewidth);
	/* todo window, todo title, and content pad */
	todowin = newwin(y-3-cheight,cwidth,cheight+1,x-cwidth);
	todotitle = newwin(2,cwidth-2,y-2-cheight+2,x-cwidth+1);
	todoconts = newpad((3 * y),cwidth-2);
	/* calendar window and contents */
	calendar = newwin(cheight,cwidth,1,x-cwidth);
	datenum = print_cal(calendar,mon,year,0,currday,evconts);
	/* main event loop */
	win = eventswin;
	win = switch_win(calendar,eventswin,todowin,win,evtitle,todotitle);
	numrecs = load_evconts(evconts,eheight,ewidth,ev_form,date_form,
		time_form,datenum);
	while ((c = getch()) != 'q') {
		if (win == calendar) {
			switch(c) {
			case KEY_DOWN: case 'j':
				datenum = change_cal(calendar,&currday,&mon,&year,7,evconts);
				numrecs = load_evconts(evconts,eheight,ewidth,ev_form,date_form,
					time_form,datenum);
				evpos = 0;
				break;
			case KEY_UP: case 'k':
				datenum = change_cal(calendar,&currday,&mon,&year,-7,evconts);
				numrecs = load_evconts(evconts,eheight,ewidth,ev_form,date_form,
					time_form,datenum);
				evpos = 0;
				break;
			case KEY_LEFT: case 'l':
				datenum = change_cal(calendar,&currday,&mon,&year,1,evconts);
				numrecs = load_evconts(evconts,eheight,ewidth,ev_form,date_form,
					time_form,datenum);
				evpos = 0;
				break;
			case KEY_RIGHT: case 'h':
				datenum = change_cal(calendar,&currday,&mon,&year,-1,evconts);
				numrecs = load_evconts(evconts,eheight,ewidth,ev_form,date_form,
					time_form,datenum);
				evpos = 0;
				break;
			case 9:
				win = switch_win(calendar,eventswin,todowin,win,
					evtitle,todotitle);
				numrecs = load_evconts(evconts,eheight,ewidth,ev_form,date_form,
					time_form,datenum);
				break;
			}
		} else if (win == eventswin) {
			switch(c) {
			case 9:
				win = switch_win(calendar,eventswin,todowin,win,
					evtitle,todotitle);
				numrecs = load_evconts(evconts,eheight,ewidth,ev_form,date_form,
					time_form,datenum);
				break;
			case 'j':
				if (evpos <= numrecs) {
					prefresh(evconts,++evpos,0,5,3,eheight,ewidth-2);
				}
				break;
			case 'k':
				if (evpos >= 0) {
					prefresh(evconts,--evpos,0,5,3,eheight,ewidth-2);
				}
				break;
			}
		} else if (win == todowin) {
			switch(c) {
			case 9:
				win = switch_win(calendar,eventswin,todowin,win,
					evtitle,todotitle);
				numrecs = load_evconts(evconts,eheight,ewidth,ev_form,date_form,
					time_form,datenum);
				break;
			}
		}
	}
	getch();
	delwin(calendar);
	delwin(eventswin);
	delwin(evtitle);
	delwin(todotitle);
	delwin(todowin);
	endwin();
	return 0;
}
	
int load_evconts(WINDOW *evconts,int eheight, int ewidth,
char *ev_form, char *date_form, char *time_form, int datenum)
{
	int i; int numnewlines = 0;
	FILE *outfile;
	int numrecs = 0;

	clear_evconts(evconts);
	clear_events();
	for (i = 0; i < (recordnums-1); ++i) {
		if (event_list[i].thisdate == (datenum-1)) {
			fill_event(ev_form,i,date_form,time_form,outfile);
			numrecs++;
		}
	}
	for (i = 1; i < numevs; ++i) {
		numnewlines += countchars(*(evlines+i),'\n');
		mvwprintw(evconts,0+i-1+numnewlines,0,"%s",*(evlines+i));
	}
	prefresh(evconts,0,0,5,3,eheight,ewidth-2);
	return numrecs + numnewlines;
}

int clear_evconts(WINDOW *evconts)
{
	int x,y,i,j;

	getmaxyx(evconts,y,x);
	for (i = 0; i < y; ++i) {
		for (j = 0; j < x; ++j) {
			mvwprintw(evconts,i,j," ");
		}
	}
}

WINDOW *switch_win(WINDOW *cal, WINDOW *ev, WINDOW *todo,WINDOW *currwin,
WINDOW *evtitle, WINDOW *todotitle)
{
	WINDOW *win;
	int i;

	wborder(cal,ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,
		ACS_ULCORNER,ACS_URCORNER, ACS_LLCORNER,ACS_LRCORNER);
	wborder(ev,ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,
		ACS_ULCORNER,ACS_URCORNER, ACS_LLCORNER,ACS_LRCORNER);
	wborder(todo,ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,
		ACS_ULCORNER,ACS_URCORNER, ACS_LLCORNER,ACS_LRCORNER);
	wrefresh(cal);
	wrefresh(ev);
	wrefresh(todo);
	if (currwin == todo)
		win = ev;
	if (currwin == ev)
		win = cal;
	if (currwin == cal)
		win = todo;
	wattron(win,A_BOLD);
	wborder(win,ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,
		ACS_ULCORNER,ACS_URCORNER, ACS_LLCORNER,ACS_LRCORNER);
	wattroff(win,A_BOLD);
	wrefresh(win);
	wborder(evtitle,' ',' ',' ',ACS_HLINE,' ',' ',' ',' ');
	wborder(todotitle,' ',' ',' ',ACS_HLINE,' ',' ',' ',' ');
	center_line(evtitle,0,"Events");
	center_line(todotitle,0,"Todos");
	wrefresh(evtitle);
	wrefresh(todotitle);
	return win;
}

int make_titlebar()
{
	int x, y,lenlft,lenrgt, i;
	char *lftstr = "--dozcal, v0.9";
	char *rgtstr = "dozenal--";

	getmaxyx(stdscr,y,x);
	lenlft = strlen(lftstr);
	lenrgt = strlen(rgtstr);
	attron(A_BOLD | A_REVERSE);
	mvprintw(0,0,"%s",lftstr);
	for (i = lenlft; i <= (x - lenrgt - 1); ++i)
		mvprintw(0,i," ");
	mvprintw(0,i,"%s",rgtstr);
	attroff(A_BOLD | A_REVERSE);
	return 0;
}

int change_cal(WINDOW *win, int *currday, int *mon, int *year, 
int shift,WINDOW *evconts)
{
	struct tm *date;
	time_t rawtime;
	double jdn;
	int datenum;

	time(&rawtime);
	date = localtime(&rawtime);
	date->tm_year = *year-1900; date->tm_mon = *mon;
		date->tm_mday = *currday; mktime(date);
	jdn = datenum_to_jdn(get_datenum(date));
	jdn += shift;
	date = broken_date(jdn_to_datenum(jdn));
	*currday = date->tm_mday; *mon = date->tm_mon;
		*year = date->tm_year + 1900;
	clear_cal(win);
	datenum = print_cal(win,*mon,*year,0,*currday,evconts);
	return datenum;
}

int clear_cal(WINDOW *win)
{
	int i; int j;

	for (i = 1; i < 9; ++i) {
		for (j = 1; j < 23; ++j) {
			mvwprintw(win,i,j," ");
		}
	}
	return 0;
}

int print_cal(WINDOW *win, int mon, int year, int fdow, int currday,
WINDOW *evconts)
{
	struct tm *date;
	time_t rawtime;
	int i, j;
	int hoffset = 2;
	int voffset = 3;
	char buf[3];

	time(&rawtime);
	date = localtime(&rawtime);
	date->tm_mon = mon; date->tm_year = year - 1900; date->tm_mday = 1;
	mktime(date);
	print_monline(win,date->tm_mon,date->tm_year+1900);
	print_wdayline(win,fdow);
	if (date->tm_wday < fdow)
		hoffset = 2 + (3 * (fdow + 1));
	else if (date->tm_wday > fdow)
		hoffset = 2 + ((date->tm_wday - 1 - fdow) * 3);
	else
		hoffset = 2 + (3 * fdow);
	while(date->tm_mon == mon) {
		buf[0] = '\0';
		if ((date->tm_wday % 7) == fdow) {
			hoffset = 2;
			voffset += 1;
		} else {
			hoffset += 3;
		}
		dectodoz(buf,(double)date->tm_mday);
		if (currday == date->tm_mday) {
			wattron(win,A_REVERSE);
			mvwprintw(win,voffset,hoffset,"%2s",buf);
			wattroff(win,A_REVERSE);
			wrefresh(win);
			refresh();
		} else {
			mvwprintw(win,voffset,hoffset,"%2s",buf);
			wrefresh(win);
			refresh();
		}
		date->tm_mday +=1; mktime(date);
	}
	date->tm_mday = currday + 1; date->tm_mon -= 1; mktime(date);
	return get_datenum(date);
}

int print_monline(WINDOW *win,int mon, int year)
{
	char month[24];
	char buf[5];

	dectodoz(buf,(double)year);
	if (mon == 0) {
		sprintf(month,"%s %s","January",buf);
		center_line(win,1,month);
	} if (mon == 1) {
		sprintf(month,"%s %s","February",buf);
		center_line(win,1,month);
	} if (mon == 2) {
		sprintf(month,"%s %s","March",buf);
		center_line(win,1,month);
	} if (mon == 3) {
		sprintf(month,"%s %s","April",buf);
		center_line(win,1,month);
	} if (mon == 4) {
		sprintf(month,"%s %s","May",buf);
		center_line(win,1,month);
	} if (mon == 5) {
		sprintf(month,"%s %s","June",buf);
		center_line(win,1,month);
	} if (mon == 6) {
		sprintf(month,"%s %s","July",buf);
		center_line(win,1,month);
	} if (mon == 7) {
		sprintf(month,"%s %s","August",buf);
		center_line(win,1,month);
	} if (mon == 8) {
		sprintf(month,"%s %s","September",buf);
		center_line(win,1,month);
	} if (mon == 9) {
		sprintf(month,"%s %s","October",buf);
		center_line(win,1,month);
	} if (mon == 10) {
		sprintf(month,"%s %s","November",buf);
		center_line(win,1,month);
	} if (mon == 11) {
		sprintf(month,"%s %s","December",buf);
		center_line(win,1,month);
	}
	return 0;
}

int print_wdayline(WINDOW *win,int fdow)
{
	if (fdow == 0)
		mvwprintw(win,2,2,"Su Mo Tu We Th Fr Sa");
	else if (fdow == 1)
		mvwprintw(win,2,2,"Mo Tu We Th Fr Sa Su");
	else if (fdow == 2)
		mvwprintw(win,2,2,"Tu We Th Fr Sa Su Mo");
	else if (fdow == 3)
		mvwprintw(win,2,2,"We Th Fr Sa Su Mo Tu");
	else if (fdow == 4)
		mvwprintw(win,2,2,"Th Fr Sa Su Mo Tu We");
	else if (fdow == 5)
		mvwprintw(win,2,2,"Fr Sa Su Mo Tu We Th");
	else if (fdow == 6)
		mvwprintw(win,2,2,"Sa Su Mo Tu We Th Fr");
	return 0;
}

int center_line(WINDOW *win, int y, char *s)
{
	int cols,rows,len;

	getmaxyx(win,rows,cols);
	len = strlen(s);
	mvwprintw(win,y,cols/2-len/2,"%s",s);
	return 0;
}
