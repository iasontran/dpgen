/*************/
/*
 * File: Scanner.h
 * Author: Jason Tran, Andrew Camps
 * NetID: ichikasuto, andrewcamps
 * Date: October 20, 2017
 *
 * Description:
 */

#ifndef Scanner_h
#define Scanner_h

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <cctype>

class Scanner {
    
    public:
        enum Line_Type {
            INPUT,
            OUTPUT,
            WIRE,
            REGISTER,
            OPERATION
        };
        Scanner(Line_Type type);
        ~Scanner();
        int scanLine(std::string line);
        void setSign(bool choice);
        bool getSign();
        std::string removeSection(std::string in, const std::string& substr);
        std::vector<std::string> getVars() const;
        std::vector<int> getBits() const;
    private:
        bool sign;
        Line_Type type;
        std::vector<std::string> vars;
        std::vector<int> bits;
};

#endif
