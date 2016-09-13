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
extern struct globopts *allopts;
extern int numopts;

WINDOW *switch_win(WINDOW *cal,WINDOW *ev, WINDOW *todo, 
	WINDOW *currwin, WINDOW *evtitle, WINDOW *todotitle);
WINDOW *switch_back_win(WINDOW *cal,WINDOW *ev, WINDOW *todo, 
	WINDOW *currwin, WINDOW *evtitle, WINDOW *todotitle);

int build_tui(char *ev_form,char *date_form,char *time_form, 
char *todo_form)
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
	int evpos = 0; int evhpos = 0; int todopos = 0; int todohpos = 0;
	int numrecs;
	int numtrecs;

	initscr(); cbreak(); noecho(); keypad(stdscr,TRUE); curs_set(0);
	if (has_colors() == FALSE) {
		print_warn("ERROR:  Terminal does not support color; "
			"using default colors...");
	}
	if (allopts[NOCOLOR].colconst != -1)
		start_color();
	if (can_change_color() == FALSE) {
		equalize_colors();
	} else {
		define_colors();
	}
	init_pair(7,COLOR_WHITE,allopts[WHOLEBG].colconst);
//	wbkgd(stdscr,COLOR_PAIR(7));
	refresh();
	getmaxyx(stdscr,y,x);
	ewidth = x - cwidth - 2;
	eheight = y - 4;
	/* title bar */
	make_titlebar();
	make_botbar();
	/* event window, event title, and content pad */
	eventswin = newwin(y-3,x-cwidth,1,0);
	init_pair(16,COLOR_WHITE,allopts[WHOLEEVBG].colconst);
	wbkgd(eventswin,COLOR_PAIR(16));
	evtitle = newwin(2,x-cwidth-2,2,1);
	evconts = newpad((3*y),2*ewidth);
	/* todo window, todo title, and content pad */
	twidth = cwidth; theight = cheight+1;
	todowin = newwin(y-2-theight,twidth,theight,x-twidth);
	init_pair(17,COLOR_WHITE,allopts[WHOLETODOBG].colconst);
	wbkgd(todowin,COLOR_PAIR(17));
	todotitle = newwin(2,cwidth-2,theight+1,x-cwidth+1);
	todoconts = newpad((3 * y),3*twidth);
	/* calendar window and contents */
	calendar = newwin(cheight,cwidth,1,x-cwidth);
	datenum = print_cal(calendar,mon,year,0,currday,evconts);
	/* main event loop */
	win = eventswin;
	win = switch_win(calendar,eventswin,todowin,win,evtitle,todotitle);
	datenum = change_cal(calendar,&currday,&mon,&year,7,evconts);
	numrecs = load_evconts(evconts,eheight,ewidth,ev_form,date_form,
		time_form,datenum);
	numtrecs = load_todos(todoconts,theight,twidth,todo_form,date_form,
		time_form);
	while ((c = getch()) != 'q') {
		if (win == calendar) {
			switch(c) {
			case KEY_DOWN: case 'j':
				datenum = change_cal(calendar,&currday,&mon,&year,7,evconts);
				numrecs = load_evconts(evconts,eheight,ewidth,ev_form,date_form,
					time_form,datenum);
				numtrecs = load_todos(todoconts,theight,twidth,todo_form,
					date_form, time_form);
				evpos = 0;
				break;
			case KEY_UP: case 'k':
				datenum = change_cal(calendar,&currday,&mon,&year,-7,evconts);
				numrecs = load_evconts(evconts,eheight,ewidth,ev_form,date_form,
					time_form,datenum);
				numtrecs = load_todos(todoconts,theight,twidth,todo_form,
					date_form, time_form);
				evpos = 0;
				break;
			case KEY_RIGHT: case 'l':
				datenum = change_cal(calendar,&currday,&mon,&year,1,evconts);
				numrecs = load_evconts(evconts,eheight,ewidth,ev_form,date_form,
					time_form,datenum);
				numtrecs = load_todos(todoconts,theight,twidth,todo_form,
					date_form, time_form);
				evpos = 0;
				break;
			case KEY_LEFT: case 'h':
				datenum = change_cal(calendar,&currday,&mon,&year,-1,evconts);
				numrecs = load_evconts(evconts,eheight,ewidth,ev_form,date_form,
					time_form,datenum);
				numtrecs = load_todos(todoconts,theight,twidth,todo_form,
					date_form, time_form);
				evpos = 0;
				break;
			case 9:
				clear_warn();
				win = switch_win(calendar,eventswin,todowin,win,
					evtitle,todotitle);
				datenum = change_cal(calendar,&currday,&mon,&year,0,evconts);
				numrecs = load_evconts(evconts,eheight,ewidth,ev_form,date_form,
					time_form,datenum);
				numtrecs = load_todos(todoconts,theight,twidth,todo_form,
					date_form, time_form);
				break;
			case KEY_BTAB:
				clear_warn();
				win = switch_back_win(calendar,eventswin,todowin,win,
					evtitle,todotitle);
				datenum = change_cal(calendar,&currday,&mon,&year,0,evconts);
				numrecs = load_evconts(evconts,eheight,ewidth,ev_form,date_form,
					time_form,datenum);
				numtrecs = load_todos(todoconts,theight,twidth,todo_form,
					date_form, time_form);
				break;
			}
		} else if (win == eventswin) {
			switch(c) {
			case 9:
				clear_warn();
				win = switch_win(calendar,eventswin,todowin,win,
					evtitle,todotitle);
				datenum = change_cal(calendar,&currday,&mon,&year,0,evconts);
				numrecs = load_evconts(evconts,eheight,ewidth,ev_form,date_form,
					time_form,datenum);
				numtrecs = load_todos(todoconts,theight,twidth,todo_form,
					date_form, time_form);
				break;
			case KEY_BTAB:
				clear_warn();
				win = switch_back_win(calendar,eventswin,todowin,win,
					evtitle,todotitle);
				datenum = change_cal(calendar,&currday,&mon,&year,0,evconts);
				numrecs = load_evconts(evconts,eheight,ewidth,ev_form,date_form,
					time_form,datenum);
				numtrecs = load_todos(todoconts,theight,twidth,todo_form,
					date_form, time_form);
				break;
			case 'j': case KEY_DOWN:
				if (evpos <= numrecs) {
					prefresh(evconts,++evpos,evhpos,5,3,eheight,ewidth-2);
				}
				break;
			case 'k': case KEY_UP:
				if (evpos >= 1) {
					prefresh(evconts,--evpos,evhpos,5,3,eheight,ewidth-2);
				}
				break;
			case 'l': case KEY_RIGHT:
				prefresh(evconts,evpos,++evhpos,5,3,eheight,ewidth-2);
				break;
			case 'h': case KEY_LEFT:
				if (evhpos >= 1) {
					prefresh(evconts,evpos,--evhpos,5,3,eheight,ewidth-2);
				}
				break;
			}
		} else if (win == todowin) {
			switch(c) {
			case 9:
				clear_warn();
				win = switch_win(calendar,eventswin,todowin,win,
					evtitle,todotitle);
				datenum = change_cal(calendar,&currday,&mon,&year,0,evconts);
				numrecs = load_evconts(evconts,eheight,ewidth,ev_form,date_form,
					time_form,datenum);
				numtrecs = load_todos(todoconts,theight,twidth,todo_form,
					date_form, time_form);
				break;
			case KEY_BTAB:
				clear_warn();
				win = switch_back_win(calendar,eventswin,todowin,win,
					evtitle,todotitle);
				datenum = change_cal(calendar,&currday,&mon,&year,0,evconts);
				numrecs = load_evconts(evconts,eheight,ewidth,ev_form,date_form,
					time_form,datenum);
				numtrecs = load_todos(todoconts,theight,twidth,todo_form,
					date_form, time_form);
				break;
			case 'l': case KEY_RIGHT:
				prefresh(todoconts,todopos,++todohpos,theight+3,x-twidth+2,
					y-4,x-3);
				break;
			case 'h': case KEY_LEFT:
				if (todohpos >= 1) {
					prefresh(todoconts,todopos,--todohpos,theight+3,x-twidth+2,
						y-4,x-3);
				}
				break;
			case 'j': case KEY_DOWN:
				if (todopos <= numtrecs) {
					prefresh(todoconts,++todopos,todohpos,theight+3,x-twidth+2,
						y-4,x-3);
				}
				break;
			case 'k': case KEY_UP:
				if (todopos >= 1) {
					prefresh(todoconts,--todopos,todohpos,theight+3,x-twidth+2,
						y-4,x-3);
				}
				break;
			}
		}
	}
	delwin(calendar);
	delwin(eventswin);
	delwin(evtitle);
	delwin(todotitle);
	delwin(todowin);
	endwin();
	return 0;
}

