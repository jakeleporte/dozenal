/* +AMDG */ 
#include<stdio.h>
#include<stdlib.h>
#include"dozbc.h"

char line[256];

int xdozbc(int num, char *args[])
{
	FD_calculator *calc;
	Window whole;
	
	fl_initialize(&num,args,"xdozbc",0,0);
	calc = create_form_calculator();
	whole = fl_show_form(calc->calculator,FL_PLACE_MOUSE,
		FL_FULLBORDER,"xdozbc");
	line[0] = '\0';
	fl_do_forms();
	fl_finish();
	return 0;
}

int check_len()
{
	if (strlen(line) > 254) {
		fl_show_messages("ERROR:  Too many characters in line");
		return 1;
	}
	return 0;
}

/* returns 0 if character's in the last word, 1 if not */
int in_curr_word(char c)
{
	int ind;
	int i;

	ind = strlen(line);
	for (i = ind; line[i] != ' ' && i >= 0; --i);
	i++;
	if (strchr(line+i,c)) {
		return 0;
	}
	return 1;
}

void proc_num( FL_OBJECT * button, long arg )
{
	int index;
	char c[2];
	FD_calculator *fd_foo = button->form->fdui;

	index = strlen(line);
	if (arg == '-') {
		if ((index != 0) && (line[index-1] != ' ')) {
			return;
		}
	}
	if (arg == ';') {
		if (in_curr_word(';') == 0) {
			return;
		}
	}
	line[index] = arg;
	line[index+1] = '\0';
	fl_set_object_label(fd_foo->ansfield,line);
}

void operator( FL_OBJECT * button, long arg )
{
	int index;
	FD_calculator *fd_foo = button->form->fdui;

	index = strlen(line);
	if ((arg == '+') || (arg == '-') || (arg == '*') ||
	(arg == '/') || (arg == '^') || (arg == '%') ||
	(arg == '!')) {
		line[index] = ' ';
		line[index+1] = arg;
		line[index+2] = ' ';
		line[index+3] = '\0';
	} else {
		switch (arg) {
		case 's': /* sine */
			strcat(line," sin(");
			break;
		case 'c': /* cosine */
			strcat(line," cos(");
			break;
		case 't': /* tangent */
			strcat(line," tan(");
			break;
		case 'S': /* arcsin */
			strcat(line," asin(");
			break;
		case 'C': /* arccosine */
			strcat(line," acos(");
			break;
		case 'T': /* arctangent */
			strcat(line," atan(");
			break;
		case 'h': /* hyperbolic sine */
			strcat(line," sinh(");
			break;
		case 'H': /* hyperbolic cosine */
			strcat(line," cosh(");
			break;
		case 'y': /* hyperbolic tangent */
			strcat(line," tanh(");
			break;
		case 'l': /* dozenal log */
			strcat(line," log(");
			break;
		case 'x': /* logx */
			strcat(line," logx(");
			break;
		case 'D': /* dublog */
			strcat(line," dlg(");
			break;
		case 'r': /* reciprocal */
			strcat(line," recip(");
			break;
		case 'n': /* natural logs */
			strcat(line," nl(");
			break;
		case 'b': /* arbitrary base logs */
			strcat(line," logb(");
			break;
		case 'v': /* square root */
			strcat(line," v(");
			break;
		case 'g': /* gcf */
			strcat(line," gcf(");
			break;
		case 'L':
			strcat(line," lcm(");
			break;
		}
	}
	fl_set_object_label(fd_foo->ansfield,line);
}

void grouping( FL_OBJECT * button, long arg )
{
}

void erase( FL_OBJECT * button, long arg )
{
	FD_calculator *fd_foo = button->form->fdui;
	int len = 0;

	if (arg == 'c') {
		line[0] = '\0';
	}
	if (arg == '<') {
		len = strlen(line);
		while (line[len] == ' ')
			--len;
		if (line[len-1] == '(') {
			while ((line[len] != ' ') && (len >= 0))
				--len;
			++len;
		} else {
			--len;
		}
		while (line[len] == ' ')
			--len;
		if (len < 0) len = 0;
		line[len] = '\0';
	}
	fl_set_object_label(fd_foo->ansfield,line);
}

void unitangle( FL_OBJECT * button, long arg )
{
}

void memory( FL_OBJECT * button, long arg )
{
}
