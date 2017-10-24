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

#include "Output.h"
#include "Input.h"
#include "Register.h"
#include "Wire.h"
#include "Operation.h"

using namespace std;

class Module {
private:
    string name;
    vector<Operation *> nodes;
    vector<Output *> outputs;
    vector<Input *> inputs;
    vector<Register *> regs;
    vector<Wire *> wires;
    enum Type { INPUT, OUTPUT, WIRE, REGISTER, OPERATION };
    bool readFile(string file);
    bool getDataType(string type, int *size);
    bool parseLine(string line, Type type);
    void outputOperationGraph();
public:
    Module(string name);
    string getName() { return name; }
    bool buildModule(string file); /* Builds the data path graph */
    bool outputModule(string file); /* Prints the module in .v format */
    int criticalPathDelay(); /* Calculates the critical path of the graph */
};

#endif /* Module_h */
