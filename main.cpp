#include <string>
#include <iostream>

#include "entries.h"

using namespace std;


fs::directory_entry getSource( const string& sourceDirPath ) {

    try {
        auto entry = fs::directory_entry(sourceDirPath);

        if (!entry.exists()) {
            throw exception();
        }

        return entry;
    }
    catch (exception&){
        throw logic_error("can't find a source");
    }
}

void checkResultDir(const string& resultDirPath) {
  
    try {
        auto iterator = fs::directory_iterator(resultDirPath); 
    }
    catch(exception&) {
        fs::create_directories(resultDirPath);
    }
}

void generate( const string& sourcePath = "./source",
                const string& resultPath = "./result" ) {

    checkResultDir(resultPath);
    auto sourceEntry = getSource(sourcePath);

    handleEntry(sourceEntry,resultPath);
}

int main() {

    generate("./function.txt");

    return 0;
}