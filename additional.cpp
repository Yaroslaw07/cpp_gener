#include "additional.h"

string join( const vector<string>& v, const string& delim ) {

    return accumulate( v.begin() + 1, v.end(), v[0], 
                        [&delim](std::string x, string y){
                            return x + delim + y;
                        }
                    );
}

