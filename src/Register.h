/*************/
/*
 * File: Register.h
 * Author: Jason Tran, Andrew Camps
 * NetID: ichikasuto, andrewcamps
 * Date: October 20, 2017
 *
 * Description:
 */

#ifndef Register_h
#define Register_h

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <cctype>

using namespace std;

class Register {
private:
    bool usigned;
    int dataWidth;
    string name;
public:
    Register(string name, int width, bool usigned);
    string getName() { return name; }
    int getWidth() { return dataWidth; }
    bool isUnsigned() { return usigned; }
    string toString();

};

#endif
