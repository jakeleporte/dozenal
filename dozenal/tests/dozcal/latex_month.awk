#!/usr/bin/awk -f
# +AMDG
# This document was begun on 19 Aug 1200, the feast of St.
# Jane Frances de Chantal, and it is humbly dedicated to her
# and to the Immaculate Heart of Mary for their prayers, and
# to the Sacred Heart of Jesus for His mercy.

BEGIN {
	FS = " \\| "
	mday = 1;
	print("\\documentclass{article}");
	print("\\title{Calendar}");
	print("\\author{}\\date{}");
	print("\\usepackage{array}");
	print("\\usepackage[paperwidth=11in,paperheight=8.5in,");
	print("\tmargin=0.5in]{geometry}");
	print("\\usepackage[typeone]{dozenal}");
	print("\\begin{document}");
	print("\\def\\hanger{\\parindent=0pt\\hangindent=1em\\hangafter=1}");
	print("\\newlength{\\daywidth}");
	print("\\setlength{\\daywidth}{0.125\\textwidth}");
	print("\\newcolumntype{L}[1]{>{\\raggedright\\arraybackslash}p{#1}}");
	print("\\noindent\\begin{tabular}{L{\\daywidth}L{\\daywidth}L{\\daywidth}L{\\daywidth}L{\\daywidth}L{\\daywidth}L{\\daywidth}}");
	printf("\\multicolumn{1}{c}{\\scshape Sunday} &");
	printf("\\multicolumn{1}{c}{\\scshape Monday} &");
	printf("\\multicolumn{1}{c}{\\scshape Tuesday} &");
	printf("\\multicolumn{1}{c}{\\scshape Wednesday} &");
	printf("\\multicolumn{1}{c}{\\scshape Thursday} &");
	printf("\\multicolumn{1}{c}{\\scshape Friday} &");
	printf("\\multicolumn{1}{c}{\\scshape Saturday} \\\\\n");
}

function add_filler(wday) {
	if (wday == 1) {
		printf("{} ");
	} else if (wday == 2) {
		printf("{} & {} ");
	} else if (wday == 3) {
		printf("{} & {} & {} ");
	} else if (wday == 4) {
		printf("{} & {} & {} & {} ");
	} else if (wday == 5) {
		printf("{} & {} & {} & {} & {} ");
	} else if (wday == 6) {
		printf("{} & {} & {} & {} & {} & {} ");
	}
}

function get_days(s) {
	match(s,/[0-9XE][0-9XE][0-9XE][0-9XE]/,year);
	if ((year[0] % 4) == 0) {
		if ((year[0] % 100) != 0) {
			leapyear = 0;
		} else if ((year[0] % 400) == 0) {
			leapyear = 1;
		} else {
			leapyear = 1;
		}
	}
	if (s ~ /Jan/) { return 31; }
	if (s ~ /Feb/) {
		if (leapyear == 0) {
			return 29;
		} else {
			return 28;
		}
	}
	if (s ~ /Mar/) { return 31; }
	if (s ~ /Apr/) { return 30; }
	if (s ~ /May/) { return 31; }
	if (s ~ /Jun/) { return 30; }
	if (s ~ /Jul/) { return 31; }
	if (s ~ /Aug/) { return 31; }
	if (s ~ /Sep/) { return 30; }
	if (s ~ /Oct/) { return 31; }
	if (s ~ /Nov/) { return 30; }
	if (s ~ /Dec/) { return 31; }
}

NR == 1 {
	if ($1 ~ /Sun/) { wday = 1; currday = wday + 1; }
	if ($1 ~ /Mon/) { wday = 2; currday = wday + 1; }
	if ($1 ~ /Tue/) { wday = 3; currday = wday + 1; }
	if ($1 ~ /Wed/) { wday = 4; currday = wday + 1; }
	if ($1 ~ /Thu/) { wday = 5; currday = wday + 1; }
	if ($1 ~ /Fri/) { wday = 6; currday = wday + 1; }
	if ($1 ~ /Sat/) { wday = 7; currday = wday + 1; }
	match($1,/[0-9XE] ([A-Z][a-z][a-z])/,month);
	currmon = month[1];
	match(s,/[0-9XE][0-9XE][0-9XE][0-9XE]/,year);
	totaldays = get_days($1);
	last_day = 0;
	last_date = $1;
	mday = 1;
	caldata[mday] = caldata[mday] "\\hbox to\\daywidth{\\hfil\\basexii{"mday"}{\\x}{\\e}}";
	mday++;
}

$1 ~ currmon && $1 ~ year[0] {
	if ($1 != last_date) {
		if ($1 ~ /Sun/) {
			caldata[mday] = caldata[mday] "\\\\\n";
		} else {
			caldata[mday] = caldata[mday] " & ";
		}
		caldata[mday] = caldata[mday] "\\hbox to\\daywidth{\\hfil\\basexii{"mday"}{\\x}{\\e}}";
		++mday;
		last_date = $1;
	}
	caldata[mday] = caldata[mday] "\\hanger\\footnotesize\\textbf{" $4 "}\\par";
}

END {
	add_filler(wday);
	for (i in caldata) {
		print caldata[i];
	}
	leftover = (i % 7);
	for (i = 0; i < (leftover - 1); ++i) {
		printf(" & {}");
	}
	print("\\\\");
	print("\\end{tabular}");
	print("\\end{document}");
}
