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

/**
 * @brief Builds the datapath graph
 *
 *
 *
 * @param
 * @return
 */
bool Module::buildModule(string file){
    if(!readFile(file)){
        cout << "Error reading file" << endl;
        return false;
    }
    
    return true;
}

/**
 * @brief
 *
 *
 *
 * @param
 * @return
 */
bool Module::readFile(string file){
    fstream in;
    
    in.open(file.c_str());
    
    if (!in.is_open()) {     // if file is available, open and read
        cout << "No input file found with the name: " << file << endl;
        return false;
    }
    
    while (!in.eof()) {     // execute until last line of file
        string line;
        getline(in, line);
        
        /* Removes all comments from line */
        string::size_type index;
        if ((index = line.find("//")) != string::npos) {
            line.erase(line.begin() + index, line.end());
        }
        
        /* Decide what type of statement the line is */
        if(line.find("=") != string::npos){
            if(!parseLine(line, OPERATION)){
                cout << "Invalid line syntax: " << line << endl;
                return false;
            }
        }
        else if (line.find("input ") != string::npos) {
            line.erase(0, line.find(" ") + 1);
            if(!parseLine(line, INPUT)){
                cout << "Invalid line syntax: " << line << endl;
                return false;
            }
            
        }
        else if (line.find("output ") != string::npos) {
            line.erase(0, line.find(" ") + 1);
            if(!parseLine(line, OUTPUT)){
                cout << "Invalid line syntax: " << line << endl;
                return false;
            }
            
        }
        else if (line.find("wire ") != string::npos) {
            line.erase(0, line.find(" ") + 1);
            if(!parseLine(line, WIRE)){
                cout << "Invalid line syntax: " << line << endl;
                return false;
            }
            
        }
        else if (line.find("register ") != string::npos) {
            line.erase(0, line.find(" ") + 1);
            if(!parseLine(line, REGISTER)){
                cout << "Invalid line syntax: " << line << endl;
                return false;
            }
            
        } /* Empty line or invalid line syntax */
        else{
            /* Invalid input line syntax */
            if(!line.empty()){
                cout << "Invalid line syntax: " << line << endl;
                return false;
            }
        }
    }
    
    in.close();
    
    return true;
}

/**
 * @brief
 *
 *
 *
 * @param
 * @return
 */
bool Module::parseLine(string line, Type type) {
    string dataType;
    string name;
    int size;
    bool usigned;
    
    switch(type){
        case INPUT:
            
            /* Gets the type of data */
            dataType = line.substr(0, line.find(" "));
            line.erase(0, line.find(" ") + 1);
            usigned = getDataType(dataType, &size);
            if(size < 0){
                cout << "Invalid data type: " << dataType << endl;
                return false;
            }
            
            /* Gets the name of each variable and creates object */
            name = line.substr(0, line.find(", "));
            while(name.compare("") > 0){
                this->inputs.push_back(new Input(name, size, usigned));
                if(line.find(',') == string::npos){
                    break;
                }
                line.erase(0, line.find(" ") + 1);
                name = line.substr(0, line.find(", "));
            }
            
            break;
        case OUTPUT:
            /* Gets the type of data */
            dataType = line.substr(0, line.find(" "));
            line.erase(0, line.find(" ") + 1);
            usigned = getDataType(dataType, &size);
            if(size < 0){
                cout << "Invalid data type: " << dataType << endl;
                return false;
            }
            
            /* Gets the name of each variable and creates object */
            name = line.substr(0, line.find(", "));
            while(name.compare("") > 0){
                this->outputs.push_back(new Output(name, size, usigned));
                if(line.find(',') == string::npos){
                    break;
                }
                line.erase(0, line.find(" ") + 1);
                name = line.substr(0, line.find(", "));
            }
            break;
        case WIRE:
            /* Gets the type of data */
            dataType = line.substr(0, line.find(" "));
            line.erase(0, line.find(" ") + 1);
            usigned = getDataType(dataType, &size);
            if(size < 0){
                cout << "Invalid data type: " << dataType << endl;
                return false;
            }
            
            /* Gets the name of each variable and creates object */
            name = line.substr(0, line.find(", "));
            while(name.compare("") > 0){
                this->wires.push_back(new Wire(name, size, usigned));
                if(line.find(',') == string::npos){
                    break;
                }
                line.erase(0, line.find(" ") + 1);
                name = line.substr(0, line.find(", "));
            }
            break;
        case REGISTER:
            dataType = line.substr(0, line.find(" "));
            line.erase(0, line.find(" ") + 1);
            usigned = getDataType(dataType, &size);
            if(size < 0){
                cout << "Invalid data type: " << dataType << endl;
                return false;
            }
            
            
            
            break;
        case OPERATION:
            
            
            break;
    }
    
    return true; // No error
}

/**
 * @brief
 *
 *
 *
 * @param
 * @return
 */
bool Module::getDataType(string type, int *size){
    
    /* Return data width */
    if(!type.compare("Int1") || !type.compare("UInt1")){
        *size = 1;
    }
    else if(!type.compare("Int2") || !type.compare("UInt2")){
        *size = 2;
    }
    else if(!type.compare("Int8") || !type.compare("UInt8")){
        *size = 8;
    }
    else if(!type.compare("Int16") || !type.compare("UInt16")){
        *size = 16;
    }
    else if(!type.compare("Int32") || !type.compare("UInt32")){
        *size = 32;
    }
    else if(!type.compare("Int64") || !type.compare("UInt64")){
        *size = 64;
    } /* Invalid data type */
    else{
        *size = -1; // error
    }
    
    /* return signed or unsigned */
    return type.find("UInt") ? false : true;
}

/**
 * @brief Prints the module in .v format
 *
 *
 *
 * @param
 * @return
 */
bool Module::outputModule(string file){
    ofstream out;
    
    out.open(file.c_str());
    
    if (!out.is_open()) {     // if file is available, open and read
        cout << "Error opening up file: " << file << endl;
        return false;
    }
    
    /* Prints heading */
    out << "`timescale 1ns / 1ns" << endl << endl;
    out << "module " << this->name << "(";
    for(auto &i : this->inputs){
        out << i->getName() << ", ";
    }
    for(int i = 0; i < (signed)this->outputs.size(); i++){
        if(i == (signed)this->outputs.size() - 1){
            out << outputs.at(i)->getName();
            break;
        }
        out << outputs.at(i)->getName() << ", ";
    }
    out << ");" << endl << endl;
    
    /* Prints all inputs, outputs, wires */
    for(auto &i : this->inputs){
        out << i->toString() << endl;
    }
    out << endl;
    for(auto &i : this->outputs){
        out << i->toString() << endl;
    }
    out << endl;
    for(auto &i : this->wires){
        out << i->toString() << endl;
    }
    out << endl;
    
    /* Prints operations */
    outputOperationGraph();
    
    /* Prints ending */
    out << "endmodule" << endl;
    
    out.close();
    
    return true;
}

/**
 * @brief
 *
 *
 *
 * @param
 * @return
 */
void Module::outputOperationGraph(){
    
}

/**
 * @brief Calculates the critical path of the graph
 *
 *
 *
 * @param
 * @return
 */
int Module::criticalPathDelay(){
    return 0;
}
