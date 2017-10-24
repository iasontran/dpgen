/*************/
/*
 * File: Operation.h
 * Author: Jason Tran, Andrew Camps
 * NetID: ichikasuto, andrewcamps
 * Date: October 20, 2017
 *
 * Description:
 */

#ifndef Operation_h
#define Operation_h

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <cctype>

#include "Output.h"
#include "Input.h"
#include "Wire.h"

using namespace std;

class Operation {
private:
    enum Operations { REG, ADD, SUB, MUL, COMP_GT, COMP_LT, COMP_EQ, MUX2x1, SHR, SHL, DIV, MOD, INC, DEC };
    Operations operation;
    Output *outNext;
    Wire *wireNext;
public:
    Operation(Operations operation);
    Operations getOperation() { return operation; }
    string toString();
    
};

#endif
