/*************/
/*
 * File: Wire.cpp
 * Author: Jason Tran, Andrew Camps
 * NetID: ichikasuto, andrewcamps
 * Date: October 21, 207
 *
 * Description:
 */

#include "Wire.h"

Wire::Wire(string name, int width, bool usigned, bool reg){
    this->name = name;
    this->dataWidth = width;
    this->usigned = usigned;
    this->reg = reg;
}

string Wire::toString(){
    string width = "";
    if(this->dataWidth > 1){
        width = "[" + to_string(this->dataWidth - 1) + ":0] ";
    }
    
    return "\twire " + width + this->name + ";";
}
