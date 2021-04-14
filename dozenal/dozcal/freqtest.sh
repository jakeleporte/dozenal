#!/bin/sh
# +AMDG

NUM=`./dozcal -f freqdata | grep "Yearly:  Testing" | wc -l`
if [ $NUM -eq 3 ]; then
	echo "[SUCCESS]:  Yearly, Enddate"
else
	echo "[FAILURE]:  Yearly, Enddate"
fi
NUM=`./dozcal -f freqdata | grep "Yearly, Noenddate" | wc -l`
if [ $NUM -eq 11 ]; then
	echo "[SUCCESS]:  Yearly, Noenddate"
else
	echo "[FAILURE]:  Yearly, Noenddate"
fi
NUM=`./dozcal -f freqdata | grep "Weekly:  Every Tuesday and Thursday" | wc -l`
if [ $NUM -eq 13 ]; then
	echo "[SUCCESS]:  Weekly, Enddate"
else
	echo "[FAILURE]:  Weekly, Enddate"
fi
NUM=`./dozcal -f freqdata | grep "Noenddate, Weekday, No Ordinal, No Monthname" | wc -l`
if [ $NUM -eq 525 ]; then
	echo "[SUCCESS]:  Weekly, Noenddate, No Ordinal, No Monthname"
else
	echo "[FAILURE]:  Weekly, Noenddate, No Ordinal, No Monthname"
fi
NUM=`./dozcal -f freqdata | grep "Enddate, Weekday, No Ordinal, No Monthname" | wc -l`
if [ $NUM -eq 53 ]; then
	echo "[SUCCESS]:  Weekly, Enddate, No Ordinal, No Monthname"
else
	echo "[FAILURE]:  Weekly, Enddate, No Ordinal, No Monthname"
fi
NUM=`./dozcal -f freqdata | grep "Noenddate, Weekday, Ordinal, No Monthname" | wc -l`
if [ $NUM -eq 121 ]; then
	echo "[SUCCESS]:  Weekly, Noenddate, Ordinal, No Monthname"
else
	echo "[FAILURE]:  Weekly, Noenddate, Ordinal, No Monthname"
fi
NUM=`./dozcal -f freqdata | grep "Enddate, Weekday, Ordinal, No Monthname" | wc -l`
if [ $NUM -eq 15 ]; then
	echo "[SUCCESS]:  Weekly, Enddate, Ordinal, No Monthname"
else
	echo "[FAILURE]:  Weekly, Enddate, Ordinal, No Monthname"
fi
NUM=`./dozcal -f freqdata | grep "Noenddate, Weekday, No Ordinal, Monthname" | wc -l`
if [ $NUM -eq 46 ]; then
	echo "[SUCCESS]:  Weekly, Noenddate, No Ordinal, Monthname"
else
	echo "[FAILURE]:  Weekly, Noenddate, No Ordinal, Monthname"
fi
NUM=`./dozcal -f freqdata | grep "Enddate, Weekday, No Ordinal, Monthname" | wc -l`
if [ $NUM -eq 8 ]; then
	echo "[SUCCESS]:  Weekly, Enddate, No Ordinal, Monthname"
else
	echo "[FAILURE]:  Weekly, Enddate, No Ordinal, Monthname"
fi
NUM=`./dozcal -f freqdata | grep "Noenddate, Weekday, Ordinal, Monthname" | wc -l`
if [ $NUM -eq 11 ]; then
	echo "[SUCCESS]:  Weekly, Noenddate, Ordinal, Monthname"
else
	echo "[FAILURE]:  Weekly, Noenddate, Ordinal, Monthname"
fi
NUM=`./dozcal -f freqdata | grep "Enddate, Weekday, Ordinal, Monthname" | wc -l`
if [ $NUM -eq 2 ]; then
	echo "[SUCCESS]:  Weekly, Enddate, Ordinal, Monthname"
else
	echo "[FAILURE]:  Weekly, Enddate, Ordinal, Monthname"
fi
NUM=`./dozcal -f freqdata | grep "Monthly Default" | wc -l`
if [ $NUM -eq 13 ]; then
	echo "[SUCCESS]:  Monthly, Enddate"
else
	echo "[FAILURE]:  Monthly, Enddate"
fi
NUM=`./dozcal -f freqdata | grep "Monthly, Noenddate" | wc -l`
if [ $NUM -eq 121 ]; then
	echo "[SUCCESS]:  Monthly, Noenddate"
else
	echo "[FAILURE]:  Monthly, Noenddate"
fi
