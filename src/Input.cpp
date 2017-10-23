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
    if(this->dataWidth > 1){
        width = "[" + to_string(this->dataWidth - 1) + ":0]";
    }
    
    return "input " + width + this->name + ";";
}
