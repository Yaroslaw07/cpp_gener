#include "file_work.h"
#include "additional.h"
#include "variable.h"

using namespace std;

ofstream getFileStream( const string& DirPath,const string& fileName,const string& fileFormat ) {
    return ofstream(DirPath + "/" + fileName + "." + fileFormat);
}

bool checkFileFormat( const string& path,const string& expectedFormat ) {

    size_t found= path.find_last_of("."); 

    if ( found == string::npos ||
         path.substr(found+1, path.size() - found) != expectedFormat) {

        return false; 
    }

    return true;
}

string getFileName( const string& path ) {

    size_t found = path.find_last_of("/")+1;
    return path.substr(found,path.find_last_of(".") - found);
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

    return type + " res;\n\nreturn res;";
}

void handlePaths( const string& sourcePath,
                  const string& resultDirPath ) {
    
    string temp = getFileName(sourcePath);

    ifstream sourceFile(sourcePath);
    ofstream resultHeader = getFileStream(resultDirPath,temp,"h"); 
    ofstream resultCpp = getFileStream(resultDirPath,temp,"cpp");
    vector<Variable> buffer;

    while(getline(sourceFile,temp)) {

        buffer.clear();

        try {
            handleFuncDecl(buffer,temp);
        } catch(logic_error& le) {
            cerr << le.what() << " in " << sourcePath << endl;
        }

        if (buffer.size() == 0) continue;

        temp = *(buffer.begin());
        temp += " (";

        if (buffer.size() >= 2) {
            temp += join({buffer.cbegin() + 1,buffer.cend()},",");
        }

        resultCpp << temp << ") {\n"<<getFuncBody((*buffer.begin()).getType())<<"\n}\n\n";
        resultHeader << temp << ");" << endl;
    }

    sourceFile.close();
    resultCpp.close();
    resultHeader.close();

}  