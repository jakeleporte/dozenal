/* +AMDG */
/*
 * The Xforms visual interface for dozdc.
 *
 * (C) Copyright 2016 Donald P. Goodman III
 *
 * This file is part of dozdc.
 *
 * dozdc is free software:  you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any
 * later version.
 *
 * dozdc is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with dozdc.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include<stdio.h>
#include<stdlib.h>
#include<float.h>
#include"dozbc.h"
#include"dozdc.h"

#define LINELEN 256

char line[LINELEN];
char memline[LINELEN];
int places = 4;
char angletype = 'z';

double commandcalc(char *word, int type, int places, char expnot);

int xdozbc(int num, char *args[])
{
	FD_calculator *calc;
	Window whole;
	Window othwhole;

	memline[0] = '\0';
	fl_initialize(&num,args,"xdozbc",0,0);
	calc = create_form_calculator();

	Pixmap mask; int w; int h;
	Pixmap pm = fl_read_pixmapfile(fl_root,"logo_shapes_dozenal.xpm",
		&w, &h, NULL, NULL, NULL, 0);
	fl_set_form_icon(calc->calculator,pm,None);

	whole = fl_show_form(calc->calculator,FL_PLACE_MOUSE,
		FL_FULLBORDER,"xdozbc");
	fl_set_object_return(calc->precisionval,FL_RETURN_CHANGED);
	fl_set_spinner_bounds(calc->precisionval,FL_nint(0.0),
		FL_nint(15.0));
	fl_set_spinner_step(calc->precisionval,FL_nint(1.0));
	fl_set_spinner_value(calc->precisionval,FL_nint(4.0));
	fl_set_object_helper(calc->comma,"Separates arguments to "
		"functions\nShortcut:  ','");
	fl_set_object_helper(calc->dit,"The fractional point\n"
		"Shortcut:  ';'");
	fl_set_object_helper(calc->neg,"A negative sign\n"
		"Shortcut:  'n'");
	fl_set_object_helper(calc->exp,"Use exponential notation; "
		"separates integral from mantissa\n"
		"Shortcut:  'E'");
	fl_set_object_helper(calc->div,"Division\n"
		"Shortcut:  '/'");
	fl_set_object_helper(calc->times,"Multiplication\n"
		"Shortcut:  '*'");
	fl_set_object_helper(calc->minus,"Subtraction\n"
		"Shortcut:  '-'");
	fl_set_object_helper(calc->plus,"Addition\n"
		"Shortcut:  '+'");
	fl_set_object_helper(calc->equals,"Equals; evaluates the "
		"expression and prints the answer\n"
		"Shortcut:  '='");
	fl_set_object_helper(calc->sqrt,"Square root\n"
		"Shortcut:  'v'");
	fl_set_object_helper(calc->expon,"Exponentiation; raises "
		"one power by another\n"
		"Shortcut:  '^'");
	fl_set_object_helper(calc->closeparen,"Close parentheses; "
		"standard grouping symbol\n"
		"Shortcut:  ')'");
	fl_set_object_helper(calc->openparen,"Open parentheses; "
		"standard grouping symbol\n"
		"Shortcut:  '('");
	fl_set_object_helper(calc->mod,"Modules; like division, "
		"but yields the remainder, not the quotient\n"
		"Shortcut:  '%'");
	fl_set_object_helper(calc->sin,"Sine\n"
		"Shortcut:  's'");
	fl_set_object_helper(calc->cosine,"Cosine\n"
		"Shortcut:  'c'");
	fl_set_object_helper(calc->tangent,"Tangent\n"
		"Shortcut:  't'");
	fl_set_object_helper(calc->asin,"Arcsin\n"
		"Shortcut:  'S'");
	fl_set_object_helper(calc->acos,"Arccosine\n"
		"Shortcut:  'C'");
	fl_set_object_helper(calc->atan,"Arctangent\n"
		"Shortcut:  'T'");
	fl_set_object_helper(calc->atantwo,"Arctangent2\n"
		"takes two arguments and takes the arctangent of "
		"each to determine the proper quadrant\n"
		"Shortcut:  'N'");
	fl_set_object_helper(calc->hysin,"Hyperbolic sine\n"
		"Shortcut:  'h'");
	fl_set_object_helper(calc->hycos,"Hyperbolic cosine\n"
		"Shortcut:  'H'");
	fl_set_object_helper(calc->hytan,"Hyperbolic tangent\n"
		"Shortcut:  'y'");
	fl_set_object_helper(calc->dozlog,"Logarithm (to base twelve)\n"
		"Shortcut:  'l'");
	fl_set_object_helper(calc->declog,"Base-X logarithm\n"
		"Shortcut:  'x'");
	fl_set_object_helper(calc->natlog,"Natural logarithm\n"
		"Shortcut:  'n'");
	fl_set_object_helper(calc->baselog,"Logarithm to an "
		"arbitrary base; first argument is the value, second "
		"the base\n"
		"Shortcut:  'b'");
	fl_set_object_helper(calc->dublog,"Base-two logarithm (\"dublog\")\n"
		"Shortcut:  'D'");
	fl_set_object_helper(calc->recip,"Reciprocal\n"
		"Shortcut:  'r'");
	fl_set_object_helper(calc->clear,"Clear the problem field\n"
		"Shortcut:  'w'");
	fl_set_object_helper(calc->backspace,"Clear the rightmost term\n"
		"Shortcut:  '<'");
	fl_set_object_helper(calc->factorial,"Factorial\n"
		"Shortcut:  '!'");
	fl_set_object_helper(calc->pi,"Pi; inserts value of pi\n"
		"Shortcut:  'p'");
	fl_set_object_helper(calc->euler,"Inserts value of "
		"Euler's constant\n"
		"Shortcut:  'u'");
	fl_set_object_helper(calc->angleunit,"Sets type of angle "
		"to be used:  unciaPis, radians, or degrees\n"
		"Shortcut:  'z'");
	fl_set_object_helper(calc->greatcommfact,"Yields the "
		"greatest common factor of its two arguments\n"
		"Shortcut:  'g'");
	fl_set_object_helper(calc->leastcommult,"Yields the "
		"least common multiple of its two arguments\n"
		"Shortcut:  'L'");
	fl_set_object_helper(calc->memappend,"Appends the problem "
		"field's contents to memory\n"
		"Shortcut:  'A'");
	fl_set_object_helper(calc->memadd,"Adds the current "
		"contents to memory to the problem field\n"
		"Shortcut:  'a'");
	fl_set_object_helper(calc->memrep,"Replaces the current "
		"contents of the problem field with the contents of "
		"memory\n"
		"Shortcut:  'R'");
	fl_set_object_helper(calc->clearmem,"Wipes the current "
		"contents of memory\n"
		"Shortcut:  'k'");
	line[0] = '\0';
	fl_do_forms();
//	fl_finish();
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
	char rpn[LINELEN];
	char infix[LINELEN];
	char word[LINELEN];
	int type = NUM;
	int numrun = 0;
	double answer;
	int i; int j = 0;

	FD_calculator *fd_foo = button->form->fdui;

	index = strlen(line);
	if ((arg == '+') || (arg == '-') || (arg == '*') ||
	(arg == '/') || (arg == '^') || (arg == '%') ||
	(arg == '!') || (arg == ',')) {
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
		case 'N': /* atan2 */
			strcat(line," atan2(");
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
		case '=':
			regularize_line();
			shunt(rpn,line);
			line[0] = '\0';
			line[0] = angletype; line[1] = ' '; line[2] = '\0';
			strcat(line,rpn);
			index = strlen(line);
			line[index] = ' ';
			line[index+1] = '=';
			line[index+2] = ' ';
			line[index+3] = '\0';
			numrun = 0;
			while ((type = graphops(line,word,&numrun)) != EOF) {
				answer = commandcalc(word, type, places, 0);
			}
			sprintf(word,"%.*f",DBL_MAX_10_EXP,answer);
			doz(word,word,places,0);
			for (i = 0; word[i] != ';' && word[i] != '\0'; ++i);
			if (word[i] == ';') {
				for (j = 0;  j < places; ++j)
					++i;
				word[++i] = '\0';
			}
			line[0] = '\0';
			strcpy(line,word);
			break;
		}
	}
	fl_set_object_label(fd_foo->ansfield,line);
}

