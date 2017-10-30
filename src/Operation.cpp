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

double Operation::reg_delay[NUM_SIZES] = { 2.616, 2.644, 2.879, 3.061, 3.602, 3.966 };
double Operation::add_delay[NUM_SIZES] = { 2.704, 3.713, 4.924, 5.638, 7.270, 9.566 };
double Operation::sub_delay[NUM_SIZES] = { 3.024, 3.412, 4.890, 5.569, 7.253, 9.566 };
double Operation::mul_delay[NUM_SIZES] = { 2.438, 3.651, 7.453, 7.811, 12.395, 15.354 };
double Operation::comp_delay[NUM_SIZES] = { 3.031, 3.934, 5.949, 6.256, 7.264, 8.416 };
double Operation::mux_delay[NUM_SIZES] = { 4.083, 4.115, 4.815, 5.623, 8.079, 8.766 };
double Operation::shr_delay[NUM_SIZES] = { 3.644, 4.007, 5.178, 6.460, 8.819, 11.095 };
double Operation::shl_delay[NUM_SIZES] = { 3.614, 3.980, 5.152, 6.549, 8.565, 11.220 };
double Operation::div_delay[NUM_SIZES] = { 0.619, 2.144, 15.439, 33.093, 86.312, 243.233 };
double Operation::mod_delay[NUM_SIZES] = { 0.758, 2.149, 16.078, 35.563, 88.142, 250.583 };
double Operation::inc_delay[NUM_SIZES] = { 1.792, 2.218, 3.111, 3.471, 4.347, 6.200 };
double Operation::dec_delay[NUM_SIZES] = { 1.792, 2.218, 3.108, 3.701, 4.685, 6.503 };

Operation::Operation(){
    for(int i = 0; i < NUM_INPUTS; i++){
        inWire[i] = NULL;
        inInput[i] = NULL;
    }
    
    outNext = NULL;
    wireNext = NULL;
}

void Operation::calcWidth(){
    int width0;
    int width1;
    
    if(operation == COMP_GT || operation == COMP_LT || operation == COMP_EQ){
        width0 = inWire[0] == NULL ? inInput[0]->getWidth() : inWire[0]->getWidth();
        width1 = inWire[1] == NULL ? inInput[1]->getWidth() : inWire[1]->getWidth();
        this->width = width0 > width1 ? width0 : width1;
    }else{
        this->width = outNext == NULL ? wireNext->getWidth() : outNext->getWidth();
    }
}

void Operation::setSign() {
    bool usigned = true;
    
    for(int i = 0; i < NUM_INPUTS; i++){
        if(inWire[i] != NULL){
            if(!inWire[i]->isUnsigned()){
                usigned = false;
                break;
            }
        }
        if(inInput[i] != NULL){
            if(!inInput[i]->isUnsigned()){
                usigned = false;
                break;
            }
        }
    }
    
    if(outNext != NULL){
        if(!outNext->isUnsigned())
        usigned = false;
    }
    if(wireNext != NULL){
        if(!wireNext->isUnsigned()){
            usigned = false;
        }
    }
    
    this->usigned = usigned;
    sign = usigned ? "" : "S";
}

double Operation::getDelay(){
    int index;
    
    switch(width){
        case 1:
            index = 0;
            break;
        case 2:
            index = 1;
            break;
        case 8:
            index = 2;
            break;
        case 16:
            index = 3;
            break;
        case 32:
            index = 4;
            break;
        case 64:
            index = 5;
            break;
    }
    
    switch(operation){
        case INC:
            return inc_delay[index];
        case DEC:
            return dec_delay[index];
        case ADD:
            return add_delay[index];
        case SUB:
            return sub_delay[index];
        case MUL:
            return mul_delay[index];
        case COMP_GT:
        case COMP_LT:
        case COMP_EQ:
            return comp_delay[index];
        case SHR:
            return shr_delay[index];
        case SHL:
            return shl_delay[index];
        case DIV:
            return div_delay[index];
        case MOD:
            return mod_delay[index];
        case MUX2x1:
            return mux_delay[index];
        case REG:
            return reg_delay[index];
    }
    
    return 0;
}

