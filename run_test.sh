#!/bin/bash
#
# Use this shell script to compile and excute find_political_donors_test.cpp.
#
g++ -std=c++11 ./src/find_political_donors_test.cpp ./src/find_political_donors.cpp -o find_political_donors_test
./find_political_donors_test

