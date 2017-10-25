/*************/
/*
 * File: Operation.cpp
 * Author: Jason Tran, Andrew Camps
 * NetID: ichikasuto, andrewcamps
 * Date: October 21, 207
 *
 * Description:
 */

#include "Operation.h"

string Operation::toString(){
    string outName = outNext == NULL ? wireNext->getName() : outNext->getName();
    string in0 = inWire[0] == NULL ? inInput[0]->getName() : inWire[0]->getName();
    string in1;
    string in2;
    
    switch(this->operation){
        case REG:
            in1 = inInput[1]->getName();
            in2 = inInput[2]->getName();
            return "\tREG #() reg" + to_string(getOpID()) + "(" + in0 + ", " + in1 + ", " + in2 + ", " + outName + ");";
        case INC:
            return "\tINC #() inc" + to_string(getOpID()) + "(" + in0 + ", " + outName + ");";
        case DEC:
            return "\tDEC #() dec" + to_string(getOpID()) + "(" + in0 + ", " + outName + ");";
        case ADD:
            in1 = inWire[1] == NULL ? inInput[1]->getName() : inWire[1]->getName();
            return "\tADD #() add" + to_string(getOpID()) + "(" + in0 + ", " + in1 + ", " + outName + ");";
        case SUB:
            in1 = inWire[1] == NULL ? inInput[1]->getName() : inWire[1]->getName();
            return "\tSUB #() sub" + to_string(getOpID()) + "(" + in0 + ", " + in1 + ", " + outName + ");";
        case MUL:
            in1 = inWire[1] == NULL ? inInput[1]->getName() : inWire[1]->getName();
            return "\tMUL #() mul" + to_string(getOpID()) + "(" + in0 + ", " + in1 + ", " + outName + ");";
        case COMP_GT:
            in1 = inWire[1] == NULL ? inInput[1]->getName() : inWire[1]->getName();
            return "\tCOMP #() comp_gt" + to_string(getOpID()) + "(" + in0 + ", " + in1 + ", " + outName + ", , " + ");";
        case COMP_LT:
            in1 = inWire[1] == NULL ? inInput[1]->getName() : inWire[1]->getName();
            return "\tCOMP #() comp_lt" + to_string(getOpID()) + "(" + in0 + ", " + in1 + ", , " + outName + ", " + ");";
        case COMP_EQ:
            in1 = inWire[1] == NULL ? inInput[1]->getName() : inWire[1]->getName();
            return "\tCOMP #() comp_eq" + to_string(getOpID()) + "(" + in0 + ", " + in1 + ", , , " + outName + ");";
        case SHR:
            in1 = inWire[1] == NULL ? inInput[1]->getName() : inWire[1]->getName();
            return "\tSHR #() shr" + to_string(getOpID()) + "(" + in0 + ", " + in1 + ", " + outName + ");";
        case SHL:
            in1 = inWire[1] == NULL ? inInput[1]->getName() : inWire[1]->getName();
            return "\tSHL #() shl" + to_string(getOpID()) + "(" + in0 + ", " + in1 + ", " + outName + ");";
        case DIV:
            in1 = inWire[1] == NULL ? inInput[1]->getName() : inWire[1]->getName();
            return "\tDIV #() div" + to_string(getOpID()) + "(" + in0 + ", " + in1 + ", " + outName + ");";
        case MOD:
            in1 = inWire[1] == NULL ? inInput[1]->getName() : inWire[1]->getName();
            return "\tMOD #() mod" + to_string(getOpID()) + "(" + in0 + ", " + in1 + ", " + outName + ");";
        case MUX2x1:
            in1 = inWire[1] == NULL ? inInput[1]->getName() : inWire[1]->getName();
            in2 = inWire[2] == NULL ? inInput[2]->getName() : inWire[2]->getName();
            return "\tMUX2x1 #() mux" + to_string(getOpID()) + "(" + in0 + ", " + in1 + ", " + in2 + ", " + outName + ");";
    }
    
    return NULL;
}

