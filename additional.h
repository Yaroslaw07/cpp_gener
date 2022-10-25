#pragma once

#include <string>
#include <vector>
#include <numeric>
#include <iostream>
#include "variable.h"

using namespace std;


const vector<string> goodTypes = {"void","int","string","bool","char"};

bool isGoodType( const string& type );

bool checkFileFormat( const string& path,const string& expectedFormat ); 

string getFileName( const string& path );

string join(const vector<Variable>& params, const string& delim);
