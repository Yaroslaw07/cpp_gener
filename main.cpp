#include <fstream>
#include <string>
#include <sstream>

using namespace std;

string generateTop(stringstream& funcDecl){
    string returnType;
    string funcName;
    funcDecl >> returnType;
    funcDecl >> funcName;

    return  returnType + " " + funcName + "( void )";
}

int main() {

    ifstream fileSource("Function.txt");
    ofstream resultCpp("./result/file.cpp"),resultH("./result/file.h");

    string temp;
    stringstream ss;

    while(getline(fileSource,temp)) {
        ss.str(temp);
        temp = generateTop(ss);

        resultH << temp << ";" << endl;
        resultCpp << temp << " {\n\n}\n\n"; 

        ss.clear();
    }

    resultCpp.close();
    resultH.close();

}