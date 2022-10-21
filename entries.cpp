#include "entries.h"



string join( const vector<string>& v, const string& delim ) {

    return accumulate( v.begin() + 1, v.end(), v[0], 
                        [&delim](std::string x, string y){
                            return x + delim + y;
                        }
                    );
}

string getFileName(const string& path) {

    size_t found = path.find_last_of("/")+1;
    return path.substr(found,path.find_last_of(".") - found);
}

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


bool checkFileFormat( const string& path,const string& expectedFormat ) {

    size_t found= path.find_last_of("."); 

    if ( found == string::npos ||
         path.substr(found+1, path.size() - found) != expectedFormat) {

        return false; 
    }

    return true;
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