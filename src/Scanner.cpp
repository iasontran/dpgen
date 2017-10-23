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

Scanner::Scanner(string file, Module *module){
    this->file = file;
    this->module = module;
}

/**
 * @brief
 *
 *
 *
 * @param
 * @return
 */
bool Scanner::readFile(){
    fstream in;
    
    in.open(this->file.c_str());
    
    if (!in.is_open()) {     // if file is available, open and read
        cout << "No input file found with the name: " << this->file << endl;
        return false;
    }
    
    while (!in.eof()) {     // execute until last line of file
        string line;
        getline(in, line);
        string::size_type index;
        
        /* Removes all comments from line */
        if ((index = line.find("//")) != string::npos) {
            line.erase(line.begin() + index, line.end());
        }
        
        /* Decide what type of statement the line is */
        if((index = line.find("=")) != string::npos){
            if(!parseLine(line, OPERATION)){
                cout << "Invalid line syntax: " << line << endl;
                return false;
            }
        }
        else if ((index = line.find("input ")) != string::npos) {
            line.erase(line.begin(), line.begin() + index);
            if(!parseLine(line, INPUT)){
                cout << "Invalid line syntax: " << line << endl;
                return false;
            }
            
        }
        else if ((index = line.find("output ")) != string::npos) {
            line.erase(line.begin(), line.begin() + index);
            if(!parseLine(line, OUTPUT)){
                cout << "Invalid line syntax: " << line << endl;
                return false;
            }
            
        }
        else if ((index = line.find("wire ")) != string::npos) {
            line.erase(line.begin(), line.begin() + index);
            if(!parseLine(line, WIRE)){
                cout << "Invalid line syntax: " << line << endl;
                return false;
            }
            
        }
        else if ((index = line.find("register ")) != string::npos) {
            line.erase(line.begin(), line.begin() + index);
            if(!parseLine(line, REGISTER)){
                cout << "Invalid line syntax: " << line << endl;
                return false;
            }
            
        } /* Empty line or invalid line syntax */
        else{
            /* Invalid input line syntax */
            if(!line.empty()){
                cout << "Invalid line syntax: " << line << endl;
                return false;
            }
        }
    }
    
    in.close();
    
    return true;
}

/**
 * @brief
 *
 *
 *
 * @param
 * @return
 */
bool Scanner::parseLine(string line, Type type) {
    string uintStr = "UInt";
    string intStr = "Int";
    
    switch(type){
        case INPUT:
            cout << "INPUT" << endl;
            
            break;
        case OUTPUT:
            cout << "OUTPUT" << endl;
            
            break;
        case WIRE:
            cout << "WIRE" << endl;
            
            break;
        case REGISTER:
            cout << "REGISTER" << endl;
            
            break;
        case OPERATION:
            cout << "OPERATION" << endl;
            
            break;
    }
    
    /*
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
     */
    
    return true; // No error
}

/*
string Scanner::removeSection(std::string in, const std::string& substr) {
    std::string out = in;
    std::string::size_type index = out.find(substr);
    if (index != std::string::npos) {
        in.erase(out.begin() + index, out.begin() + index + substr.length());
    }
    return out;
}

string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}
 */
