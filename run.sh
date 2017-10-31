#!/bin/bash
#
# Use this shell script to compile and excute find_political_donors_main.cpp.
#
g++ -std=c++11 ./src/find_political_donors_main.cpp ./src/find_political_donors.cpp -o find_political_donors
./find_political_donors ./input/itcont.txt ./output/medianvals_by_zip.txt ./output/medianvals_by_date.txt