int clear_warn()
{
	int x,y,i;

	init_pair(5,allopts[WARNINGFORE].colconst,allopts[WARNINGBACK].colconst);
	getmaxyx(stdscr,y,x);
	attron(A_BOLD);
	attron(COLOR_PAIR(5));
	for (i = 0; i <= x; ++i)
		mvprintw(y-1,i," ");
	attroff(COLOR_PAIR(5));
	attroff(A_BOLD);
	return 0;
}

int print_warn(char *s)
{
	int x,y,i;

	getmaxyx(stdscr,y,x);
	init_pair(5,allopts[WARNINGFORE].colconst,allopts[WARNINGBACK].colconst);
	attron(A_BOLD);
	attron(COLOR_PAIR(5));
	mvprintw(y-1,0,"%s",s);
	attroff(COLOR_PAIR(5));
	attroff(A_BOLD);
	return 0;
}
	
int load_evconts(WINDOW *evconts,int eheight, int ewidth,
char *ev_form, char *date_form, char *time_form, int datenum)
{
	int i; int numnewlines = 0;
	FILE *outfile;
	int numrecs = 0;
	int x, y;

	getmaxyx(stdscr,y,x);
	clear_evconts(evconts);
	clear_events();
	init_pair(14,allopts[EVFORE].colconst,allopts[EVBACK].colconst);
	init_pair(15,COLOR_WHITE,allopts[EVENTBG].colconst);
	wbkgd(evconts,COLOR_PAIR(15));
	wattron(evconts,COLOR_PAIR(14));
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
	int j;
	for (j = 0; j <= x; ++j) {
		mvwprintw(evconts,i+3+numnewlines,j,"-");
		mvwprintw(evconts,i+4+numnewlines,j,"-");
	}
	prefresh(evconts,0,0,5,3,eheight,ewidth-2);
	wattroff(evconts,COLOR_PAIR(14));
	return numrecs + numnewlines;
}

