/*************/
/*
 * File: Scanner.cpp
 * Author: Jason Tran, Andrew Camps
 * NetID: ichikasuto, andrewcamps
 * Date: October 21, 207
 *
 * Description:
 */

#include "Scanner.h"

Scanner::Scanner(Line_Type type) {
    this->type = type;
}

Scanner::~Scanner() {

}

int Scanner::scanLine(std::string line){
    std::string uintStr = "UInt";
    std::string intStr = "Int";
    std::string tempLine = line;
    std::string tempBits;
    int unsignPos = tempLine.find(uintStr);
    int signPos = tempLine.find(intStr);
    
    if (this->type == INPUT) {
        removeSection(tempLine, "input ");
    }
    else if (this->type == OUTPUT) {
        removeSection(tempLine, "output ");
    }
    else if (this->type == WIRE) {
        removeSection(tempLine, "wire ");
    }
    else if (this->type == REGISTER) {
        removeSection(tempLine, "register ");
    }
    else if (this->type == OPERATION) {
        
    }
    
    if (unsignPos != std::string::npos) {
        tempBits = tempLine.substr(0, 2);
        //int pos = unsignPos + 4;
        //tempBits = tempLine.substr(pos, 2);
        bits.push_back(std::stoi (tempBits));
        setSign(false);
    }
    else if (signPos != std::string::npos) {
        tempBits = tempLine.substr(0,2);
        //int pos = unsignPos + 3;
        //tempBits = tempLine.substr(pos, 2);
        bits.push_back(std::stoi (tempBits));
        setSign(true);
    }
    if (getSign()) {
        intStr.insert(0, tempBits);
        removeSection(tempLine, intStr);
    }
    else {
        uintStr.insert(0, tempBits);
        removeSection(tempLine, uintStr);
    }
    
    return 0; // No error
}

void Scanner::setSign(bool choice) {
    this->sign = choice;
}

bool Scanner::getSign() {
    return this->sign;
}

std::string Scanner::removeSection(std::string in, const std::string& substr) {
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

std::vector<std::string> Scanner::getVars() const {
    return this->vars;
}

std::vector<int> Scanner::getBits() const {
    return this->bits;
}
