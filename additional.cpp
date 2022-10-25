#include "additional.h"
#include <algorithm>


bool isGoodType( const string& type ) {
    return count(goodTypes.begin(),goodTypes.end(),type);
}


string join(const vector<Variable>& params, const string& delim) {
    if (params.empty()) return "";

    string res = *params.begin();

    if (params.begin() == params.end()) return res;

    for (auto i = params.begin() + 1;i != params.end();++i) {
        res += delim + string(*i);
    }

    return res;
}

string getFileName( const string& path ){

    size_t found = path.find_last_of("/")+1;
    return path.substr(found,path.find_last_of(".") - found);
}

bool checkFileFormat( const string& path,const string& expectedFormat ){

    size_t found= path.find_last_of("."); 

    if ( found == string::npos ||
         path.substr(found+1, path.size() - found) != expectedFormat) {

        return false; 
    }

    return true;
}