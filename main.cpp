#include <fstream>
#include <string>

using namespace std;

string generateTop(string funcName){
    return  "void " + funcName + "( void )";
}

int main() {

    string arr[4] = {"open","close","read","write"};
    

    ofstream resultCpp("./result/file.cpp"),resultH("./result/file.h");


    string temp;
    for ( int i = 0; i < 4; i++) {
        temp = generateTop(arr[i]);
        resultH << temp << ";" << endl;
        resultCpp << temp << " {\n\n}\n\n"; 
    }

    resultCpp.close();
    resultH.close();

}