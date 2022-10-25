#include "additional.h"
#include <algorithm>


bool isGoodType( string type ) {
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


