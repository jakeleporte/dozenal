#!/bin/bash

./symm_run.sh > symm_results.txt;
diff symm_ans.txt symm_results.txt > /dev/null;
if [ $? -eq 0 ]; then
	echo "Gregorian to Symm676 works!"
else
	echo "Gregorian to Symm676 doesn't work!"
	diff symm_ans.txt symm_results.txt;
fi
