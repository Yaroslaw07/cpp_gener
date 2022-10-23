#pragma once
#include "entry.h"


fs::directory_entry getSource( const string& sourceDirPath ) {

    auto entry = fs::directory_entry(sourceDirPath);

    if (!entry.exists()) {
        throw logic_error("source doesn't exist");
    }

    return entry;
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
