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
    ofstream out;
    
    out.open(file.c_str());
    
    if (!out.is_open()) {     // if file is available, open and read
        cout << "Error opening up file: " << file << endl;
        return false;
    }
    
    out << "`timescale 1ns / 1ns" << endl << endl;
    out << "module " << this->name << "(";
    // TODO: Print input and output names by cycling through vectors
    out << ");" << endl << endl;
    // TODO: Print all inputs, outputs, wires, registers
    outputOperationGraph();
    out << "endmodule" << endl;
    
    out.close();
    
    return true;
}

void Module::outputOperationGraph(){
    
}

/* Calculates the critical path of the graph */
int Module::criticalPathDelay(){
    return 0;
}
