/**************************************************************************************************/

/*
 * File: main.cpp
 * Author: Jason Tran, Andrew Camps
 * NetID: ichikasuto, andrewcamps
 * Date: October 20, 2017
 *
 * Description:
 *
 */
/**************************************************************************************************/

#include "Scanner.h"

bool readFile(std::string filename) {
    std::fstream in;
    std::string line;
    bool result = false;
    
    in.open(filename.c_str());
    
    if (in.is_open()) {     // if file is available, open and read
        while (!in.eof()) {     // execute until last line of file
            line.clear();
            std::getline(in, line);
            std::string::size_type index;
            
            /* Removes all comments from line */
            if ((index = line.find("//")) != std::string::npos) {
                line.erase(line.begin() + index, line.end());
            }
            
            /* Decide what type of statement the line is */
            if (line.find("input ") != std::string::npos) {
                Scanner *type_input = new Scanner(Scanner::INPUT);
                type_input->scanLine(line);
                
            }
            else if (line.find("output ") != std::string::npos) {
                Scanner *type_output = new Scanner(Scanner::OUTPUT);
                type_output->scanLine(line);
                
            }
            else if (line.find("wire ") != std::string::npos) {
                Scanner *type_wire = new Scanner(Scanner::WIRE);
                type_wire->scanLine(line);
                
            }
            else if (line.find("register ") != std::string::npos) {
                Scanner *type_register = new Scanner(Scanner::REGISTER);
                type_register->scanLine(line);
                
            }
            else if(line.find("=") != std::string::npos){
                Scanner *type_operation = new Scanner(Scanner::OPERATION);
                type_operation->scanLine(line);
                
            } /* Empty line or invalid line syntax */
            else{
                /* Invalid input line syntax */
                if(!line.empty()){
                    std::cout << "Invalid line syntax: " << line << std::endl;
                }
            }
        }
        result = true;      // set outcome as true for successful read
    }
    
    /* Input file error */
    if (in.fail()) {
        std::cout << "No input file found with the name: " << filename << std::endl;
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
