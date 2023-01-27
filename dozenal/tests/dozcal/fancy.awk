#!/usr/bin/awk -f
# +AMDG
# Converts dozcal plain output (default) to "fancy" plain
# text output
# If the current date is the same as the last, it's not
# printed, and the rest of the record is printed indented
# instead.

BEGIN {
	FS = " \\| "
	lastdate = ""
}

// {
	currdate = $2
	if (currdate != lastdate) {
		printf "-------------------------------------------------"
		printf "------------\n"
		printf "%-13.13s%-30.30s%-18.18s\n","DATE","EVENT","LOCATION"
		printf "-------------------------------------------------"
		printf "------------\n"
		printf "%-13.13s",$3
		lastdate = $2
	} else {
		printf "%-13.13s"," "
	}
	printf "%-30.28s%-18.18s\n",$4,$9
	if ($3 != "") {
		printf "%13.13s\t%7.7s"," ",$3
	} if ($3 != "") {
		printf "--%7.7s",$3
	} if (($3 != "") || ($3 != "")) {
		printf("\n")
	}
	if ($5 != "") {
		printf("%13.13s\t%-16.16s\n"," ",$5)
	} if ($6 != "") {
		printf("%13.13s\t%-60.60s\n"," ",$6)
	}
}