int load_todos(WINDOW *todoconts,int theight, int twidth,
char *todo_form, char *date_form, char *time_form)
{
	int i; int numnewlines = 0;
	FILE *outfile;
	int numrecs = 0;
	int x, y;

	getmaxyx(stdscr,y,x);
	clear_todos();
	init_pair(18,COLOR_WHITE,allopts[TODOBG].colconst);
	wbkgd(todoconts,COLOR_PAIR(18));
	init_pair(19,allopts[TODOFORE].colconst,
		allopts[TODOBACK].colconst);
	wattron(todoconts,COLOR_PAIR(19));
	for (i = 0; i < (todonums-1); ++i) {
			fill_todo(todo_form,i,date_form,time_form,outfile);
	}
	for (i = 1; i < numtodos; ++i) {
		numnewlines += countchars(*(todolines+i),'\n');
		mvwprintw(todoconts,0+i-1+numnewlines,0,"%s",*(todolines+i));
	}
	int j;
	for (j = 0; j < x; ++j) {
		mvwprintw(todoconts,i+1+numnewlines,j,"-");
		mvwprintw(todoconts,i+2+numnewlines,j,"-");
	}
	prefresh(todoconts,0,0,theight+3,x-twidth+2,y-4,x-3);
	wattroff(todoconts,COLOR_PAIR(19));
	return numtodos + numnewlines - 3;
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

	init_pair(1,allopts[INACTIVEBORDFORE].colconst,
		allopts[INACTIVEBORDBACK].colconst);
	init_pair(6,COLOR_WHITE,allopts[CALBG].colconst);
	wbkgd(cal,COLOR_PAIR(6));
	wattron(todo,COLOR_PAIR(1));
	wattron(ev,COLOR_PAIR(1));
	wattron(cal,COLOR_PAIR(1));
	wborder(cal,ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,
		ACS_ULCORNER,ACS_URCORNER, ACS_LLCORNER,ACS_LRCORNER);
	wborder(ev,ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,
		ACS_ULCORNER,ACS_URCORNER, ACS_LLCORNER,ACS_LRCORNER);
	wborder(todo,ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,
		ACS_ULCORNER,ACS_URCORNER, ACS_LLCORNER,ACS_LRCORNER);
	wattroff(todo,COLOR_PAIR(1));
	wattroff(ev,COLOR_PAIR(1));
	wattroff(cal,COLOR_PAIR(1));
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
	init_pair(2,allopts[ACTIVEBORDFORE].colconst,
		allopts[ACTIVEBORDBACK].colconst);
	wattron(win,COLOR_PAIR(2));
	wborder(win,ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,
		ACS_ULCORNER,ACS_URCORNER, ACS_LLCORNER,ACS_LRCORNER);
	wattroff(win,COLOR_PAIR(2));
	wattroff(win,A_BOLD);
	wrefresh(win);
	init_pair(12,allopts[EVLINEFORE].colconst,
		allopts[EVLINEBACK].colconst);
	wattron(evtitle,COLOR_PAIR(12));
	wborder(evtitle,' ',' ',' ',ACS_HLINE,' ',' ',' ',' ');
	wattroff(evtitle,COLOR_PAIR(12));
	init_pair(11,allopts[TODOTITLEFORE].colconst,
		allopts[TODOTITLEBACK].colconst);
	wbkgd(todotitle,COLOR_PAIR(11));
	init_pair(13,allopts[TODOLINEFORE].colconst,
		allopts[TODOLINEBACK].colconst);
	wattron(todotitle,COLOR_PAIR(13));
	wborder(todotitle,' ',' ',' ',ACS_HLINE,' ',' ',' ',' ');
	wattroff(todotitle,COLOR_PAIR(13));
	init_pair(10,allopts[EVTITLEFORE].colconst,
		allopts[EVTITLEBACK].colconst);
	wattron(evtitle,COLOR_PAIR(10));
	center_line(evtitle,0,"Events");
	wattroff(evtitle,COLOR_PAIR(10));
	wattron(todotitle,COLOR_PAIR(11));
	center_line(todotitle,0,"Todos");
	wattroff(todotitle,COLOR_PAIR(11));
	wrefresh(evtitle);
	wrefresh(todotitle);
	return win;
}

