#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <iterator>

using namespace std;

struct Variable{
    protected:
    string type;
    string name;
    public:
    Variable(const string& type,const string& name):type(type),name(name){};
    string getType() {return type;}
    operator string() const;
    Variable& operator=(const Variable& var);
    friend ostream& operator<<(ostream& os,const Variable& var);
};


