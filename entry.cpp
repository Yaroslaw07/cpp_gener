#include "entry.h"
#include "additional.h"


// to refactor
string getVariable( stringstream& ss ) {

    string returnType;
    string funcName;

    ss >> returnType;
    ss >> funcName;

    return  returnType + " " + funcName;
}

// to refactor
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


void handleEntry( const fs::directory_entry& sourceEntry,
                  const string& resultDirPath ) {

    if (sourceEntry.is_directory()) {
        for (const auto& entry: fs::directory_iterator(sourceEntry.path()))
            handleEntry(entry,resultDirPath);

        return;
    }

    string path = sourceEntry.path();

    if (!checkFileFormat(path,"txt")) return;

    string fileName = getFileName(path);

    ifstream sourceFile(path);
    ofstream resultHeader = getFile(path,fileName,"h"); 
    ofstream resultCpp = getFile(path,fileName,"cpp");

    while(getline(sourceFile,fileName)) {
        fileName = getFuncDecl(fileName);
        resultCpp << fileName << " {\n\n}\n\n";
        resultHeader << fileName << ";" << endl;
    }

    sourceFile.close();
    resultCpp.close();
    resultHeader.close();
}