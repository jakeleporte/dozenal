#!/bin/bash

./symm_run.sh > symm_results.txt;
diff symm_ans.txt symm_results.txt;
