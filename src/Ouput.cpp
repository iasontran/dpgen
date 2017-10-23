/*************/
/*
 * File: Output.cpp
 * Author: Jason Tran, Andrew Camps
 * NetID: ichikasuto, andrewcamps
 * Date: October 21, 207
 *
 * Description:
 */

#include "Output.h"

Output::Output(string name, int width, bool usigned){
    this->name = name;
    this->dataWidth = width;
    this->usigned = usigned;
}

string Output::toString(){
    return "";
}
