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
            Input *newInput;
            cout << "INPUT" << endl;
            
            break;
        case OUTPUT:
            Output *newOutput;
            cout << "OUTPUT" << endl;
            
            break;
        case WIRE:
            Wire *newWire;
            cout << "WIRE" << endl;
            
            break;
        case REGISTER:
            Register *newRegister;
            cout << "REGISTER" << endl;
            
            break;
        case OPERATION:
            Operation *newOp;
            cout << "OPERATION" << endl;
            
            break;
    }
    
    return true; // No error
}
