#include "file_work.h"
#include "additional.h"
#include "variable.h"

using namespace std;

ofstream getFileStream( const string& DirPath,const string& fileName,const string& fileFormat ) {
    return ofstream(DirPath + "/" + fileName + "." + fileFormat);
}

Variable getVariable( stringstream& ss ) {

    string type;
    string name;

    ss >> type;
    if (!isGoodType(type)) {
        throw logic_error("Wrong type |" + type +  "| of variable");
    }

    ss >> name;
    if (name.empty() && type != "void") {
        throw logic_error("Empty name");
    } 

    return Variable(type,name);
}

void handleFuncDecl(vector<Variable>& buff,const string& funcDecl ) {

    stringstream ss;
    ss.str(funcDecl);

    while (!ss.eof()) {
        try{
            buff.push_back(getVariable(ss));
        }
        catch (logic_error& le) {
            throw logic_error( string(le.what()) + " in string \"" + funcDecl + "\"" );
        }
    }
}



string getFuncBody(const string& type) {
    if (type == "void") {
        return "";
    }

    return "\t" + type + " res;\n\n\treturn res;";
}

void handleFileLine(ofstream& header,ofstream& cpp,const string& line) {
    vector<Variable> buffer;
    string res;

    handleFuncDecl(buffer,line);
    
    if (buffer.size() == 0) return;
    
    res = *(buffer.begin());
    res += " (";
    
    if (buffer.size() >= 2) {
        res += join({buffer.cbegin() + 1,buffer.cend()},",");
    }

    cpp << res << ") {\n"<<getFuncBody((*buffer.begin()).getType())<<"\n}\n\n";
    header << res << ");" << endl;
}

void handlePaths( const string& sourcePath,
                  const string& resultDirPath ) {
    
    string temp = getFileName(sourcePath);

    ifstream sourceFile(sourcePath);
    ofstream resultHeader = getFileStream(resultDirPath,temp,"h"); 
    ofstream resultCpp = getFileStream(resultDirPath,temp,"cpp");

    while(getline(sourceFile,temp)) {

        try{
            handleFileLine(resultHeader,resultCpp,temp);
        }
        catch(logic_error& le) {
             cerr << le.what() << " in " << sourcePath << endl;
        }
    }

    sourceFile.close();
    resultCpp.close();
    resultHeader.close();

}  