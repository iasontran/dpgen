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
#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

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
};

#endif /* Input_h */
