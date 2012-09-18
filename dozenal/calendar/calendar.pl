#!/usr/bin/perl
# +AMDG  This document was begun on 8 Sept 11E8, the feast
# of the Nativity of the Blessed Virgin Mary and the Comm.
# of St. Hadrian, Martyr, and it is humbly dedicated to them
# for their prayers, and to the Sacred Heart of Jesus for
# His mercy.

use strict;
use POSIX;
use Data::Dumper::Simple;
use String::Escape qw (unbackslash);
use Time::Piece;
use Date::Day;
use Date::Easter;
use Date::Pcalc qw(Add_Delta_Days
	Date_to_Days leap_year);
use Getopt::Std;
getopts('f:d:o:');
our($opt_f,$opt_d,$opt_o);

# define our exit codes

my $SUCCESS = 0;
my $BAD_INPUT_FILE = 1;
my $INPUT_FILE_NOT_EXIST = 2;
my $BAD_OUTPUT_FORMAT = 3;

# change to dozenal digits; takes the scalar integer,
# returnst he dozenal digit character

sub dozenize($)
{
	if (($_[0] >= 0) && ($_[0] <= 9)) {
		return $_[0];
	} else {
		return 'X' if ($_[0] == 10);
		return 'E' if ($_[0] == 11);
	}
}

# convert integers from decmial to dozenal; takes the scalar
# integer, returns the scalar string

sub doz_int($)
{
	my $decnum = $_[0];
	my $holder = 1;
	my $doznum = "";

	while ($decnum >= 12) {
		$holder = $decnum % 12;
		$holder = dozenize($holder);
		$doznum .= $holder;
		$decnum /= 12;
	}
	$holder = $decnum % 12;
	$holder = dozenize($holder);
	$doznum .= $holder;
	return scalar reverse($doznum);
}

# converts single dozenal digits to decimal values; takes a
# scalar dozenal digit, returns the scalar decimal digit

sub decimalize($)
{
	if ($_[0] eq 'X') {
		return 10;
	} elsif ($_[0] eq 'E') {
		return 11;
	} else {
		return $_[0];
	}
}

# converts dozenal integers into decimal integers; takes the
# dozenal integer as a scalar, returns the decimal integer
# as a scalar

