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
        
        /* Parse line */
        if(!parseLine(split(line))){
            cout << "Invalid line syntax: " << line << endl;
            return false;
        }
    }
    
    in.close();
    
    return true;
}

/**
 * @brief Tokenizing a string
 *
 *
 *
 * @param
 * @return
 */
vector<string> Module::split(string const &input) {
    istringstream buffer(input);
    vector<string> ret((istream_iterator<string>(buffer)), istream_iterator<string>());
    return ret;
}

/**
 * @brief
 *
 *
 *
 * @param
 * @return
 */
bool Module::parseLine(vector<string> line) {
    Type lineType;
    int size;
    
    /* Skip empty empty lines */
    if(!line.size()){
        return true;
    }
    
    /* Input */
    string type = line.front();
    if(type.compare("input") == 0){
        line.erase(line.begin());
        lineType = INPUT;
    } /* Output */
    else if(type.compare("output") == 0){
        line.erase(line.begin());
        lineType = OUTPUT;
    } /* Wire */
    else if(type.compare("wire") == 0){
        line.erase(line.begin());
        lineType = WIRE;
    } /* Register */
    else if(type.compare("register") == 0){
        line.erase(line.begin());
        lineType = REGISTER;
    } /* Operation or invalid line  */
    else {
        /* Checks for invalid line */
        if(line.at(1).compare("=") != 0){
            return false;
        }
        
        lineType = OPERATION;
    }
    
    /* Get data size, sign type and create object type */
    if(lineType == INPUT || lineType == OUTPUT || lineType == WIRE || lineType == REGISTER){
        
        /* Invalid line */
        if(!line.size()){
            return false;
        }
        
        bool usigned = getDataType(line.front(), &size);
        if(size < 0){
            cout << "Invalid data type: " << line.front() << endl;
            return false;
        }
        line.erase(line.begin());
        
        /* Invalid line */
        if(!line.size()){
            return false;
        }
        
        /* Loop until end of string */
        while(line.size() > 0){
            string name = line.front();
            
            /* Remove commas from variable list names */
            string::size_type index;
            if((index = name.find(',')) != string::npos){
                name.erase(name.begin() + index, name.end());
            }
            
            /* Create specific object type */
            switch(lineType){
                case INPUT:
                    this->inputs.push_back(new Input(name, size, usigned));
                    break;
                case OUTPUT:
                    this->outputs.push_back(new Output(name, size, usigned));
                    break;
                case WIRE:
                    this->wires.push_back(new Wire(name, size, usigned, false));
                    break;
                case REGISTER:
                    this->wires.push_back(new Wire(name, size, usigned, true));
                    break;
                case OPERATION:
                    /* do nothing */
                    break;
            }
            
            line.erase(line.begin());
        }
    } /* OPERATION */
    else {
        Operation *newOp = new Operation();
        Operation *regOp = NULL;
        string var;
        bool assigned;
        
        /* Checks to see if the first variable is an output type */
        var = line.front();
        assigned = false;
        for(int i = 0; i < (signed)this->outputs.size(); i++){
            /* Check if this is a not REG operation to output */
            if(var.compare(outputs.at(i)->getName()) == 0 && line.size() > 3){
                this->wires.push_back(new Wire(var + "wire", outputs.at(i)->getWidth(), outputs.at(i)->isUnsigned(), false));
                regOp = new Operation();
                regOp->setOperation(Operation::REG);
                regOp->setOpID(getID(Operation::REG));
                newOp->wireNext = wires.back();
                regOp->outNext = outputs.at(i);
                regOp->inWire[0] = wires.back();
                regOp->inInput[1] = inputs.at(0);
                regOp->inInput[2] = inputs.at(1);
                wires.back()->toOperations.push_back(regOp);
                assigned = true;
                break;
            } /* REG operation */
            else{

                /* Register or error */
                if(var.compare(outputs.at(i)->getName()) == 0 && line.size() == 3){
                    newOp->setOperation(Operation::REG);
                    newOp->setOpID(getID(Operation::REG));
                    newOp->outNext = outputs.at(i);
                    assigned = true;

                    

                    break;
                }
            }
        }
        if(!assigned){
            for(int i = 0; i < (signed)this->wires.size(); i++){
                if(var.compare(wires.at(i)->getName()) == 0){
                    newOp->wireNext = wires.at(i);
                    assigned = true;
                    break;
                }
            }
        }

        /* No assignment was defined */
        if(!assigned){
            cout << "ERROR: Missing wire or ouput varible definition for: " << var << endl;
            return false;
        }

        /* Remove first variable and equals sign in operation line */
        line.erase(line.begin());
        line.erase(line.begin());
        if(!line.size()){
            return false;
        }

        /* Assigns first Input or Wire to operation */
        assigned = false;
        var = line.front();
        for(int i = 0; i < (signed)this->inputs.size(); i++){
            if(var.compare(inputs.at(i)->getName()) == 0){
                newOp->inInput[0] = inputs.at(i);
                inputs.at(i)->toOperations.push_back(newOp);
                assigned = true;
                break;
            }
        }
        if(!assigned){
            for(int i = 0; i < (signed)this->wires.size(); i++){
                if(var.compare(wires.at(i)->getName()) == 0){
                    newOp->inWire[0] = wires.at(i);
                    wires.at(i)->toOperations.push_back(newOp);
                    assigned = true;
                    break;
                }
            }
        }

        /* No assignment was defined */
        if(!assigned){
            cout << "ERROR: Missing input or wire varible definition for: " << var << endl;
            return false;
        }

        /* Remove second variable in operation line */
        line.erase(line.begin());
        
        if(!line.size()){
            if(newOp->getOperation() == Operation::REG){
                newOp->inInput[1] = inputs.at(0);
                newOp->inInput[2] = inputs.at(1);
                newOp->calcWidth();
                newOp->setSign();
                this->operations.push_back(newOp);
                return true;
            }
        }

        /* ADD or INC */
        var = line.front();
        if(var.compare("+") == 0){
            line.erase(line.begin());
            var = line.front();
            if(name.compare("1") == 0){
                newOp->setOperation(Operation::INC);
                newOp->setOpID(getID(Operation::INC));
                newOp->calcWidth();
                newOp->setSign();
                this->operations.push_back(newOp);
                if(regOp != NULL){
                    regOp->calcWidth();
                    regOp->setSign();
                    this->operations.push_back(regOp);
                }
                return true;
            }
            newOp->setOperation(Operation::ADD);
            newOp->setOpID(getID(Operation::ADD));
        } /* SUB or DEC */
        else if(var.compare("-") == 0){
            line.erase(line.begin());
            var = line.front();
            if(name.compare("1") == 0){
                newOp->setOperation(Operation::DEC);
                newOp->setOpID(getID(Operation::DEC));
                newOp->calcWidth();
                newOp->setSign();
                this->operations.push_back(newOp);
                if(regOp != NULL){
                    regOp->calcWidth();
                    regOp->setSign();
                    this->operations.push_back(regOp);
                }
                return true;
            }
            newOp->setOperation(Operation::SUB);
            newOp->setOpID(getID(Operation::SUB));
        } /* MUL */
        else if(var.compare("*") == 0){
            newOp->setOperation(Operation::MUL);
            newOp->setOpID(getID(Operation::MUL));
        } /* COMP_GT */
        else if(var.compare(">") == 0){
            newOp->setOperation(Operation::COMP_GT);
            newOp->setOpID(getID(Operation::COMP_GT));
        } /* COMP_LT */
        else if(var.compare("<") == 0){
            newOp->setOperation(Operation::COMP_LT);
            newOp->setOpID(getID(Operation::COMP_LT));
        } /* COMP_EQ */
        else if(var.compare("==") == 0){
            newOp->setOperation(Operation::COMP_EQ);
            newOp->setOpID(getID(Operation::COMP_EQ));
        } /* MUX2x1 */
        else if(var.compare("?") == 0){
            newOp->setOperation(Operation::MUX2x1);
            newOp->setOpID(getID(Operation::MUX2x1));
        } /* SHR */
        else if(var.compare(">>") == 0){
            newOp->setOperation(Operation::SHR);
            newOp->setOpID(getID(Operation::SHR));
        } /* SHL */
        else if(var.compare("<<") == 0){
            newOp->setOperation(Operation::SHL);
            newOp->setOpID(getID(Operation::SHL));
        } /* DIV */
        else if(var.compare("/") == 0){
            newOp->setOperation(Operation::DIV);
            newOp->setOpID(getID(Operation::DIV));
        } /* MOD */
        else if(var.compare("%") == 0){
            newOp->setOperation(Operation::MOD);
            newOp->setOpID(getID(Operation::MOD));
        } /* Invalid Line/Operator */
        else{
            
            cout << "ERROR: Invalid type -> " << var << endl;
            return false;

        }

        /* Remove operator in operation line if and only if...
		   operator hasn't been removed already*/
		if (!((newOp->getOperation() == Operation::ADD) 
			|| (newOp->getOperation() == Operation::INC)
			|| (newOp->getOperation() == Operation::SUB)
			|| (newOp->getOperation() == Operation::DEC))) {
			line.erase(line.begin());
		};

        /* Assign out Input or Wire to operation */
        assigned = false;
        var = line.front();
        for(int i = 0; i < (signed)this->inputs.size(); i++){
            if(var.compare(inputs.at(i)->getName()) == 0){
                newOp->inInput[1] = inputs.at(i);
                inputs.at(i)->toOperations.push_back(newOp);
                assigned = true;
                break;
            }
        }
        if(!assigned){
            for(int i = 0; i < (signed)this->wires.size(); i++){
                if(var.compare(wires.at(i)->getName()) == 0){
                    newOp->inWire[1] = wires.at(i);
                    wires.at(i)->toOperations.push_back(newOp);
                    assigned = true;
                    break;
                }
            }
        }

        /* No assignment was defined */
        if(!assigned){
            cout << "ERROR: Missing input or wire varible definition for: " << var << endl;
            return false;
        }
        
        if(newOp->getOperation() == Operation::MUX2x1){

            line.erase(line.begin());
            line.erase(line.begin());

            /* Assign out Input or Wire to operation */
            assigned = false;
            var = line.front();
            for(int i = 0; i < (signed)this->inputs.size(); i++){
                if(var.compare(inputs.at(i)->getName()) == 0){
                    newOp->inInput[2] = inputs.at(i);
                    inputs.at(i)->toOperations.push_back(newOp);
                    assigned = true;
                    break;
                }
            }
            if(!assigned){
                for(int i = 0; i < (signed)this->wires.size(); i++){
                    if(var.compare(wires.at(i)->getName()) == 0){
                        newOp->inWire[2] = wires.at(i);
                        wires.at(i)->toOperations.push_back(newOp);
                        assigned = true;
                        break;
                    }
                }
            }

            /* No assignment was defined */
            if(!assigned){
                cout << "ERROR: Missing input or wire varible definition for: " << var << endl;
                return false;
            }
        }
        
        /* Adds operation to module */
        newOp->calcWidth();
        newOp->setSign();
        this->operations.push_back(newOp);
        if(regOp != NULL){
            regOp->calcWidth();
            regOp->setSign();
            this->operations.push_back(regOp);
        }
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
    int id = 1;
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
    vector<Wire *> wireQueue;
    vector<Operation *> operationQueue;
    vector<double> wireDistance;
    vector<double> operationDist;
    Wire* currWire;
    Output* currOut;
    Operation* currOp;
    unsigned long queueSize;
    
    // Search through all operations to initialize queue of vertices with indegree of 0
    for (int i = 0; i < operations.size(); i++) {
        // Search through all available input/wires of the specific operation
        for (int j = 0; j < 3; j++) {
            // Check if input does not exists
            if (operations.at(i)->inInput[j] == NULL) {
                cout << "Failed searching for initial 0 indegree operations (input does not exist when needed)" << endl;
                return -1;
            }
            // Check if wire exists
            if (operations.at(i)->inWire[j] != NULL) {
                cout << "Failed searching for initial 0 indegree operations (wire exists when should be input only operation)" << endl;
            }
        }
        // After searching through, should satisfy if operation has only inputs and no wires, then add operation to 0 indegree operations queue
        operationQueue.push_back(operations.at(i));
    }
    
    queueSize = operationQueue.size();
    while (queueSize != 0) {
        currOp = operationQueue.front();
        // If updated variable is a wire, begin looking at its next operations
        if (currOp->wireNext != NULL) {
            currWire = currOp->wireNext;
            for (int i = 0; i < currWire->toOperations.size(); i++) {
                // If when searching, the current operation is found, skip onto the next iteration
                if (currOp == currWire->toOperations.at(i)) {
                    continue;
                }
                else {
                    
                }
            }
        }
        else if (currOp->outNext != NULL) {
            currOut = currOp->outNext;
            // At end of critical path, update final distance
        }
        else {
            cout << "Something went wrong when looking at queue (no wire or output result for operaation)" << endl;
            return -1;
        }
    }
    
    return 0;
}
