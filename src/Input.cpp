/*************/
/*
 * File: Input.cpp
 * Author: Jason Tran
 * NetID: ichikasuto
 * Date: October 21, 207
 *
 * Description:
 */

#include "Input.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cctype>

Input::Input() {
    
}

Input::~Input() {
    
}

std::string Input::removeSection(std::string in, const std::string& substr) {
    std::string out = in;
    std::string::size_type index = out.find(substr);
    if (index != std::string::npos) {
        in.erase(out.begin() + index, out.begin() + index + substr.length());
    }
    return out;
}

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

void Input::setSign(bool choice) {
    this->sign = choice;
}

bool Input::getSign() {
    return this->sign;
}

std::vector<std::string> Input::getVars() const {
    return this->vars;
}

std::vector<int> Input::getBits() const {
    return this->bits;
}

void Input::scanString(std::string line) {
    std::string tempLine = line;
    std::string tempBits;
    int unsignPos = tempLine.find("UInt");
    int signPos = tempLine.find("Int");
    if (unsignPos != std::string::npos) {
        int pos = unsignPos + 4;
        tempBits = tempLine.substr(pos, 2);
        bits.push_back(std::stoi (tempBits));
        setSign(false);
    }
    else if (signPos != std::string::npos) {
        int pos = unsignPos + 3;
        tempBits = tempLine.substr(pos, 2);
        bits.push_back(std::stoi (tempBits));
        setSign(true);
    }
    tempLine = getSign() ? removeSection(tempLine, "Int") : removeSection(tempLine, "UInt");
    
    
}
