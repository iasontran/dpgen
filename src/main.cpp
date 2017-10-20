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
#include <cstdio>
#include <iostream>
#include <string>
#include <cstdlib>

int main(int argc, char *argv[]) {
    if (argc != 3) {        // if arguments found is not 3, display user statement and exit
        std::cout << "Usage: dpgen netlistFile verilogFile" << std::endl;
        return EXIT_FAILURE;
    }
    
    
    
    return 0;
}
