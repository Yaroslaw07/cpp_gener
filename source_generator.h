#pragma once

#include <filesystem>
#include <iostream>

#include "file_work.h"

namespace fs = std::filesystem;

void handleEntry( const fs::directory_entry& sourceEntry,
                  const fs::directory_entry& resultDirEntry );

fs::directory_entry getSource( const string& sourcePath ) {

    auto entry = fs::directory_entry(sourcePath);

    if (!entry.exists()) {
        throw logic_error("source doesn't exist");
    }

    return entry;
}

fs::directory_entry getResultDir(const string& resultDirPath) {
  
    try {
        auto iterator = fs::directory_iterator(resultDirPath); 
    }
    catch(exception&) {
        fs::create_directories(resultDirPath);
    }
    return fs::directory_entry(resultDirPath);
}

void generate( const string& sourcePath = "./source",
                const string& resultDirPath = "./result" ) {

    auto resultEntry = getResultDir(resultDirPath);
    auto sourceEntry = getSource(sourcePath);

    handleEntry(sourceEntry,resultEntry);
}

void generate( const vector<string> sourcePaths,
                const string& resultDirPath = "./result" ) {

    auto resultEntry = getResultDir(resultDirPath);

    for ( const string& source:sourcePaths ) {

        try {  
        auto sourceEntry = getSource(source);
        handleEntry(sourceEntry,resultEntry);
        } catch (logic_error& l) {
            cerr << source << " " << l.what();
            continue;
        }
        
    }
}

void handleEntry( const fs::directory_entry& sourceEntry,
                  const fs::directory_entry& resultDirEntry ) {

    if (sourceEntry.is_directory()) {
        for (const auto& entry: fs::directory_iterator(sourceEntry.path()))
            handleEntry(entry,resultDirEntry);

        return;
    }

    string sourcePath = string(sourceEntry.path());

    if (!checkFileFormat(sourcePath,"txt")) return;

    handlePaths(sourcePath,resultDirEntry.path());
}
