//
//  find_political_donors.cpp
//
//
//  Created by Shan Lu on 10/28/17. This file defines the classes and functions.
//
//

#include "find_political_donors.h"

#include <vector>
#include <utility>
#include <queue>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <math.h>
#include <iostream>

using namespace std;

namespace {

// IdCrossDateComp: used to compare two strings in the form of "id|date".
struct IdCrossDateComp{
    bool operator()(const string& str1, const string& str2) const {
        int pos1 = str1.find("|");
        int pos2 = str2.find("|");
        
        string id1 = str1.substr(0, pos1);
        string id2 = str2.substr(0, pos2);
        if (id1 != id2) return id1 < id2;
        
        string year1 = str1.substr(pos1 + 5);
        string year2 = str2.substr(pos2 + 5);
        if (year1 != year2) return year1 < year2;
        
        string month1 = str1.substr(pos1 + 1, 2);
        string month2 = str2.substr(pos2 + 1, 2);
        if (month1 != month2) return month1 < month2;
        
        string day1 = str1.substr(pos1 + 3, 2);
        string day2 = str2.substr(pos2 + 3, 2);
        return day1 < day2;
    }
};

// mp_zip_small and mp_zip_large: used to store the smaller half and larger half of the contributions that an ID receives so far from an IP; adding data has a time complexity of  O(logn); and compute median has a time complexity of O(1).
// mp_zip_sum: used to store the total amount of contributions that an ID receives so far from an IP.
// mp_date: all the transactions an ID receives on a Date.
// mp_date_sum: the summation of the all the transactions an ID receives on a Date.
    
struct StreamHelperMaps {
    unordered_map<string, priority_queue<float> > mp_zip_large;
    unordered_map<string, priority_queue<float> > mp_zip_small;
    unordered_map<string, float> mp_zip_sum;
    map<string, vector<float>, IdCrossDateComp> mp_date;
    unordered_map<string, float> mp_date_sum;
};

// function to check if a zip is valid.
bool CheckZip(const string &zip) {
    if (zip.size() < 5) return false;
    for (int i=0; i<5; ++i) {
        if (!isdigit(zip[i])) return false;
    }
    return true;
}

// fucntion to check if a date is valid.
bool CheckDate(const string &date) {
    if (date.size() != 8) return false;
    for (auto c : date) {
        if (!isdigit(c)) return false;
    }
    string month = date.substr(0, 2);
    string day = date.substr(2,2);
    if (month >= "01" && month <= "12" && day >= "01" && day <= "31") return true;
    return false;
}

// function to add a new record to the id-zip's small and large heaps and update the total amount; time complexity for adding is O(log n), n is the heaps' current size.
void MapsAddTransaction(const string& id_zipcode, float amt, StreamHelperMaps& stream_helper_maps) {
    stream_helper_maps.mp_zip_small[id_zipcode].push(amt);
    stream_helper_maps.mp_zip_large[id_zipcode].push(-stream_helper_maps.mp_zip_small[id_zipcode].top());
    stream_helper_maps.mp_zip_small[id_zipcode].pop();
    if (stream_helper_maps.mp_zip_small[id_zipcode].size() < stream_helper_maps.mp_zip_large[id_zipcode].size()) {
        stream_helper_maps.mp_zip_small[id_zipcode].push(-stream_helper_maps.mp_zip_large[id_zipcode].top());
        stream_helper_maps.mp_zip_large[id_zipcode].pop();
    }
    stream_helper_maps.mp_zip_sum[id_zipcode] += amt;
}

// function to find median of a id-zip pair using the heaps; time complexity O(1).
int StreamFindMedian(const string& key,
                     StreamHelperMaps& stream_helper_maps) {
    return stream_helper_maps.mp_zip_small[key].size() > stream_helper_maps.mp_zip_large[key].size()
    ? round(stream_helper_maps.mp_zip_small[key].top())
    : round((stream_helper_maps.mp_zip_small[key].top()
             - stream_helper_maps.mp_zip_large[key].top()) / 2.0);
}

// function to add a new record to the id-date vector; and update the total amount; time complexity O(1).
void MapsTotalAddTransaction(const string& id_date, float amt, StreamHelperMaps& stream_helper_maps) {
    stream_helper_maps.mp_date[id_date].push_back(amt);
    stream_helper_maps.mp_date_sum[id_date] += amt;
}

// function to write the "medianvals_by_zip.txt" file.
void writeZipFile(const string& key, ofstream& medianvals_by_zip,
                  StreamHelperMaps& stream_helper_maps){
    int median = StreamFindMedian(key, stream_helper_maps);
    int sz = stream_helper_maps.mp_zip_small[key].size() + stream_helper_maps.mp_zip_large[key].size();
    float sum = stream_helper_maps.mp_zip_sum[key];
    medianvals_by_zip << key << "|" << median << "|"  << sz << "|" << sum << "\n";
}

// function to write the "medianvals_by_date.txt" file.
void writeDateFile(ofstream& medianvals_by_date,
                   StreamHelperMaps& stream_helper_maps){
    for (auto it = stream_helper_maps.mp_date.begin(); it != stream_helper_maps.mp_date.end(); ++it) {
        string key = it->first;
        sort(it->second.begin(), it->second.end());
        int sz = it->second.size();
        int median = round((it->second[(sz-1)/2] + it->second[sz/2])/2.0);
        float sum = stream_helper_maps.mp_date_sum[key];
        medianvals_by_date << key << "|"  << median << "|" << sz << "|" << sum << "\n";
    }
}

}  // namespace

