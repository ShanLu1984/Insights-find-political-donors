//
//  find_political_donors_test.cpp
//  
//
//  Created by Shan Lu on 10/28/17. This file is used to test ParseLine function of FindPoliticalDonors class.
//
//  Compile the unit test:
//  g++ -std=c++11 ./src/find_political_donors_main.cpp ./src/find_political_donors.cpp -o find_political_donors_test
//  Run the unit test: ./find_political_donors_test

#include "find_political_donors.h"

#include <iostream>

using namespace std;

// function to compare two TransactionLineInfo objects;
bool CompareInfo (TransactionLineInfo &lineoutput, TransactionLineInfo &lineoutput_truth) {
    if (lineoutput.CMTE_ID != lineoutput_truth.CMTE_ID) {
        return false;
    } else if (lineoutput.ZIP_CODE != lineoutput_truth.ZIP_CODE){
        return false;
    } else if (lineoutput.TRANSACTION_DT != lineoutput_truth.TRANSACTION_DT) {
        return false;
    } else if (lineoutput.TRANSACTION_AMT != lineoutput_truth.TRANSACTION_AMT) {
        return false;
    } else if (lineoutput.OTHER_ID != lineoutput_truth.OTHER_ID) {
        return false;
    } else {
        return true;
    }
}

int main()
{
    FindPoliticalDonors find_political_donors_test;
    
    // test 0: valid input;
    string line0 = "C00629618||||||||||90017|||01032017|40||||||";
    TransactionLineInfo line0output;
    TransactionLineInfo line0output_truth = {"C00629618", "90017", "01032017", "40", "empty"};
    
    find_political_donors_test.ParseLine(line0, line0output);
    
    if (CompareInfo(line0output, line0output_truth)) {
         cout << "test 0 pass!\n";
    } else {
         cout << "test 0 fail!\n";
    }
   
    // test 1: field 1 (CMTE_ID) is empty, skip the following steps;
    string line1 = "||||||||||90017|||01032017|40||||||";
    TransactionLineInfo line1output;
    TransactionLineInfo line1output_truth = {"invalid", "", "", "", ""};
    
    find_political_donors_test.ParseLine(line1, line1output);
    
    if (CompareInfo(line1output, line1output_truth)) {
         cout << "test 1 pass!\n";
    } else {
         cout << "test 1 fail!\n";
    }
    
    // test 2: field 11 (ZIP_CODE) is empty;
    string line2 = "C00629618|||||||||||||01032017|40||||||";
    TransactionLineInfo line2output;
    TransactionLineInfo line2output_truth = {"C00629618", "invalid", "01032017", "40", "empty"};
    
    find_political_donors_test.ParseLine(line2, line2output);
    
    if (CompareInfo(line2output, line2output_truth)) {
         cout << "test 2 pass!\n";
    } else {
         cout << "test 2 fail!\n";
    }
    
    // test 3: field 11 (ZIP_CODE) has fewer than 5 digits;
    string line3 = "C00629618||||||||||1912c|||01032017|40||||||";
    TransactionLineInfo line3output;
    TransactionLineInfo line3output_truth = {"C00629618", "invalid", "01032017", "40", "empty"};
    
    find_political_donors_test.ParseLine(line3, line3output);
    
    if (CompareInfo(line3output, line3output_truth)) {
         cout << "test 3 pass!\n";
    } else {
         cout << "test 3 fail!\n";
    }
    
    // test 4: field 14 (TRANSACTION_DT) is malformed, less than 8;
    string line4 = "C00629618||||||||||90017|||2017|40||||||";
    TransactionLineInfo line4output;
    TransactionLineInfo line4output_truth = {"C00629618", "90017", "invalid", "40", "empty"};
    
    find_political_donors_test.ParseLine(line4, line4output);
    
    if (CompareInfo(line4output, line4output_truth)) {
         cout << "test 4 pass!\n";
    } else {
         cout << "test 4 fail!\n";
    }

    // test 5: fild 14 (TRANSACTION_DT) is malformed, include non-digit characters;
    string line5 = "C00629618||||||||||90017|||june2017|40||||||";
    TransactionLineInfo line5output;
    TransactionLineInfo line5output_truth = {"C00629618", "90017", "invalid", "40", "empty"};
    
    find_political_donors_test.ParseLine(line5, line5output);
    
    if (CompareInfo(line5output, line5output_truth)) {
         cout << "test 5 pass!\n";
    } else {
         cout << "test 5 fail!\n";
    }
    
    // test 6: field 14 (TRANSACTION_DT) is malformed, not in month-day-year format;
    string line6 = "C00629618||||||||||90017|||20170103|40||||||";
    TransactionLineInfo line6output;
    TransactionLineInfo line6output_truth = {"C00629618", "90017", "invalid", "40", "empty"};
    
    find_political_donors_test.ParseLine(line6, line6output);
    
    if (CompareInfo(line6output, line6output_truth)) {
         cout << "test 6 pass!\n";
    } else {
         cout << "test 6 fail!\n";
    }

    // test 7: field 15 (TRANSACTION_AMT) is a float number;
    string line7 = "C00629618||||||||||90017|||01032017|1000.92||||||";
    TransactionLineInfo line7output;
    TransactionLineInfo line7output_truth = {"C00629618", "90017", "01032017", "1000.92", "empty"};
    
    find_political_donors_test.ParseLine(line7, line7output);
    
    if (CompareInfo(line7output, line7output_truth)) {
         cout << "test 7 pass!\n";
    } else {
         cout << "test 7 fail!\n";
    }

    // test 8: field 15 (TRANSACTION_AMT) is a negative number;
    string line8 = "C00629618||||||||||90017|||01032017|-2700||||||";
    TransactionLineInfo line8output;
    TransactionLineInfo line8output_truth = {"C00629618", "90017", "01032017", "-2700", "empty"};
    
    find_political_donors_test.ParseLine(line8, line8output);
    
    if (CompareInfo(line8output, line8output_truth)) {
         cout << "test 8 pass!\n";
    } else {
         cout << "test 8 fail!\n";
    }
    
    // test 9: field 15 (TRANSACTION_AMT) is empty, skip the following steps;
    string line9 = "C00629618||||||||||90017|||01032017|||||||";
    TransactionLineInfo line9output;
    TransactionLineInfo line9output_truth = {"C00629618", "90017", "01032017", "invalid", ""};
    
    find_political_donors_test.ParseLine(line9, line9output);
    
    if (CompareInfo(line9output, line9output_truth)) {
         cout << "test 9 pass!\n";
    } else {
         cout << "test 9 fail!\n";
    }
    

     // test 10: field 16 (OTHER_ID) is non-empty;
    string line10 = "C00629618||||||||||90017|||01032017|40|H6CA34245|||||";
    TransactionLineInfo line10output;
    TransactionLineInfo line10output_truth = {"C00629618", "90017", "01032017", "40", "invalid"};
    
    find_political_donors_test.ParseLine(line10, line10output);
    
    if (CompareInfo(line10output, line10output_truth)) {
         cout << "test 10 pass!\n";
    } else {
         cout << "test 10 fail!\n";
    }

    // test 11: less than 16 fields;
    string line11 = "C00629618||||||||||90017|||01032017|";
    TransactionLineInfo line11output;
    TransactionLineInfo line11output_truth = {"C00629618", "90017", "01032017", "", ""};
    
    find_political_donors_test.ParseLine(line11, line11output);
 
    if (CompareInfo(line11output, line11output_truth)) {
         cout << "test 11 pass!\n";
    } else {
         cout << "test 11 fail!\n";
    }

    // test 12: random input;
    string line12 = "Cfj=FPakoakof!!Aka,mvn9%#-";
    TransactionLineInfo line12output;
    TransactionLineInfo line12output_truth = {"", "", "", "", ""};
    
    if (CompareInfo(line12output, line12output_truth)) {
         cout << "test 12 pass!\n";
    } else {
         cout << "test 12 fail!\n";
    }
    
    return 0;
}
