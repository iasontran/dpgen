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

#define NUM_INPUTS 3

using namespace std;

class Wire;
class Input;

class Operation {
public:
    enum Operations { REG, ADD, SUB, MUL, COMP_GT, COMP_LT, COMP_EQ, MUX2x1, SHR, SHL, DIV, MOD, INC, DEC };
    Operations getOperation() { return operation; }
    void setOperation(Operations op) {operation = op; }
    int getOpID() { return operationID; }
    void setOpID(int ID) { operationID = ID; }
    string toString();
    Output *outNext;
    Wire *wireNext;
    Wire *inWire[NUM_INPUTS];
    Input *inInput[NUM_INPUTS];
private:
    Operations operation;
    int operationID;
};

#endif