int regularize_line()
{
	int len;
	int i,j;
	char fixed[LINELEN];

	len = strlen(line);
	fixed[0] = '\0';
	j = 0;
	for (i = 0; line[i] != '\0'; ++i) {
		if (line[i] == '(') {
			fixed[j++] = ' ';
			fixed[j++] = '(';
			fixed[j++] = ' ';
		} else if (line[i] == ')') {
			fixed[j++] = ' ';
			fixed[j++] = ')';
			fixed[j++] = ' ';
		} else {
			fixed[j++] = line[i];
		}
	}
	fixed[j] = '\0';
	line[0] = '\0';
	strcpy(line,fixed);
	j = 0; fixed[j] = '\0';
	for (i = 0; line[i] != '\0'; ++i) {
		if (line[i] == ' ') {
			if (line[i-1] != ' ') {
				fixed[j++] = line[i];
			}
		} else {
			fixed[j++] = line[i];
		}
	}
	fixed[j] = '\0';
	line[0] = '\0';
	strcpy(line,fixed);
	return 0;
}

void grouping( FL_OBJECT * button, long arg )
{
	FD_calculator *fd_foo = button->form->fdui;
	int index;

	index = strlen(line);
	if (arg == '(') {
		line[index] = ' ';
		line[index+1] = arg;
		line[index+2] = '\0';
	} else if (arg == ')') {
		line[index] = arg;
		line[index+1] = '\0';
	}
	fl_set_object_label(fd_foo->ansfield,line);
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
	FD_calculator *fd_foo = button->form->fdui;
	int index;

	if (angletype == 'd') {
		operate(ZENIPI,&places,PRINT);
		fl_set_object_label(button,"Z/r/d");
		angletype = 'z';
	} else if (angletype == 'z') {
		operate(RADIANS,&places,PRINT);
		fl_set_object_label(button,"z/R/d");
		angletype = 'r';
	} else if (angletype == 'r') {
		operate(DEGREES,&places,PRINT);
		fl_set_object_label(button,"z/r/D");
		angletype = 'd';
	}
}

