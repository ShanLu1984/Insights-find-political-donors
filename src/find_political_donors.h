//
//  find_political_donors.h
//
//
//  Created by Shan Lu on 10/28/17. This file declares the classes and functions.
//  TractionLineInfo struct and FindPoliticalDonors class.
//
//

#ifndef FIND_POLITICAL_DONORS_H_
#define FIND_POLITICAL_DONORS_H_

#include <string>
#include <fstream>

struct TransactionLineInfo {
    std::string CMTE_ID;
    std::string ZIP_CODE;
    std::string TRANSACTION_DT;
    std::string TRANSACTION_AMT;
    std::string OTHER_ID;
};

class FindPoliticalDonors {
public:
    FindPoliticalDonors();
    virtual ~FindPoliticalDonors();
    bool ParseLine(std::string& line, TransactionLineInfo& line_info);
    void GenerateAnalysis(std::string itcont_input_file,
                          std::string medianvals_by_zip,
                          std::string medianvals_by_date);
};


#endif // FIND_POLITICAL_DONORS_H_
