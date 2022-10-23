#pragma once

#include <fstream>
#include <string>

using namespace std;

ofstream getFile(const string& DirPath = ".",const string& fileName = "default",const string& fileFormat = "txt" );

bool checkFileFormat( const string& path,const string& expectedFormat );

string getFileName(const string& path);