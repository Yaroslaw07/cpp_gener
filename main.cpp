#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <numeric>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

string getVariable( stringstream& ss ) {

    string returnType;
    string funcName;

    ss >> returnType;
    ss >> funcName;

    return  returnType + " " + funcName;
}

string join( const vector<string>& v, const string& delim ) {

    return accumulate( v.begin() + 1, v.end(), v[0], 
                        [&delim](std::string x, string y){
                            return x + delim + y;
                        }
                    );
}

string getFuncDecl(const string& funcDecl) {

    stringstream ss;
    ss.str(funcDecl);

    string res;

    res = getVariable(ss);

    vector<string> args;

    while (!ss.eof()) {
        args.push_back(getVariable(ss));
    }

    res += "(";

    if (args.empty()){
        res += " void ";
    } else {
        res += join(args,", ");
    }

    res += ")";

    return res;
} 

void generateFiles( const string& sourcePathDir = "./source",
                    const string& resultPathDir = "./result") {
    
    //check if directories exist
    fs::directory_iterator iterator;

    {
        try {
            iterator = fs::directory_iterator(resultPathDir);
        } 
        catch(exception& e) {
            fs::create_directory(resultPathDir);
        }


        try {
            iterator = fs::directory_iterator(sourcePathDir);
        }
        catch(exception& e) {
            cerr << "Can't find source file";
            return;
        }
    }

    ifstream sourceFile;

    ofstream resultHeader, resultCpp;
    string temp;

    stringstream ss;

    //handle every file in 
    for (const auto& entry : iterator ) {

        if (entry.is_directory()) continue;

        temp = entry.path();
        size_t found = temp.find_last_of(".");

        if (found == string::npos ||  temp.substr(found+1,3 ) != "txt") continue;

        //cout << entry.path() << "        |"<<temp.substr(found+1,3)<<"|";

        found = temp.find_last_of("/")+1;
        temp = temp.substr(found,temp.find_last_of(".") - found);

        cout << temp << endl;

        sourceFile.open(entry.path());
        resultHeader.open(resultPathDir + "/" + temp + ".h");
        resultCpp.open(resultPathDir + "/" + temp + ".cpp");

        while(getline(sourceFile,temp)) {

            temp = getFuncDecl(temp);

            resultCpp << temp << " {\n\n}\n\n";
            resultHeader << temp << ";" << endl;

        }

        resultCpp.close();
        resultHeader.close();


    }
}

int main() {

    generateFiles();    

    // open files
    /*ifstream fileSource("Function.txt");
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
    resultH.close();*/

}