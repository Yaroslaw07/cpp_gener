#pragma once

#include <filesystem>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <numeric>


namespace fs = std::filesystem;
using namespace std;

string join( const vector<string>& v, const string& delim );

string getVariable( stringstream& ss );

string getFuncDecl();

bool checkFileFormat( const string& path,const string& expectedFormat );

fs::directory_entry handleResultDir(const string& resultDirPath = "./result");

fs::directory_entry handleSource( const string& sourceDirPath );

void handleEntry( const fs::directory_entry& sourceEntry,
                  const string& resultDirPath );