string Operation::toString(){
    string outName = outNext == NULL ? wireNext->getName() : outNext->getName();
    string in0 = inWire[0] == NULL ? inInput[0]->getName() : inWire[0]->getName();
    string in1;
    string in2;
    
    switch(operation){
        case INC:
            return "\t" + sign + "INC #(" + to_string(width) + ") inc" + to_string(getOpID()) + "(" + in0 + ", " + outName + ");";
        case DEC:
            return "\t" + sign + "DEC #(" + to_string(width) + ") dec" + to_string(getOpID()) + "(" + in0 + ", " + outName + ");";
        case ADD:
            in1 = inWire[1] == NULL ? inInput[1]->getName() : inWire[1]->getName();
            return "\t" + sign + "ADD #(" + to_string(width) + ") add" + to_string(getOpID()) + "(" + in0 + ", " + in1 + ", " + outName + ");";
        case SUB:
            in1 = inWire[1] == NULL ? inInput[1]->getName() : inWire[1]->getName();
            return "\t" + sign + "SUB #(" + to_string(width) + ") sub" + to_string(getOpID()) + "(" + in0 + ", " + in1 + ", " + outName + ");";
        case MUL:
            in1 = inWire[1] == NULL ? inInput[1]->getName() : inWire[1]->getName();
            return "\t" + sign + "MUL #(" + to_string(width) + ") mul" + to_string(getOpID()) + "(" + in0 + ", " + in1 + ", " + outName + ");";
        case COMP_GT:
            in1 = inWire[1] == NULL ? inInput[1]->getName() : inWire[1]->getName();
            return "\t" + sign + "COMP #(" + to_string(width) + ") comp_gt" + to_string(getOpID()) + "(" + in0 + ", " + in1 + ", " + outName + ", , " + ");";
        case COMP_LT:
            in1 = inWire[1] == NULL ? inInput[1]->getName() : inWire[1]->getName();
            return "\t" + sign + "COMP #(" + to_string(width) + ") comp_lt" + to_string(getOpID()) + "(" + in0 + ", " + in1 + ", , " + outName + ", " + ");";
        case COMP_EQ:
            in1 = inWire[1] == NULL ? inInput[1]->getName() : inWire[1]->getName();
            return "\t" + sign + "COMP #(" + to_string(width) + ") comp_eq" + to_string(getOpID()) + "(" + in0 + ", " + in1 + ", , , " + outName + ");";
        case SHR:
            in1 = inWire[1] == NULL ? inInput[1]->getName() : inWire[1]->getName();
            return "\t" + sign + "SHR #(" + to_string(width) + ") shr" + to_string(getOpID()) + "(" + in0 + ", " + in1 + ", " + outName + ");";
        case SHL:
            in1 = inWire[1] == NULL ? inInput[1]->getName() : inWire[1]->getName();
            return "\t" + sign + "SHL #(" + to_string(width) + ") shl" + to_string(getOpID()) + "(" + in0 + ", " + in1 + ", " + outName + ");";
        case DIV:
            in1 = inWire[1] == NULL ? inInput[1]->getName() : inWire[1]->getName();
            return "\t" + sign + "DIV #(" + to_string(width) + ") div" + to_string(getOpID()) + "(" + in0 + ", " + in1 + ", " + outName + ");";
        case MOD:
            in1 = inWire[1] == NULL ? inInput[1]->getName() : inWire[1]->getName();
            return "\t" + sign + "MOD #(" + to_string(width) + ") mod" + to_string(getOpID()) + "(" + in0 + ", " + in1 + ", " + outName + ");";
        case MUX2x1:
            in1 = inWire[1] == NULL ? inInput[1]->getName() : inWire[1]->getName();
            in2 = inWire[2] == NULL ? inInput[2]->getName() : inWire[2]->getName();
            return "\t" + sign + "MUX2x1 #(" + to_string(width) + ") mux" + to_string(getOpID()) + "(" + in0 + ", " + in1 + ", " + in2 + ", " + outName + ");";
        case REG:
            in1 = inInput[1]->getName();
            in2 = inInput[2]->getName();
            return "\t" + sign + "REG #(" + to_string(width) + ") reg" + to_string(getOpID()) + "(" + in0 + ", " + in1 + ", " + in2 + ", " + outName + ");";
    }
    
    return NULL;
}