WINDOW *switch_back_win(WINDOW *cal, WINDOW *ev, WINDOW *todo,
WINDOW *currwin, WINDOW *evtitle, WINDOW *todotitle)
{
	WINDOW *win;
	int i;

	init_pair(1,allopts[INACTIVEBORDFORE].colconst,
		allopts[INACTIVEBORDBACK].colconst);
	init_pair(6,COLOR_WHITE,allopts[CALBG].colconst);
	wbkgd(cal,COLOR_PAIR(6));
	wattron(todo,COLOR_PAIR(1));
	wattron(ev,COLOR_PAIR(1));
	wattron(cal,COLOR_PAIR(1));
	wborder(cal,ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,
		ACS_ULCORNER,ACS_URCORNER, ACS_LLCORNER,ACS_LRCORNER);
	wborder(ev,ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,
		ACS_ULCORNER,ACS_URCORNER, ACS_LLCORNER,ACS_LRCORNER);
	wborder(todo,ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,
		ACS_ULCORNER,ACS_URCORNER, ACS_LLCORNER,ACS_LRCORNER);
	wattroff(todo,COLOR_PAIR(1));
	wattroff(ev,COLOR_PAIR(1));
	wattroff(cal,COLOR_PAIR(1));
	wrefresh(cal);
	wrefresh(ev);
	wrefresh(todo);
	if (currwin == todo)
		win = cal;
	if (currwin == ev)
		win = todo;
	if (currwin == cal)
		win = ev;
	wattron(win,A_BOLD);
	init_pair(2,allopts[ACTIVEBORDFORE].colconst,
		allopts[ACTIVEBORDBACK].colconst);
	wattron(win,COLOR_PAIR(2));
	wborder(win,ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,
		ACS_ULCORNER,ACS_URCORNER, ACS_LLCORNER,ACS_LRCORNER);
	wattroff(win,COLOR_PAIR(2));
	wattroff(win,A_BOLD);
	wrefresh(win);
	init_pair(12,allopts[EVLINEFORE].colconst,
		allopts[EVLINEBACK].colconst);
	wattron(evtitle,COLOR_PAIR(12));
	wborder(evtitle,' ',' ',' ',ACS_HLINE,' ',' ',' ',' ');
	wattroff(evtitle,COLOR_PAIR(12));
	init_pair(11,allopts[TODOTITLEFORE].colconst,
		allopts[TODOTITLEBACK].colconst);
	wbkgd(todotitle,COLOR_PAIR(11));
	init_pair(13,allopts[TODOLINEFORE].colconst,
		allopts[TODOLINEBACK].colconst);
	wattron(todotitle,COLOR_PAIR(13));
	wborder(todotitle,' ',' ',' ',ACS_HLINE,' ',' ',' ',' ');
	wattroff(todotitle,COLOR_PAIR(13));
	init_pair(10,allopts[EVTITLEFORE].colconst,
		allopts[EVTITLEBACK].colconst);
	wattron(evtitle,COLOR_PAIR(10));
	center_line(evtitle,0,"Events");
	wattroff(evtitle,COLOR_PAIR(10));
	wattron(todotitle,COLOR_PAIR(11));
	center_line(todotitle,0,"Todos");
	wattroff(todotitle,COLOR_PAIR(11));
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
	init_pair(3,allopts[TITLEFORE].colconst,
		allopts[TITLEBACK].colconst);
	attron(A_BOLD);
	attron(COLOR_PAIR(3));
	mvprintw(0,0,"%s",lftstr);
	for (i = lenlft; i <= (x - lenrgt - 1); ++i)
		mvprintw(0,i," ");
	mvprintw(0,i,"%s",rgtstr);
	attroff(A_BOLD);
	attroff(COLOR_PAIR(3));
	return 0;
}

