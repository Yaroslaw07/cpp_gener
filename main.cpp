#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <numeric>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

string join( const vector<string>& v, const string& delim ) {

    return accumulate( v.begin() + 1, v.end(), v[0], 
                        [&delim](std::string x, string y){
                            return x + delim + y;
                        }
                    );
}

bool checkFileFormat(const string& path,const string& expectedFormat) {

    size_t found= path.find_last_of("."); 

    if ( found == string::npos ||
         path.substr(found+1, path.size() - found) != expectedFormat) {

        return false; 
    }

    return true;
}

string getVariable( stringstream& ss ) {

    string returnType;
    string funcName;

    ss >> returnType;
    ss >> funcName;

    return  returnType + " " + funcName;
}

string getFuncDecl( const string& funcDecl ) {

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

fs::directory_iterator handleSourceDir( const string& sourceDirPath ) {

    try {
        return fs::directory_iterator(sourceDirPath);
    }
    catch (exception&){
        throw logic_error("can't find a source folder");
    }
}

void handleResultDir(const string& resultDirPath = "./result") {
  
    try {
        auto iterator = fs::directory_iterator(resultDirPath);
    }
    catch(exception&) {
        fs::create_directories(resultDirPath);
    }
}

fs::directory_iterator handleDirPaths( const string& sourceDirPath = "./source",
                                       const string& resultDirPath = "./result" ) {
    
    auto iterator = handleSourceDir(sourceDirPath);
    handleResultDir(resultDirPath);
    return iterator;

}



string getFileName(const string& path) {

    size_t found = path.find_last_of("/")+1;
    return path.substr(found,path.find_last_of(".") - found);
}

void handleEntry( const fs::directory_entry& sourceEntry,
                  const string& resultDirPath ) {

    if (sourceEntry.is_directory()) return;

    string path = sourceEntry.path();

    if (!checkFileFormat(path,"txt")) return;

    ifstream sourceFile(path);

    string fileName = getFileName(path);
    ofstream resultHeader(resultDirPath + "/" + fileName + ".h");
    ofstream resultCpp(resultDirPath + "/" + fileName + ".cpp");

    while(getline(sourceFile,fileName)) {
        fileName = getFuncDecl(fileName);
        resultCpp << fileName << " {\n\n}\n\n";
        resultHeader << fileName << ";" << endl;
    }

    sourceFile.close();
    resultCpp.close();
    resultHeader.close();

}

void generateFiles( const string& sourceDirPath = "./source",
                    const string& resultDirPath = "./result" ) {
    
    //check if directories exist
    fs::directory_iterator iterator = handleDirPaths();

    //handle every file in 
    for (const auto& entry : iterator ) {
        handleEntry(entry,resultDirPath);
    }
}

int main() {

    generateFiles();

    return 0;
}