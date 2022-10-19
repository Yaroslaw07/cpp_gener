#include <fstream>
#include <string>

using namespace std;

string generateTop(string funcName){
    return  "void " + funcName + "( void )";
}

int main() {

    ifstream fileSource("config.txt");
    ofstream resultCpp("./result/file.cpp"),resultH("./result/file.h");


    string temp;

    while(getline(fileSource,temp)) {
        temp = generateTop(temp);

        resultH << temp << ";" << endl;
        resultCpp << temp << " {\n\n}\n\n"; 
    }

    resultCpp.close();
    resultH.close();

}