int make_botbar()
{
	int x, y,lenlft,lenrgt, i;
	char *lftstr = "q:QUIT | TAB/SHFT-TAB:switch windows | k/j:UP/DOWN | "
		"h/l:LEFT/RIGHT";
	char *rgtstr = " ";

	getmaxyx(stdscr,y,x);
	lenlft = strlen(lftstr);
	lenrgt = strlen(rgtstr);
	init_pair(4,allopts[BOTFORE].colconst,
		allopts[BOTBACK].colconst);
	attron(A_BOLD);
	attron(COLOR_PAIR(4));
	mvprintw(y-2,0,"%s",lftstr);
	for (i = lenlft; i <= (x - lenrgt - 1); ++i)
		mvprintw(y-2,i," ");
	mvprintw(y-2,i,"%s",rgtstr);
	attroff(COLOR_PAIR(4));
	attroff(A_BOLD);
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
	init_pair(20,allopts[CALFORE].colconst,allopts[CALBACK].colconst);
	wattron(win,COLOR_PAIR(20));
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
	wattroff(win,COLOR_PAIR(20));
	date->tm_mday = currday + 1; date->tm_mon -= 1; mktime(date);
	return get_datenum(date);
}

int print_monline(WINDOW *win,int mon, int year)
{
	char month[24];
	char buf[5];

	init_pair(9,allopts[CALTITLEFORE].colconst,
		allopts[CALTITLEBACK].colconst);
	wattron(win,COLOR_PAIR(9));
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
	wattroff(win,COLOR_PAIR(9));
	return 0;
}

