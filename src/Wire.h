/*************/
/*
 * File: Wire.h
 * Author: Jason Tran, Andrew Camps
 * NetID: ichikasuto, andrewcamps
 * Date: October 20, 2017
 *
 * Description:
 */

#ifndef Wire_h
#define Wire_h

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <cctype>

#include "Operation.h"

using namespace std;

class Operation;

class Wire {
private:
    bool usigned;
    bool reg;
    int dataWidth;
    string name;
public:
    Wire(string name, int width, bool usigned, bool reg);
    string getName() { return name; }
    int getWidth() { return dataWidth; }
    bool isUnsigned() { return usigned; }
    bool isRegister() { return reg; }
    string toString();
    vector<Operation *> toOperations;
};

#endif

