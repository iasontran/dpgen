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
    
    /* Define Clk and Rst for all modules */
    this->inputs.push_back(new Input("Clk", 1, false));
    this->inputs.push_back(new Input("Rst", 1, false));
    
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
            while(1){
                string::size_type index;
                if((index = name.find(' ')) != string::npos){
                    name.erase(name.begin() + index, name.end());
                }
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
            while(1){
                string::size_type index;
                if((index = name.find(' ')) != string::npos){
                    name.erase(name.begin() + index, name.end());
                }
                this->outputs.push_back(new Output(name, size, usigned));
                if(line.find(',') == string::npos){
                    break;
                }
                line.erase(0, line.find(" ") + 1);
                name = line.substr(0, line.find(", "));
            }
            break;
        case WIRE:
        case REGISTER:
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
            while(1){
                string::size_type index;
                if((index = name.find(' ')) != string::npos){
                    name.erase(name.begin() + index, name.end());
                }
                this->wires.push_back(new Wire(name, size, usigned));
                if(line.find(',') == string::npos){
                    break;
                }
                line.erase(0, line.find(" ") + 1);
                name = line.substr(0, line.find(", "));
            }
            
            break;
        case OPERATION:
            Operation *newOp = new Operation();
            bool assigned;
            
            /* Gets the name of the first variable in operation */
            // TODO: Take into account multiple spaces or tabs
            name = line.substr(0, line.find(" "));
            
            /* Assign out wire or output */
            assigned = false;
            for(int i = 0; i < (signed)this->wires.size(); i++){
                if(!name.compare(wires.at(i)->getName())){
                    newOp->wireNext = wires.at(i);
                    assigned = true;
                    break;
                }
            }
            if(!assigned){
                for(int i = 0; i < (signed)this->outputs.size(); i++){
                    if(!name.compare(outputs.at(i)->getName())){
                        newOp->outNext = outputs.at(i);
                        assigned = true;
                        break;
                    }
                }
            }

            /* No assignment was defined */
            if(!assigned){
                cout << "ERROR: Missing wire or ouput varible definition for: " << name << endl;
                return false;
            }
            
            /* Removes first equals sign of equation */
            // TODO: Take into account multiple spaces or tabs
            line.erase(0, line.find(" ") + 1);
            line.erase(0, line.find(" ") + 1);
            name = line.substr(0, line.find(" "));
            
            /* Assign out Input or Wire to operation */
            assigned = false;
            for(int i = 0; i < (signed)this->inputs.size(); i++){
                if(!name.compare(inputs.at(i)->getName())){
                    newOp->inInput[0] = inputs.at(i);
                    inputs.at(i)->toOperations.push_back(newOp);
                    assigned = true;
                    break;
                }
            }
            if(!assigned){
                for(int i = 0; i < (signed)this->wires.size(); i++){
                    if(!name.compare(wires.at(i)->getName())){
                        newOp->inWire[0] = wires.at(i);
                        wires.at(i)->toOperations.push_back(newOp);
                        assigned = true;
                        break;
                    }
                }
            }
            
            /* No assignment was defined */
            if(!assigned){
                cout << "ERROR: Missing input or wire varible definition for: " << name << endl;
                return false;
            }
            
            /* Get operation type */
            // TODO: Take into account multiple spaces or tabs
            line.erase(0, line.find(" ") + 1);
            name = line.substr(0, line.find(" "));
            
            /* ADD or INC */
            if(name.compare("+") == 0){
                // TODO: Take into account multiple spaces or tabs
                line.erase(0, line.find(" ") + 1);
                name = line.substr(0, line.find(" "));
                if(name.compare("1") == 0){
                    newOp->setOperation(Operation::INC);
                    newOp->setOpID(getID(Operation::INC));
                    this->operations.push_back(newOp);
                    return true;
                }
                newOp->setOperation(Operation::ADD);
                newOp->setOpID(getID(Operation::ADD));
            } /* SUB or DEC */
            else if(name.compare("-") == 0){
                // TODO: Take into account multiple spaces or tabs
                line.erase(0, line.find(" ") + 1);
                name = line.substr(0, line.find(" "));
                if(name.compare("1") == 0){
                    newOp->setOperation(Operation::DEC);
                    newOp->setOpID(getID(Operation::DEC));
                    this->operations.push_back(newOp);
                    return true;
                }
                newOp->setOperation(Operation::SUB);
                newOp->setOpID(getID(Operation::SUB));
            } /* MUL */
            else if(name.compare("*") == 0){
                newOp->setOperation(Operation::MUL);
                newOp->setOpID(getID(Operation::MUL));
            } /* COMP_GT */
            else if(name.compare(">") == 0){
                newOp->setOperation(Operation::COMP_GT);
                newOp->setOpID(getID(Operation::COMP_GT));
            } /* COMP_LT */
            else if(name.compare("<") == 0){
                newOp->setOperation(Operation::COMP_LT);
                newOp->setOpID(getID(Operation::COMP_LT));
            } /* COMP_EQ */
            else if(name.compare("==") == 0){
                newOp->setOperation(Operation::COMP_EQ);
                newOp->setOpID(getID(Operation::COMP_EQ));
            } /* MUX2x1 */
            else if(name.compare("?") == 0){
                newOp->setOperation(Operation::MUX2x1);
                newOp->setOpID(getID(Operation::MUX2x1));
            } /* SHR */
            else if(name.compare(">>") == 0){
                newOp->setOperation(Operation::SHR);
                newOp->setOpID(getID(Operation::SHR));
            } /* SHL */
            else if(name.compare("<<") == 0){
                newOp->setOperation(Operation::SHL);
                newOp->setOpID(getID(Operation::SHL));
            } /* DIV */
            else if(name.compare("/") == 0){
                newOp->setOperation(Operation::DIV);
                newOp->setOpID(getID(Operation::DIV));
            } /* MOD */
            else if(name.compare("%") == 0){
                newOp->setOperation(Operation::MOD);
                newOp->setOpID(getID(Operation::MOD));
            } /* REG */
            else{
                newOp->setOperation(Operation::REG);
                newOp->setOpID(getID(Operation::REG));
                newOp->inInput[1] = inputs.at(0);
                newOp->inInput[2] = inputs.at(1);
                this->operations.push_back(newOp);
                return true;
            }
            
            /* Get last wire or input name */
            if(newOp->getOperation() != Operation::ADD && newOp->getOperation() != Operation::SUB){
                // TODO: Take into account multiple spaces or tabs
                line.erase(0, line.find(" ") + 1);
                name = line.substr(0, line.find(" "));
            }
            
            /* Assign out Input or Wire to operation */
            assigned = false;
            for(int i = 0; i < (signed)this->inputs.size(); i++){
                if(!name.compare(inputs.at(i)->getName())){
                    newOp->inInput[1] = inputs.at(i);
                    inputs.at(i)->toOperations.push_back(newOp);
                    assigned = true;
                    break;
                }
            }
            if(!assigned){
                for(int i = 0; i < (signed)this->wires.size(); i++){
                    if(!name.compare(wires.at(i)->getName())){
                        newOp->inWire[1] = wires.at(i);
                        wires.at(i)->toOperations.push_back(newOp);
                        assigned = true;
                        break;
                    }
                }
            }
            
            /* No assignment was defined */
            if(!assigned){
                cout << "ERROR: Missing input or wire varible definition for: " << name << endl;
                return false;
            }
            
            if(newOp->getOperation() == Operation::MUX2x1){
                line.erase(0, line.find(" ") + 1);
                line.erase(0, line.find(" ") + 1);
                name = line.substr(0, line.find(" "));
                
                /* Assign out Input or Wire to operation */
                assigned = false;
                for(int i = 0; i < (signed)this->inputs.size(); i++){
                    if(!name.compare(inputs.at(i)->getName())){
                        newOp->inInput[2] = inputs.at(i);
                        inputs.at(i)->toOperations.push_back(newOp);
                        assigned = true;
                        break;
                    }
                }
                if(!assigned){
                    for(int i = 0; i < (signed)this->wires.size(); i++){
                        if(!name.compare(wires.at(i)->getName())){
                            newOp->inWire[2] = wires.at(i);
                            wires.at(i)->toOperations.push_back(newOp);
                            assigned = true;
                            break;
                        }
                    }
                }
                
                /* No assignment was defined */
                if(!assigned){
                    cout << "ERROR: Missing input or wire varible definition for: " << name << endl;
                    return false;
                }
            }
            
            /* Adds operation to module */
            this->operations.push_back(newOp);
            
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
int Module::getID(Operation::Operations operation){
    int id = 0;
    for(int i = 0; i < (signed)this->operations.size(); i++){
        if(this->operations.at(i)->getOperation() == operation){
            id++;
        }
    }
    
    return id;
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
    for(int i = 0; i < (signed)this->inputs.size(); i++){
        out << inputs.at(i)->getName() << ", ";;
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
    for(int i = 0; i < (signed)this->inputs.size(); i++){
        out << inputs.at(i)->toString() << endl;
    }
    out << endl;
    for(int i = 0; i < (signed)this->outputs.size(); i++){
        out << outputs.at(i)->toString() << endl;
    }
    out << endl;
    for(int i = 0; i < (signed)this->wires.size(); i++){
        out << wires.at(i)->toString() << endl;
    }
    out << endl;
    
    /* Prints operations */
    for(int i = 0; i < (signed)this->operations.size(); i++){
        out << operations.at(i)->toString() << endl;
    }
    out << endl;
    
    /* Prints ending */
    out << "endmodule" << endl;
    
    out.close();
    
    return true;
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