int print_wdayline(WINDOW *win,int fdow)
{
	init_pair(8,allopts[CALWEEKFORE].colconst,
		allopts[CALWEEKBACK].colconst);
	wattron(win,COLOR_PAIR(8));
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
	wattroff(win,COLOR_PAIR(8));
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

int equalize_colors()
{
	int i;

	for (i = 1; i < numopts; ++i) {
		if (allopts[i].r > 499)
			allopts[i].r = 1000;
		else
			allopts[i].r = 0;
		if (allopts[i].g > 499)
			allopts[i].g = 1000;
		else
			allopts[i].g = 0;
		if (allopts[i].b > 499)
			allopts[i].b = 1000;
		else
			allopts[i].b = 0;
		if ((allopts[i].r == 0) && (allopts[i].g == 0) &&
		(allopts[i].b == 0))
			allopts[i].colconst = COLOR_BLACK;
		if ((allopts[i].r == 1000) && (allopts[i].g == 0) &&
		(allopts[i].b == 0))
			allopts[i].colconst = COLOR_RED;
		if ((allopts[i].r == 0) && (allopts[i].g == 1000) &&
		(allopts[i].b == 0))
			allopts[i].colconst = COLOR_GREEN;
		if ((allopts[i].r == 0) && (allopts[i].g == 0) &&
		(allopts[i].b == 1000))
			allopts[i].colconst = COLOR_BLUE;
		if ((allopts[i].r == 1000) && (allopts[i].g == 1000) &&
		(allopts[i].b == 0))
			allopts[i].colconst = COLOR_YELLOW;
		if ((allopts[i].r == 0) && (allopts[i].g == 1000) &&
		(allopts[i].b == 1000))
			allopts[i].colconst = COLOR_CYAN;
		if ((allopts[i].r == 1000) && (allopts[i].g == 1000) &&
		(allopts[i].b == 1000))
			allopts[i].colconst = COLOR_WHITE;
		if ((allopts[i].r == 1000) && (allopts[i].g == 0) &&
		(allopts[i].b == 1000))
			allopts[i].colconst = COLOR_MAGENTA;
	}
	print_warn("WARNING:  Terminal does not support changing "
		"colors; using built-in colors...");
	return 0;
}

int define_colors()
{
	init_color(COL_WHOLEBG,allopts[WHOLEBG].r,
		allopts[WHOLEBG].g,allopts[WHOLEBG].b);
	allopts[WHOLEBG].colconst = COL_WHOLEBG;
	init_color(COL_CALBG,allopts[CALBG].r,
		allopts[CALBG].g,allopts[CALBG].b);
	allopts[CALBG].colconst = COL_CALBG;
	init_color(COL_EVENTBG,allopts[EVENTBG].r,
		allopts[EVENTBG].g,allopts[EVENTBG].b);
	allopts[EVENTBG].colconst = COL_EVENTBG;
	init_color(COL_TODOBG,allopts[TODOBG].r,
		allopts[TODOBG].g,allopts[TODOBG].b);
	allopts[TODOBG].colconst = COL_TODOBG;
	init_color(COL_CALTITLEFORE,allopts[CALTITLEFORE].r,
		allopts[CALTITLEFORE].g,allopts[CALTITLEFORE].b);
	allopts[CALTITLEFORE].colconst = COL_CALTITLEFORE;
	init_color(COL_CALTITLEBACK,allopts[CALTITLEBACK].r,
		allopts[CALTITLEBACK].g,allopts[CALTITLEBACK].b);
	allopts[CALTITLEBACK].colconst = COL_CALTITLEBACK;
	init_color(COL_CALWEEKFORE,allopts[CALWEEKFORE].r,
		allopts[CALWEEKFORE].g,allopts[CALWEEKFORE].b);
	allopts[CALWEEKFORE].colconst = COL_CALWEEKFORE;
	init_color(COL_CALWEEKBACK,allopts[CALWEEKBACK].r,
		allopts[CALWEEKBACK].g,allopts[CALWEEKBACK].b);
	allopts[CALWEEKBACK].colconst = COL_CALWEEKBACK;
	init_color(COL_CALFORE,allopts[CALFORE].r,
		allopts[CALFORE].g,allopts[CALFORE].b);
	allopts[CALFORE].colconst = COL_CALFORE;
	init_color(COL_CALBACK,allopts[CALBACK].r,
		allopts[CALBACK].g,allopts[CALBACK].b);
	allopts[CALBACK].colconst = COL_CALBACK;
	init_color(COL_TODOTITLEFORE,allopts[TODOTITLEFORE].r,
		allopts[TODOTITLEFORE].g,allopts[TODOTITLEFORE].b);
	allopts[TODOTITLEFORE].colconst = COL_TODOTITLEFORE;
	init_color(COL_TODOTITLEBACK,allopts[TODOTITLEBACK].r,
		allopts[TODOTITLEBACK].g,allopts[TODOTITLEBACK].b);
	allopts[TODOTITLEBACK].colconst = COL_TODOTITLEBACK;
	init_color(COL_TODOLINEFORE,allopts[TODOLINEFORE].r,
		allopts[TODOLINEFORE].g,allopts[TODOLINEFORE].b);
	allopts[TODOLINEFORE].colconst = COL_TODOLINEFORE;
	init_color(COL_TODOLINEBACK,allopts[TODOLINEBACK].r,
		allopts[TODOLINEBACK].g,allopts[TODOLINEBACK].b);
	allopts[TODOLINEBACK].colconst = COL_TODOLINEBACK;
	init_color(COL_TODOFORE,allopts[TODOFORE].r,
		allopts[TODOFORE].g,allopts[TODOFORE].b);
	allopts[TODOFORE].colconst = COL_TODOFORE;
	init_color(COL_TODOBACK,allopts[TODOBACK].r,
		allopts[TODOBACK].g,allopts[TODOBACK].b);
	allopts[TODOBACK].colconst = COL_TODOBACK;
	init_color(COL_EVTITLEFORE,allopts[EVTITLEFORE].r,
		allopts[EVTITLEFORE].g,allopts[EVTITLEFORE].b);
	allopts[EVTITLEFORE].colconst = COL_EVTITLEFORE;
	init_color(COL_EVTITLEBACK,allopts[EVTITLEBACK].r,
		allopts[EVTITLEBACK].g,allopts[EVTITLEBACK].b);
	allopts[EVTITLEBACK].colconst = COL_EVTITLEBACK;
	init_color(COL_EVLINEFORE,allopts[EVLINEFORE].r,
		allopts[EVLINEFORE].g,allopts[EVLINEFORE].b);
	allopts[EVLINEFORE].colconst = COL_EVLINEFORE;
	init_color(COL_EVLINEBACK,allopts[EVLINEBACK].r,
		allopts[EVLINEBACK].g,allopts[EVLINEBACK].b);
	allopts[EVLINEBACK].colconst = COL_EVLINEBACK;
	init_color(COL_EVFORE,allopts[EVFORE].r,
		allopts[EVFORE].g,allopts[EVFORE].b);
	allopts[EVFORE].colconst = COL_EVFORE;
	init_color(COL_EVBACK,allopts[EVBACK].r,
		allopts[EVBACK].g,allopts[EVBACK].b);
	allopts[EVBACK].colconst = COL_EVBACK;
	init_color(COL_TITLEFORE,allopts[TITLEFORE].r,
		allopts[TITLEFORE].g,allopts[TITLEFORE].b);
	allopts[TITLEFORE].colconst = COL_TITLEFORE;
	init_color(COL_TITLEBACK,allopts[TITLEBACK].r,
		allopts[TITLEBACK].g,allopts[TITLEBACK].b);
	allopts[TITLEBACK].colconst = COL_TITLEBACK;
	init_color(COL_BOTFORE,allopts[BOTFORE].r,
		allopts[BOTFORE].g,allopts[BOTFORE].b);
	allopts[BOTFORE].colconst = COL_BOTFORE;
	init_color(COL_BOTBACK,allopts[BOTBACK].r,
		allopts[BOTBACK].g,allopts[BOTBACK].b);
	allopts[BOTBACK].colconst = COL_BOTBACK;
	init_color(COL_WARNINGFORE,allopts[WARNINGFORE].r,
		allopts[WARNINGFORE].g,allopts[WARNINGFORE].b);
	allopts[WARNINGFORE].colconst = COL_WARNINGFORE;
	init_color(COL_WARNINGBACK,allopts[WARNINGBACK].r,
		allopts[WARNINGBACK].g,allopts[WARNINGBACK].b);
	allopts[WARNINGBACK].colconst = COL_WARNINGBACK;
	init_color(COL_INACTIVEBORDFORE,allopts[INACTIVEBORDFORE].r,
		allopts[INACTIVEBORDFORE].g,allopts[INACTIVEBORDFORE].b);
	allopts[INACTIVEBORDFORE].colconst = COL_INACTIVEBORDFORE;
	init_color(COL_INACTIVEBORDBACK,allopts[INACTIVEBORDBACK].r,
		allopts[INACTIVEBORDBACK].g,allopts[INACTIVEBORDBACK].b);
	allopts[INACTIVEBORDBACK].colconst = COL_INACTIVEBORDBACK;
	init_color(COL_ACTIVEBORDFORE,allopts[ACTIVEBORDFORE].r,
		allopts[ACTIVEBORDFORE].g,allopts[ACTIVEBORDFORE].b);
	allopts[ACTIVEBORDFORE].colconst = COL_ACTIVEBORDFORE;
	init_color(COL_ACTIVEBORDBACK,allopts[ACTIVEBORDBACK].r,
		allopts[ACTIVEBORDBACK].g,allopts[ACTIVEBORDBACK].b);
	allopts[ACTIVEBORDBACK].colconst = COL_ACTIVEBORDBACK;
	return 0;
}
