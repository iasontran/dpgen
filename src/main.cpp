/**************************************************************************************************/

/*
 * File: main.cpp
 * Author: Jason Tran
 * NetID: ichikasuto
 * Date: October 20, 2017
 *
 * Description:
 *
 */
/**************************************************************************************************/
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include "Input.h"

bool readFile(std::string filename) {
    std::fstream in;
    std::string line;
    std::string temp;
    Input* newInput = new Input;
    bool result = false;
    
    in.open(filename.c_str());
    
    if (in.is_open()) {     // if file is available, open and read
        while (!in.eof()) {     // execute until last line of file
            line.clear();
            in >> line;
            if (line.find("//")) {
                std::string::size_type index = line.find("//");
                if (index != std::string::npos) {
                    line.erase(line.begin() + index, line.end());
                }
            }
            if (line.find("input")) {
                newInput->scanString(line);
            }
            else if (line.find("output")) {
                // setup output class
            }
            else if (line.find("wire")) {
                // setup wire class
            }
            else if (line.find("=")) {
                // setup equation
            }
        }
        result = true;      // set outcome as true for successful read
    }
    
    if (in.fail()) {
        
    }
    
    in.close();
    return result;
}


int main(int argc, char *argv[]) {
    if (argc != 3) {        // if arguments found is not 3, display user statement and exit
        std::cout << "Usage: dpgen netlistFile verilogFile" << std::endl;
        return EXIT_FAILURE;
    }
    
    if (readFile(argv[1]) == false) {
        std::cout << "Failed to read variables from file." << std::endl;
        return EXIT_FAILURE;
    }
    
    return 0;
}
