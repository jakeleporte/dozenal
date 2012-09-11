#!/usr/bin/perl
# +AMDG  This document was begun on 8 Sept 11E8, the feast
# of the Nativity of the Blessed Virgin Mary and the Comm.
# of St. Hadrian, Martyr, and it is humbly dedicated to them
# for their prayers, and to the Sacred Heart of Jesus for
# His mercy.

use strict;
use POSIX;
use Time::Piece;
use Date::Day;
use Date::Easter;
use Date::Pcalc qw(Add_Delta_Days
	Date_to_Days);
use Getopt::Std;
getopts('f:');
our($opt_f);

# define our exit codes

my $SUCCESS = 0;
my $BAD_INPUT_FILE = 1;
my $INPUT_FILE_NOT_EXIST = 2;

# define our mod functions; both take two arguments, x and
# y, and return an integer

sub mod
{
	return $_[0] - $_[1] * ($_[0] / $_[1]);
}
sub amod
{
	return $_[1] + mod($_[0],-$_[1]);
}

# get the julian date; takes year, month, day

sub julday
{
	return 1721423.5 + Date_to_Days($_[0],$_[1],$_[2]) + 1;
}

# convert julian date back to gregorian date; takes the
# julian day, returns an array of year, month, day

sub jultogreg
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

# define @datelist; this array holds the broken-down dates
# and the events that go with them

my @datelist;

sub popsched
{
	my $i = 0;
	my $j = 0;
	my $k = 0;
	my @row = ();			# placeholder to feed into @calndar
	open($calfile,"<","$_[0]") || die $!;
	while (<$calfile>) {
		$k++;
		if ($_ !~ /(.*)\t(.*)\t(.*)\t(.*)/) {
			print STDERR "dozcal error:  malformation in data ";
			print STDERR "file $_[0] at line $k\n";
			exit $BAD_INPUT_FILE;
		}
		@row = ($_ =~ /(.*)\t(.*)\t(.*)\t(.*)/);
		push @{$calendar[$i]},@row;
		$i++;
	}
	close $calfile;
}

sub use_input_file
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

sub fill_range
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
	$firstday = qx(dec $firstday);
	$lastday = qx(dec $lastday);
	$firstyear = qx(dec $firstyear);
	$lastyear = qx(dec $lastyear);
	$firstmon++;
	$lastmon++;
	$firstday = julday($firstyear,$firstmon,$firstday);
	$lastday = julday($lastyear,$lastmon,$lastday);
	my $i = 0;
	$range[$i++] = $firstday++ while $firstday <= $lastday;
	return @range;
}

# gets the date from the array; parses it; returns a list of
# dates which meet the requirements

sub get_dates
{
	my $entry;			# date field we're working with
	my $first = "";	# first date of a range
	my $last = "";		# last date of a range
	my @range;

	for (my $i=0; $i <= $#calendar; ++$i) {
		$entry = $calendar[$i][1];
		($first,$last) = ($entry =~ /[^\s\w\d]*([\s\w\d]+)-([\s\w\d]+)/);
		if ($first ne "") {
			@range = fill_range($first,$last);
			print @range;
			#process exceptions to range here
			#then feed @range into @eventlist, with other data
			#from @calendar
		}
	}
}

use_input_file();
get_dates();

#for (my $i = 0; $i <= $#calendar; ++$i) {
#	for (my $j = 0; $j < 4; ++$j) {
#		print $calendar[$i]->[$j]."|";
#	}
#	print "\n";
#}
#
#print $calendar[0][1];
