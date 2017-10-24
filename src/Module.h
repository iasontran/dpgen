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
#include "Input.h"
#include "Output.h"
#include "Wire.h"

using namespace std;

class Module {
private:
    string name;
    vector<Operation *> nodes;
    vector<Output *> outputs;
    vector<Input *> inputs;
    vector<Wire *> wires;
    enum Type { INPUT, OUTPUT, WIRE, REGISTER, OPERATION };
    bool readFile(string file);
    bool getDataType(string type, int *size);
    bool parseLine(string line, Type type);
public:
    Module(string name);
    string getName() { return name; }
    bool buildModule(string file); /* Builds the data path graph */
    bool outputModule(string file); /* Prints the module in .v format */
    int criticalPathDelay(); /* Calculates the critical path of the graph */
    void outputOperationGraph();
};

#endif /* Module_h */
