//
//  Module.cpp
//  dpgen
//
//  Created by Andrew Camps on 10/22/17.
//

#include "Module.h"

Module::Module(string name){
    this->name = name;
}

string Module::getName(){
    return this->name;
}

/* Builds the data path graph */
bool Module::buildModule(string file){
    Scanner scan(file, this);
    if(!scan.readFile()){
        cout << "Error reading file" << endl;
        return false;
    }
    
    return true;
}

/* Prints the module in .v format */
bool Module::outputModule(string file){
    return true;
}

/* Calculates the critical path of the graph */
int Module::criticalPathDelay(){
    return 0;
}
