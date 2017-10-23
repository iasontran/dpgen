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

Wire::Wire(string name, int width, bool usigned){
    this->name = name;
    this->dataWidth = width;
    this->usigned = usigned;
}

string Wire::getName(){
    return this->name;
}

int Wire::getWidth(){
    return this->dataWidth;
}

bool Wire::isUnsigned(){
    return this->usigned;
}

string Wire::toString(){
    string width = "";
    if(this->dataWidth > 1){
        width = "[" + to_string(this->dataWidth - 1) + ":0]";
    }
    
    return "wire " + width + this->name + ";";
}
