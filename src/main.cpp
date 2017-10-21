/**************************************************************************************************/

/*
 * File: main.cpp
 * Author: Jason Tran
 * NetID: ichikasuto
 * Date: October 20, 2017
 *
 * Description: Main function that runs through reading and checking of file.
 *
 */
/**************************************************************************************************/
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>

bool readFile(std::string filename) {
    std::fstream in;
    std::string line;
    bool result = false;
    
    in.open(filename.c_str());
    
    if (in.is_open()) {     // if file is available, open and read
        while (!in.eof()) {     // execute until last line of file
            line.clear();
            in >> line;
            if (line.find("//")) {
                // remove comment section
            }
            if (line.find("input")) {
                // setup input class
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
