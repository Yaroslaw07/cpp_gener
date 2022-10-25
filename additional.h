#pragma once

#include <string>
#include <vector>
#include <numeric>
#include <iostream>
#include "variable.h"

using namespace std;


const vector<string> goodTypes = {"void","int","string","bool","char"};

bool isGoodType( string type );

string join(const vector<Variable>& params, const string& delim);