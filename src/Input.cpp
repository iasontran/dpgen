//
//  Input.cpp
//  dpgen
//
//  Created by Andrew Camps on 10/22/17.
//

#include "Input.h"


Input::Input(string name, int width, bool usigned){
    this->name = name;
    this->dataWidth = width;
    this->usigned = usigned;
}

string Input::toString(){
    string width = "";
    string sign = "";
    if(this->dataWidth > 1){
        width = "[" + to_string(this->dataWidth - 1) + ":0] ";
    }
    
    if(!this->isUnsigned()){
        sign = "signed ";
    }
    
    return "\tinput " + sign + width + this->name + ";";
}
