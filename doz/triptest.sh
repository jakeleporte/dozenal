#!/bin/bash
# +AMDG

echo "Reading from a file:";
./doz < testfile;
echo "Reading from file with 3 precision:";
./doz -k 3 < testfile;
echo "Reading from file, 3 precision, 2 bad arguments:";
./doz -x -k 3 -n < testfile;
echo "Reading from file, 3 precision, 1 prior bad argument:";
./doz -x -k 3 < testfile;
echo "Reading from file, 3 precision, 1 subsequent bad argument:";
./doz -k 3 -n < testfile;
echo "Reading from file, no precision specified:";
./doz -k < testfile;
echo "Reading from file, ridiculous precision specified:";
./doz -k 500 < testfile;
echo "Reading from command line:";
./doz 1492.5;
echo "Reading from command line, 3 precision:";
./doz -k 3 1492.5;
echo "Command line, 2 bad arguments:";
./doz -x -k 3 -n 1492.5;
echo "Command line, 1 bad subsequent argument:";
./doz -k 3 -n 1492.5;
echo "Command line, 1 bad prior argument:";
./doz -x -k 3 1492.5;
echo "Command line, -k with no precision value:";
./doz -k 1492.5;
echo "Command line, -k with ridiculous precision value:";
./doz -k 500 1492.5;
echo "Command line, 3, exponential output:";
./doz -e -k 3 1492.5;
echo "File, 5, exponential output:";
./doz -e -k 5 < testfile;
