#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>


using namespace std;

ofstream getFile(const string& DirPath = ".",const string& fileName = "default",const string& fileFormat = "txt" );

bool checkFileFormat( const string& path,const string& expectedFormat );

string getFileName( const string& path );

void handlePaths( const string& sourcePath, const string& resultDirPath );