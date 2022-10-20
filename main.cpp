#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <numeric>

using namespace std;

string getTypeAndName(stringstream& ss){

    string returnType;
    string funcName;

    ss >> returnType;
    ss >> funcName;

    return  returnType + " " + funcName;
}

string getFuncDecl(stringstream& funcDecl) {

    string res;

    res = getTypeAndName(funcDecl);

    vector<string> args;

    while (!funcDecl.eof()) {
        args.push_back(getTypeAndName(funcDecl));
    }

    res += "(";

    if (args.empty()){
        res += " void ";
    } else {
        res += accumulate(args.begin() + 1, args.end(), args[0], 
                            [](std::string x, string y){
                                return x + ',' + y;
                            }
                        );
    }

    res += ")";


    return res;
} 


int main() {

    // open files
    ifstream fileSource("Function.txt");
    ofstream resultCpp("./result/file.cpp"),resultH("./result/file.h");

    string temp;
    stringstream ss;

    // loop to handle every line of file
    while(getline(fileSource,temp)) {

        
        ss.str(temp);

        // handle line
        temp = getFuncDecl(ss);

        // write results to files
        resultH << temp << ";" << endl;
        resultCpp << temp << " {\n\n}\n\n"; 

        ss.clear();
    }

    resultCpp.close();
    resultH.close();

}