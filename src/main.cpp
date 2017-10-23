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

#include "Module.h"

#define INFILE 1
#define OUTFILE 2

using namespace std;

int main(int argc, char *argv[]) {
    Module *module;
    
    /* If arguments found is not 3, display user statement and exit */
    if (argc != 3) {
        cout << "Usage: dpgen netlistFile verilogFile" << endl;
        return EXIT_FAILURE;
    }
    
    /* Initialize the module */
    string moduleName = argv[OUTFILE];
    moduleName.erase(moduleName.begin() + moduleName.find("."), moduleName.end());
    module = new Module(moduleName);
    
    /* Build module datapath from input file */
    if (!module->buildModule(argv[INFILE])) {
        cout << "Failed to build module from input file: " << argv[INFILE] << endl;
        return EXIT_FAILURE;
    }
    
    /* Output datapath module to .v file */
    if(!module->outputModule(argv[OUTFILE])){
        cout << "Failed to create output module file: " << argv[OUTFILE] << endl;
        return EXIT_FAILURE;
    }
    
    /* Print critical path delay of the module */
    cout << "Critical Path : " << module->criticalPathDelay() << " ns" << endl;
    
    return 0;
}