sub dec_int($)
{
	my @digits;
	my $len;
	my $decnum;
	my $exp = 0;

	@digits = split(//,$_[0]);
	$exp = $#digits;
	foreach my $var (@digits) {
		$decnum += decimalize($var) * (12**($exp--));
	}
	return $decnum;
}

# define our mod functions; both take two arguments, x and
# y, and return an integer

sub mod($$)
{
	return $_[0] - $_[1] * ($_[0] / $_[1]);
}
sub amod($$)
{
	return $_[1] + mod($_[0],-$_[1]);
}

# get the julian date; takes year, month, day

sub julday($$$)
{
	return 1721423.5 + Date_to_Days($_[0],$_[1],$_[2]) + 1;
}

# convert julian date back to gregorian date; takes the
# julian day, returns an array of year, month, day

sub jultogreg($)
{
	return Add_Delta_Days(1,1,1,$_[0] - 1721423.5 - 2);
}

# define @calendar; this array eats the contents of our
# data file

my $calfile;
my @calendar;

# define @eventlist; this array takes the calendar data,
# converted into absolute dates

my @eventlist;

# define arrays to hold the dates grouped by various
# criteria

my @callist;
my @monthlist;
my @weeklist;
my @daylist;

# define date format default; command line option or file
# option can change

my $dateformat = "%d %b %Y";

# define layouts; an array of strings; each string
# is formatted "output-type, type, formatstring"

my @layouts = (
	"text, event, %d: %t: %n\\n",
	"text, special, %d: %n\\n"
);

# option handling from config file; takes the line involved
# (starts with "%") and fills the appropriate value in the
# options hash; returns nothing

sub config_opt($)
{
	my $var; my $ovar; my $finish;

	if ($_ =~ /^%DATEFORM/) {
		($dateformat) = ($_ =~ /^%DATEFORM:\s(.*)\s$/);
	} elsif ($_ =~ /^%FORM_([A-Z]+)\s+(\w+)\s+"(.*)"$/) {
		$var = lc($1); $ovar = $2; $finish = $3;
		for (my $i = 0; $i <= $#layouts; $i++) {
			if ($layouts[$i] =~ /$var, $ovar/) {
				$layouts[$i] =~ s/($var, $ovar,\s*).*/$1 $finish/;
			}
		}
	}
}

# takes a filehandle; returns no value; populates @calendar

sub popsched(*)
{
	my $i = 0;
	my $j = 0;
	my $k = 0;
	my @row = ();			# placeholder to feed into @calndar
	open($calfile,"<","$_[0]") || die $!;
	while (<$calfile>) {
		if ($_ =~ /^%/) {
			config_opt($_);
		}
		$k++;
		if ($_ !~ /^#/) {
			if ($_ =~ /(.*)\t(.*)\t(.*)\t(.*)\t(.*)/) {
				@row = ($_ =~ /(.*)\t(.*)\t(.*)\t(.*)\t(.*)/);
				push @{$calendar[$i]},@row if $_ !~ /^#/;
				$i++;
			}
		} elsif ($_ =~ /^#/) {
			next;
		} else {
			print STDERR "dozcal error:  malformation in data ";
			print STDERR "file $_[0] at line $k\n";
			exit $BAD_INPUT_FILE;
		}
	}
	close $calfile;
}

sub use_input_file()
{
	if ($opt_f) {
		if (!-e $opt_f) {
			print STDERR "dozcal error:  data file $opt_f ";
			print STDERR "does not exist\n";
			exit $INPUT_FILE_NOT_EXIST;
		} else {
			popsched($opt_f);
		}
	} else {
		popsched('sampdata');
	}
}

# takes the first and last days of a range and returns a
# list of all the dates between them, including them
# themselves

sub fill_range($$)
{
	my $firstmon = -1;		# first month in range
	my $lastmon = -1;			# second month in range
	my $firstyear = -1;		# first year in range
	my $lastyear = -1;		# last year in range
	my $firstday = -1;		# first day in range
	my $lastday = -1;			# last day in range
	my @range = ();			# range of dates to return

	my @months = qw( Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec Irv );
	for (my $i = 0; $i < 13; $i++) {
		$firstmon = $i if ($_[0] =~ /$months[$i]/);
		$lastmon = $i if ($_[1] =~ /$months[$i]/);
	}
	$firstmon = $lastmon if (($firstmon == -1) && ($lastmon > -1));
	$lastmon = $firstmon if (($firstmon > -1) && ($lastmon == -1));
	$firstyear = $1 if $_[0] =~ /([\dXE]{4,4})/;
	$lastyear = $1 if $_[1] =~ /([\dXE]{4,4})/;
	$firstyear = $lastyear if (($firstyear == -1) && ($lastyear > -1));
	$lastyear = $firstyear if (($firstyear > -1) && ($lastyear == -1));
	$firstday = $1 if $_[0] =~ /([\d\dXE]{1,2})/;
	$lastday = $1 if $_[1] =~ /([\d\dXE]{1,2})/;
	$firstday = dec_int($firstday);
	$lastday = dec_int($lastday);
	$firstyear = dec_int($firstyear);
	$lastyear = dec_int($lastyear);
	$firstmon++;
	$lastmon++;
	$firstday = julday($firstyear,$firstmon,$firstday);
	$lastday = julday($lastyear,$lastmon,$lastday);
	my $i = 0;
	$range[$i++] = $firstday++ while $firstday <= $lastday;
	return @range;
}

# before passing to the range and list functions (if
# applicable), parse the date and put it into a standard
# form (e.g., 4 Mar 11E8); accepts variety of dates in
# little-endian or big-endian formats, but not the strange
# American way; requires four-digit year; returns a string,
# or -1 if a valid date isn't found

sub parse_dates($)
{
	my $flag = 0;					# set to 1 if found valid date
	my $temp = $_[0];				# variable to deal with in calcs
	my $year = -1;
	my $month = -1;
	my $day = -1;
	my $standate = -1;
	my @months = qw( Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec Irv );
	my $t = localtime;

	if ($temp =~ /([\dXE]{2,4})[-|\/]([\dXE]{1,2})[-\/]([\dXE]{1,2})/) {
		$flag = 1;
		($year,$month,$day) = ($1,$2,$3);
	} elsif ($temp =~ /(\w{3,9}).*([\dXE]{1,2}).*,.*([\dXE]{2,4})/) {
		$flag = 1;
		($year,$month,$day) = ($3,$1,$2);
	} elsif ($temp =~ /([\dXE]{1,2})[-|\/]([\dXE]{1,2})[-\/]([\dXE]{2,4})/) {
		$flag = 1;
		($year,$month,$day) = ($3,$1,$2);
	} else {
		my $i;
		foreach my $var (@months) {
			$i++;
			next if ($temp !~ /$var/);
			$month = $i if $i < 13;
			$month = 1 if $month == -1;
			if ($temp =~ /([\dXE]{4,4})/) {
				$year = $1;
			} else {
				$year = $t->year;
				$year = doz_int($year);
			}
			if ($temp =~ /([\dXE]{1,2})/) {
				$day = $1;
			} else {
				$day = $t->mday;
				$day = doz_int($day);
			}
			$standate =  "$day $months[$month-1] $year";
		}
	}
	if ($flag == 1) {
		$month = "Oct" if $month eq "X" || $month eq "0X";
		$month = "Nov" if $month eq "E" || $month eq "0E";
		$month = "Dec" if $month eq "10";
		if ($month =~ /[\dXE]+/) {
			$month--;
			$month = $months[$month];
		}
		$standate = $day." ".$month." ".$year;
	}
	return $standate;
}

# takes an individual date as scalar string, returns it as
# julian day

sub ind_date($)
{
	my $year;
	my $month;
	my $day = 1;
	my @months = qw( Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec Irv );
	my $t = localtime;

	for (my $i = 0; $i < 13; $i++) {
		$month = $i if ($_[0] =~ /$months[$i]/);
	}
	if ($_[0] =~ /([\dXE]{4,4})/) {
		$year = $1;
	} else {
		$year = $t->year;
		$year = doz_int($year);
	}
	$day = $1 if $_[0] =~ /([\d\dXE]{1,2})/;
	$day = dec_int($day);
	$year = dec_int($year);
	$month++;
	return julday($year,$month,$day);
}

# takes a scalar; parses it for dayname, including ranges;
# returns an array of julian days that match

sub parse_daynames($)
{
	my $temp = $_[0];
	my $first = "";
	my $last = "";
	my @weekdays = qw( Sun Mon Tue Wed Thu Fri Sat );
	my @months = qw( Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec Irv );
	my @monthdays = qw( 31 28 31 30 31 30 31 31 30 31 30 31 7);
	my @range;
	my $year;
	my $month = -1;
	my $day;
	my $t = localtime;
	my $i = 0;
	my $j = 0;
	my $weekday;
	my $flag = 0;
	my $monthname = "";

	while ($temp =~ /--/) {
		($first,$last)=($temp=~/([A-Z][a-z]+day)--([A-Z][a-z]+day)/);
		$temp =~ s/$first--$last//;
		foreach my $var (@months) {
			last if grep(/$var/,$temp);
			$j++;
		} foreach my $var (@weekdays) {
			last if grep(/$var/,$first);
			$i++;
		}
		$monthname = $months[$j];
		while (!grep(/$weekdays[$i]/,$last)) {	
			$temp .= $weekdays[$i++]."day"." ".$monthname.",";
		}
		$temp .= $weekdays[$i++]."day"." ".$monthname.",";
	}
	$i = 0;
	while (($temp =~ /,/) || ($temp !~ /[,]/ && $temp =~ /day/)) {
		($first) = ($temp =~ /[^\s\w\d]*([\/-\s\w\d]+)/);
		$temp =~ s/$first[,]*//;
		foreach my $var (@weekdays) {
			if (grep(/$var/,$first)) {
				$weekday = $var;
			}
		}
		foreach my $var (@months) {
			if (grep(/$var/,$first)) {
				$flag = 1;
				$i = 0;
				$i++ while $months[$i] ne $var;
				$month = $i + 1;
				if ($first =~ /([\dXE]{4,4})/) {
					$year = $1;
					$year = dec_int($year);
				} else {
					$year = $t->year;
				}
				$day = 1;
				$weekday = lc($weekday);
				$monthdays[1]++ if (leap_year($year)) && $monthdays[1] < 29;
				$day++ while (lc(day($month,$day,$year)) ne $weekday);
				while ($day <= @monthdays[$month-1]) {
					push(@range,julday($year,$month,$day));
					$day += 7;
				}
			}
		}
		if ($flag == 0) {
			$month = 1;
			if ($first =~ /([\dXE]{4,4})/) {
				$year = $1;
			} else { 
				$year = $t->year;
			}
			$monthdays[1]++ if (leap_year($year)) && $monthdays[1] < 29;
			$day = 1;
			$weekday = lc($weekday);
			$day++ while (lc(day(1,$day,$year)) ne $weekday);
			while ($day <= $monthdays[$month-1] && $month <= 12) {
				push(@range,julday($year,$month,$day));
				$day += 7;
				if ($day > $monthdays[$month-1]) {
					$month++;
					$day = 1;
					if ($month <= 12) {
						$day++ while (lc(day($month,$day,$year)) ne $weekday);
					}
				}
			}
		}
	}
	return @range;
}

# takes a scalar (a date field from @calendar); parses it; 
# returns a list of dates which meet the requirements

sub get_dates($)
{
	my $first = "";	# first date of a range
	my $last = "";		# last date of a range
	my @range = ();	# the array of dates which match the field
	my $temp;			# placeholder so we don't clobber $_[0]

	$temp = $_[0];
	$temp =~ s/\s//g;
	while ($temp =~ /--/ && $temp !~ /day/) {
		($first,$last)=($temp=~/[^\s\w\d]*([\/-\s\w\d]+)--([\/-\s\w\d]+)/);
		$temp =~ s/$first--$last//;
		$first = parse_dates($first) if parse_dates($first) != -1;
		$last = parse_dates($last) if parse_dates($last) != -1;
		push(@range,fill_range($first,$last));
	}
	while ($temp =~ /,/ && $temp !~ /day/) {
		($first) = ($temp =~ /[^\s\w\d]*([^;][\/-\s\w\d]+),/);
		$temp =~ s/$first,//;
		$first = parse_dates($first) if parse_dates($first) != -1;
		push(@range,ind_date($first));
	}
	if ($temp =~ /day/) {
		@range = parse_daynames($temp);
	} else {
		push(@range,ind_date(parse_dates($temp))) 
			if parse_dates($temp) != -1;
	}
	return @range;
}

# takes a scalar argument, the first field of the calendar
# line, and scans it for a time or times; returns an array
# of times

sub get_times($)
{
	my @times;
	my $temp;
	my $i;

	$temp = $_[0];
	$temp =~ s/\s//g;
	while ($temp =~ /([\dXE]{1,2};[\dXE]{1,4}[-]{0,2})/) {
		push(@times,$1);
		$temp =~ s/$1//;
	}
	return @times;
}

# after @calendar is populated, creates the date ranges with
# the events associated with them; takes no args, returns
# nothing

sub parse_input_file()
{
	my @range;
	my @exceptions;
	my @times;
	my $times;
	my @row;
	my @final_range;
	my $j = 0;

	for (my $i=0; $i <= $#calendar; ++$i) {
		@range = get_dates($calendar[$i][1]);
		@times = get_times($calendar[$i][2]);
		$times = join(",",@times);
		$times =~ s/--,/--/g;
		@exceptions = get_dates($calendar[$i][3]);
		foreach my $var (@range) {
			@row = ($var,$times,$calendar[$i][0],$calendar[$i][4]);
			push @{$eventlist[$j++]},@row if !grep(/$var/,@exceptions);
		}
	}
#	for (my $i = 0; $i <= $#eventlist; $i++) {
#		for ($j = 0; $j < 4; $j++) {
#			print $eventlist[$i][$j]."\n";
#		}
#	}
#	my @parseddate;
#	for (my $i = 0; $i <= $#eventlist; $i++) {
#		@parseddate = jultogreg($eventlist[$i][0]);
#		print day($parseddate[1],$parseddate[2],$parseddate[0]);
#		print " $parseddate[0] $parseddate[1] $parseddate[2]\n";
#	}
}

# takes day, month, and year; returns a string with the
# dozenalized date

sub thedate($$$)
{
	my $date;
	my $year;
	my $month;
	my $day;

	$year = doz_int($_[2]);
	$month = doz_int($_[1]);
	$day = doz_int($_[0]);
	$date = qx(dozdate -d"$year-$month-$day" "$dateformat");
	$date =~ s/^\s(.*)\s$/$1/;
	return $date;
}

# request a calendar; takes the year, the month, and the
# day, and returns the requested array; if month is zero,
# gives the entire year; if day is zero, gives the entire
# month

sub prod_cal($$$)
{
	my $i;
	my $j;
	my $k;
	my @parsed;

	for ($i = 0; $i <= $#eventlist; ++$i) {
		@parsed = jultogreg($eventlist[$i][0]);
		if ($parsed[0] == $_[0]) {
			for ($j = 0; $j <= 4; ++$j) {
				$callist[$k][$j]=thedate($parsed[2],$parsed[1],
					$parsed[0]) if ($j == 4);
				$callist[$k][$j]=$eventlist[$i][$j] 
					if ($j != 4);
			}
			$k++;
			if ($_[1] != 0) {
				if ($parsed[1] != $_[1]) {
					splice(@callist,(--$k),1);
				} elsif (($parsed[2] != $_[2]) && ($_[2] != 0)) {
					splice(@callist,(--$k),1);
				}
			}
		}
	}
	return @callist;
}

# parse the request dates; return an array of year, month, day

sub get_input_date($)
{
	my $year;
	my $month = 0;
	my $day = 0;
	my @months = qw( Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec Irv );
	my $i = 0;
	my $whole = "";
	my $flag = 0;

	if ($_[0] =~ /([\dXE]{4,4})/) {
		$year = $1;
	}
	foreach my $var (@months) {
		$i++;
		if ($_[0] =~ $var) {
			$month = doz_int($i);
			$flag = 1;
			last;
		}
	}
	if ($flag == 1) {
		$day = $1 if ($_[0] =~ /[^\dXE]([\dXE]{1,2})(^\dXE|$)/);
		$day = $1 if ($_[0] =~ /\w{3,9}.*?([\dXE]{1,2}),/);
	}
	$whole .= $year;
	if ($month eq "0") {
		if ($_[0] =~ /($year.*?([\dXE]{1,2}))/) {
			$month = $2;
			$whole = $1;
		} elsif ($_[0] =~ /(([\dXE]{1,2})[^\dXE]*?$year)/) {
			$month = $2;
			$whole = $1;
		}
	}
	if ($day eq "0") {
		if ($_[0] =~ /($whole.*?([\dXE]{1,2}))(^\dXE|$)/) {
			$day = $2;
			$whole = $1;
		} elsif ($_[0] =~ /(([\dXE]{1,2}).*?$whole)/) {
			$day = $2;
			$whole = $1;
		}
	}
	return ($year,$month,$day);
}

# parses the requested input date; returns an array of the
# list of the matching appointments/events

sub parse_it()
{
	my $year;
	my $month = 0;
	my $day = 0;
	my $t = localtime;
	my @resarray;

	if ($opt_d) {
		($year,$month,$day) = get_input_date($opt_d);
		$year = dec_int($year);
	} else {
		($year,$month,$day) = get_input_date($t->year);
	}
	$month = dec_int($month);
	$day = dec_int($day);
	@resarray = prod_cal($year,$month,$day);
#	for (my $i = 0; $i <= $#resarray; $i++) {
#		for (my $j = 0; $j < 5; $j++) {
#			print "$resarray[$i][$j] ";
#		}
#	}
	return @resarray;
}

# form_string, which formats the parts of the output (date,
# time, and name) and sends them back to the format
# function; takes the format string, the index in the
# layouts array that we're dealing with, and then the date,
# time, and name, and returns the formatted string

sub form_string($$$$$)
{
	my $date = $_[2];
	my $time = $_[3];
	my $name = $_[4];
	my $i = $_[1];
	my $string = $_[0];
	my $holder;
	my $spacer = " ";
	my $numfill = 0;
	my $curr;
	my $whole;
	my $leftjust = 0;

	my $var = $string;
	while ($var =~ /(%.*?([dnt]))/) {
		$curr = $2;
		$whole = $1;
		if ($var =~ /%(.*?)$curr/) {
			$holder = $1;
			if ($holder =~ /-/) {
				$leftjust = 1;
				$holder =~ s/-//;
			}
			if ($holder =~ /([\dXE]+)/) {
				$numfill = dec_int($1);
				if ($holder =~ /([^\d])/) {
					$spacer = $1;
				}
			}
			if ($curr eq 'd') {
				$numfill -= length($date);
				$spacer x= $numfill;
				$date =~ s/($date)/$spacer$1/ if $leftjust == 0;
				$date =~ s/($date)/$1$spacer/ if $leftjust == 1;
			}
			if ($curr eq 't') {
				$numfill -= length($time);
				$spacer x= $numfill;
				$time =~ s/($time)/$spacer$1/ if $leftjust == 0;
				$time =~ s/($time)/$1$spacer/ if $leftjust == 1;
			}
			if ($curr eq 'n') {
				$numfill -= length($name);
				$spacer x= $numfill;
				$name =~ s/($name)/$spacer$1/ if $leftjust == 0;
				$name =~ s/($name)/$1$spacer/ if $leftjust == 1;
			}
		}
		$var =~ s/$whole//;
		$string =~ s/%.*?$curr/$date/ if $curr eq 'd';
		$string =~ s/%.*?$curr/$time/ if $curr eq 't';
		$string =~ s/%.*?$curr/$name/ if $curr eq 'n';
	}
	return $string;
}

# formats the requeste dates for plain text output; takes an
# array of the dates, returns nothing

sub text_format(\@)
{
	my $lastdate = "";		# variable to prevent duplicate 
									# printing of dates
	my $outline = "";
	my $date = "";
	my $time = "";
	my $name = "";

	for (my $i = 0; $i <= $#{$_[0]}; $i++) {
		for (my $j = 0; $j <= $#layouts; $j++) {
			if (grep(/text, $_[0][$i][3]/,$layouts[$j])) {
				($outline) = ($layouts[$j] =~ /\w+,\s*\w+,\s*(.*)$/);
				$outline = form_string($outline,$i,$_[0][$i][4],$_[0][$i][1],
					$_[0][$i][2]);
#				$outline =~ s/%.*?d/$_[0][$i][4]/;
#				$outline =~ s/%.*?t/$_[0][$i][1]/;
#				$outline =~ s/%.*?n/$_[0][$i][2]/;
				print unbackslash($outline);
			}
		}
	}
}

# checks for a requested output format (default is text);
# then calls the appropriate function to crank it out; takes
# the array of relevant dates, returns nothing

sub output(\@)
{
	my $format = "text";

	$format = $opt_o if ($opt_o);
	if ($format eq "text") {
		text_format(@{$_[0]});
	} else {
		print STDERR "dozcal error:  the output format ";
		print STDERR "\"$format\" is not recognized\n";
		exit $BAD_OUTPUT_FORMAT;
	}
}

# a function for testing the rest

sub test_func()
{
	my @testarray;
	my $i;
	my $j;

	@testarray = prod_cal(2011,2,0);
	for (my $i = 0; $i <= $#testarray; $i++) {
		for ($j = 0; $j < 5; $j++) {
			print "$testarray[$i][$j] ";
		}
	}
}

# we all know what this one's for

sub main()
{
	my @datearray;

	use_input_file();
	parse_input_file();
	@datearray = parse_it();
	@datearray = sort { $a->[0] <=> $b->[0] } @datearray;
	output(@datearray);
#	test_func();
}

main();
