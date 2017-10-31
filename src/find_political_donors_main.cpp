//
//  find_political_donors_main.cpp
//
//
//  Created by Shan Lu on 10/28/17. This is the main function of the find_political_donors program.
//
//

#include "find_political_donors.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc == 4) {
        std::string input_file(argv[1]);
        std::string medianvals_by_zip(argv[2]);
        std::string medianvals_by_date(argv[3]);
        FindPoliticalDonors find_political_donors;
        find_political_donors.GenerateAnalysis(input_file,
                                           medianvals_by_zip,
                                           medianvals_by_date);
    }
    else cout << "The inputs are invalid.\n";
    return 0;
}
