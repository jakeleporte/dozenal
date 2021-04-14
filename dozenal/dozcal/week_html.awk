#!/usr/bin/awk -f
# +AMDG
# This document was begun on 1 Aug 1200, the Comm. of the
# Holy Machabees, MM, and it is humbly dedicated to them and
# to the Immaculate Heart of Mary, for their prayers, and to
# the Sacred Heart of Jesus, for His mercy.

BEGIN {
	FS = " \\| "
	lastdate = ""
	heading_line = "<tr>"
	ind = -1;
	print "<html>"
	print "<style>"
	print "tr {margin:  0pt;}"
	print "td { border-width:  2px; border-color: black;"
	print "border-style:  solid; width:  14.2%; margin: 0pt;"
	print "font-size:  75%;}"
	print "th { border-width:  2px; border-color: black;"
	print "border-style:  solid; font-variant: small-caps;"
	print "width:  14.2%; margin:  0pt;}"
	print "ul { padding:  0pt; padding-left:  1.5em; }"
	print "</style>"
	print "<body>"
	print "<table>"
}

// {
	currdate = $2
	if (currdate != lastdate) {
		heading_line = heading_line  "<th>" currdate "</th>"
		if (ind != 0) {
			events[ind] = events[ind] "</ul></td>"
		}
		ind = ind + 1
		events[ind] = "<td><ul><li>"$5
		if ($3 != "")
			events[ind] = events[ind] " ("$3
		if ($4 != "")
			events[ind] = events[ind] "--"$4
		if (($3 != "") || ($4 != ""))
			events[ind] = events[ind] ") "
		events[ind] = events[ind] "</li>"
		lastdate = $2
	} else {
		events[ind] = events[ind] "<li>"$5
		if ($3 != "")
			events[ind] = events[ind] " ("$3
		if ($3 != "")
			events[ind] = events[ind] "--"$4
		if (($3 != "") || ($4 != ""))
			events[ind] = events[ind] ") "
		events[ind] = events[ind] "</li>"
		#fill in stuff
	}
}

END {
	heading_line = heading_line "</tr>"
	print heading_line
	for (i = 0; i < 7; ++i) {
		print events[i]
	}
	print "</tr>"
	print "</table>"
	print "</body>"
	print "</html>"
}
