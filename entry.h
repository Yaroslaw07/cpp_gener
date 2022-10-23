#pragma once

#include "file_work.h"

#include <filesystem>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>




namespace fs = std::filesystem;
using namespace std;

string getVariable( stringstream& ss );

string getFuncDecl();

string getEntryName(const string& path);

void handleEntry( const fs::directory_entry& sourceEntry,
                  const string& resultDirPath );