#include<fel/types.hpp>

namespace FEngine {
    Depends mergeDepends(const Depends& lhs, const Depends& rhs) {
        // The implementation is simple and not correct
        Depends res = lhs;
        for(Depends::const_iterator it = rhs.begin(); it != rhs.end(); ++it) {
            string key = it->first;
            vector<DateTime> val = it->second;
            if(lhs.find(key) == lhs.end())
                res[key] = val;
        }
        return res;
    }
}