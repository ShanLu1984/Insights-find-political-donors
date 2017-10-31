#!/bin/bash
#
# Use this shell script to compile (if necessary) your code and then execute it. Below is an example of what might be found in this file if your program was written in Python
#
g++ -std=c++11 ./src/find_political_donors_main.cpp ./src/find_political_donors.cpp -o find_political_donors
./find_political_donors ./input/itcont.txt ./output/medianvals_by_zip.txt ./output/medianvals_by_date.txt
