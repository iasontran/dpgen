//
//  Module.h
//  dpgen
//
//  Created by Andrew Camps on 10/22/17.
//

#ifndef Module_h
#define Module_h

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <cctype>

#include "Operation.h"
#include "Scanner.h"

using namespace std;

class Module {
private:
    string name;
    vector<Operation *> nodes;
public:
    Module(string name);
    string getName();
    bool buildModule(string file); /* Builds the data path graph */
    bool outputModule(string file); /* Prints the module in .v format */
    int criticalPathDelay(); /* Calculates the critical path of the graph */
};

#endif /* Module_h */
