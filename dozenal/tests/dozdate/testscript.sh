#!/bin/bash

./dozdate -f testfile.txt > results;
sed -i -e 's/EST/EDT/g' results;
diff results answers.txt;
if [ $? == 0 ]; then
	printf "Works!\n";
else
	printf "Doesn't work!\n";
fi