FindPoliticalDonors::FindPoliticalDonors() {}

FindPoliticalDonors::~FindPoliticalDonors() {}

// function to parse line and get useful information.
bool FindPoliticalDonors::ParseLine(string& line, TransactionLineInfo& line_info){
    int field = 0;
    int start = 0;
    int found = line.find_first_of("|");
    while (found != int(string::npos)){
        field++;
        string str_temp = line.substr(start, found - start);
        if (field == 1) {
            if (str_temp.empty()) {
                line_info.CMTE_ID = "invalid";
                return false;
            }
            line_info.CMTE_ID = str_temp;
        }
        if (field == 11) {
            if (!CheckZip(str_temp)) line_info.ZIP_CODE = "invalid";
            else line_info.ZIP_CODE = str_temp.substr(0,5);
        }
        if (field == 14) {
            if (!CheckDate(str_temp)) line_info.TRANSACTION_DT = "invalid";
            else line_info.TRANSACTION_DT = str_temp;
        }
        if (field == 15) {
            if (str_temp.empty()) {
                line_info.TRANSACTION_AMT = "invalid";
                return false;
            }
            line_info.TRANSACTION_AMT = str_temp;
        }
        if (field == 16) {
            if (!str_temp.empty()) {
                line_info.OTHER_ID = "invalid";
                return false;
            }
            line_info.OTHER_ID = "empty";
        }
        start = found + 1;
        found = line.find("|", start);
    }
    if (field < 16) return false;
    return true;
}

// function to read line from input file, parse line, get informaiton, update the records, and write to output file.
void FindPoliticalDonors::GenerateAnalysis (string input_file,
                                            string medianvals_by_zip_file,
                                            string medianvals_by_date_file) {
    string line;
    TransactionLineInfo line_info;
    StreamHelperMaps stream_helper_maps;

    ifstream input(input_file);
    ofstream medianvals_by_zip(medianvals_by_zip_file);
    ofstream medianvals_by_date(medianvals_by_date_file);

    if (input.is_open()) {
        while (getline(input, line)) {
            if (ParseLine(line, line_info)) {
                if (line_info.ZIP_CODE != "invalid") {
                    string id_zipcode = line_info.CMTE_ID + '|' + line_info.ZIP_CODE;
                    float amt = stof(line_info.TRANSACTION_AMT);
                    MapsAddTransaction(id_zipcode, amt, stream_helper_maps);

                    if (medianvals_by_zip.is_open()) {
                        writeZipFile(id_zipcode, medianvals_by_zip,stream_helper_maps);
                    }
                    else cout << "Unable to open file <medianvals_by_zip.txt>\n";
                }
                if (line_info.TRANSACTION_DT != "invalid") {
                    string id_date = line_info.CMTE_ID + '|' + line_info.TRANSACTION_DT;
                    float amt = stof(line_info.TRANSACTION_AMT);
                    MapsTotalAddTransaction(id_date, amt, stream_helper_maps);
                }
            }
        }
        input.close();
        medianvals_by_zip.close();

        if (medianvals_by_date.is_open()){
            writeDateFile(medianvals_by_date, stream_helper_maps);
            medianvals_by_date.close();
        }
        else cout << "Unable to open file <medianvals_by_date.txt>\n";
    }
    else cout << "Unable to open file <itcont.txt>\n";
}

