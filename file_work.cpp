#include "file_work.h"

ofstream getFile(const string& DirPath,const string& fileName,const string& fileFormat) {
    return ofstream(DirPath + "/" + fileName + "." + fileFormat);
}

bool checkFileFormat( const string& path,const string& expectedFormat ) {

    size_t found= path.find_last_of("."); 

    if ( found == string::npos ||
         path.substr(found+1, path.size() - found) != expectedFormat) {

        return false; 
    }

    return true;
}

string getFileName(const string& path) {

    size_t found = path.find_last_of("/")+1;
    return path.substr(found,path.find_last_of(".") - found);
}
