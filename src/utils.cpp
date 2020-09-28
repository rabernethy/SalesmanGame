#include <cstdio>
#include <string>
#include <vector>
#include "constants.h"
std::vector<std::string> split(const std::string& istr, char delim=' ') { 
    std::vector<std::string> tokens; 
    std::string temp = "";
  
    // Go through string grabbing substrings in between delimiters
    for (u_int i = 0; i < istr.length(); i++) {
        if (istr.at(i) == delim || istr.at(i) == '\n') {
            tokens.push_back(temp);
            temp = "";
        } else {
            temp += istr.at(i);
        }
    }
    return tokens;
 }
