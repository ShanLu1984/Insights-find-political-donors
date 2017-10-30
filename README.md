# Insights-find-political-donors

## Introduction 

This is a repository for Insight Data Engineering Coding Challenge. For more details, you may refer to the repository by Insight Data Science: https://github.com/InsightDataScience/find-political-donors.

## What's inside:
### src folder: contains all the source files of C++
1. *find_political_donors_main.cpp* : the main function of the find_political_donors program
2. *find_political_donors.cpp* : This file defines the classes and functions
3. *find_political_donors.h* : his file declares the classes and functions
4. *find_political_donors_test* : This file is used to test ParseLine function of FindPoliticalDonors class

### input folder: contains *itcont.txt* file, the file provided by Insight for test.

### output folder: contains all the output files.
1. *medianvals_by_date.txt* : contains a calculated running median, total dollar amount and total number of contributions by recipient and zip code
2. *medianvals_by_zip.txt* : has the calculated median, total dollar amount and total number of contributions by recipient and date.

### insight_testsuie: provided by Insight Data Science
1. *run_tests.sh* : to if the code has the correct directory structure and the format of the output files are correct
2. *results.txt* : records of test results
3. *tests folder* : used to store all the tests. Each test has a separate folder with an input folder for itcont.txt and an output folder for output corresponding to that test.

### two shell scripts:
1. run.sh: use this shell script to compile and execute *find_political_donors_main.cpp*
2. run_test.sh: use this shell script to compile and execute *find_political_donors_test.cpp*

## How to run:
1. Clone and download the whole repository;
1. Put all the files under a folder, such as name "find-political-donors";
1. For Unix/Linux users, open the terminal, make the current path *your_path/find-political-donors* by using cd command;
1. Change the input file or output file name in *run.sh*. 
1. Run *run.sh* using command `sh run.sh`;
1. Run *run_test.sh* by using command `sh run_test.sh`;
1. To test all the tests in insight_tests folder, make the current path "your_path/find-political-donors/insight_testsuite" by using command `cd insight_testsuite`;
1. Run *run_tests.sh* by using command `sh run_tests.sh`.
