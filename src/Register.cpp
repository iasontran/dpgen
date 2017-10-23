/*************/
/*
 * File: Register.cpp
 * Author: Jason Tran, Andrew Camps
 * NetID: ichikasuto, andrewcamps
 * Date: October 21, 207
 *
 * Description:
 */

#include "Register.h"

Register::Register(string name, int width, bool usigned){
    this->name = name;
    this->dataWidth = width;
    this->usigned = usigned;
}

string Register::toString(){
    return "";
}
