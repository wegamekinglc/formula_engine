#include<algorithm>
#include<fel/types.hpp>

namespace FEngine {
    Depends mergeDepends(const Depends& lhs, const Depends& rhs) {
        Depends res = lhs;
        for(Depends::const_iterator it = rhs.begin(); it != rhs.end(); ++it) {
            string key = it->first;
            vector<DateTime> val = it->second;
            if(lhs.find(key) == lhs.end())
                res[key] = val;
            else {
                vector<DateTime>& t = res[key];
                t.insert(t.end(), val.begin(), val.end());
                std::sort(t.begin(), t.end() );
                t.erase(std::unique(t.begin(), t.end() ), t.end() );
            }
        }
        return res;
    }
}