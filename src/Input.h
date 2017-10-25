//
//  Input.h
//  dpgen
//
//  Created by Andrew Camps on 10/22/17.
//

#ifndef Input_h
#define Input_h

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <cstring>
#include <cctype>

#include "Operation.h"

using namespace std;

class Operation;

class Input {
private:
    bool usigned;
    int dataWidth;
    string name;
public:
    Input(string name, int width, bool usigned);
    string getName() { return name; }
    int getWidth() { return dataWidth; }
    bool isUnsigned() { return usigned; }
    string toString();
    vector<Operation *> toOperations;
};

#endif /* Input_h */
