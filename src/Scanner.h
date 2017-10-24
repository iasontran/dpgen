/*************/
/*
 * File: Scanner.h
 * Author: Jason Tran, Andrew Camps
 * NetID: ichikasuto, andrewcamps
 * Date: October 20, 2017
 *
 * Description:
 */

#ifndef Scanner_h
#define Scanner_h

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <cctype>
#include <string>
#include <sstream>

#include "Output.h"
#include "Input.h"
#include "Register.h"
#include "Wire.h"
#include "Operation.h"

using namespace std;

class Module;

class Scanner {
private:
    string file;
    Module *module;
    enum Type { INPUT, OUTPUT, WIRE, REGISTER, OPERATION };
    bool parseLine(string line, Type type);
public:
    Scanner(string file, Module *module);
    bool readFile();
    vector<string> parseVars(string line);
};

#endif
