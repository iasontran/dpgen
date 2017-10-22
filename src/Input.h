/*************/
/*
 * File: Input.h
 * Author: Jason Tran
 * NetID: ichikasuto
 * Date: October 20, 2017
 *
 * Description:
 */

#ifndef Input_h
#define Input_h

#include <cstdio>
#include <string>
#include <vector>
#include <fstream>

class Input {
private:
    bool sign;
    std::vector<std::string> vars;
    std::vector<int> bits;
public:
    std::string removeSection(std::string in, const std::string& substr);
    void scanString(std::string line);
    void setSign(bool choice);
    std::vector<std::string> getVars() const;
    std::vector<int> getBits() const;
    bool getSign();
    Input();
    ~Input();
};

#endif