void memory( FL_OBJECT * button, long arg )
{
	FD_calculator *fd_foo = button->form->fdui;
	int index;
	int i, j;

	index = strlen(line);
	if (arg == '+') { /* append line to memory */
		if ((strlen(memline) + index) > LINELEN) {
			fprintf(stderr,"dozdc:  line is too long for memory to "
			"be appended to it; adding maximum number of "
			"characters...\n");
		}
		for (i = strlen(memline), j = 0; (i < LINELEN) && 
		(line[j] != '\0'); ++i, ++j)
			memline[i] = line[j];
		memline[i] = '\0';
		fprintf(stderr,"dozdc:  memory contents: \"%s\"\n",memline);
	} else if (arg == 'A') { /* append memory to line */
		if ((strlen(memline) + index) > LINELEN) {
			fprintf(stderr,"dozdc:  memory is too long for line to "
			"be appended to it; adding maximum number of "
			"characters...\n");
		}
		for (i = index, j = 0; (i < LINELEN) && (memline[j] != '\0'); 
		++i, ++j)
			line[i] = memline[j];
		line[i] = '\0';
		fprintf(stderr,"dozdc:  memory contents: %s\n",memline);
	} else if (arg == 'r') { /* replace current line with memory */
		line[0] = '\0';
		strcpy(line,memline);
	} else if (arg == 'c') { /* clears memory */
		memline[0] = '\0';
	}
	fl_set_object_label(fd_foo->ansfield,line);
}

void set_prec(FL_OBJECT *spinner, long arg)
{
	places = (int) fl_get_spinner_value(spinner);
}

void quitfunc(FL_OBJECT *button, long arg)
{
	fl_finish();
	exit(0);
}


