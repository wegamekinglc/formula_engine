#include<algorithm>
#include<fel/types.hpp>

namespace FEngine {
    Depends mergeDepends(const Depends& lhs, const Depends& rhs) {
        Depends res = lhs;
        for(const auto& pair: rhs) {
            String_ key = pair.first;
            Vector_<DateTime> val = pair.second;
            if(lhs.find(key) == lhs.end())
                res[key] = val;
            else {
                Vector_<DateTime>& t = res[key];
                t.insert(t.end(), val.begin(), val.end());
                std::sort(t.begin(), t.end() );
                t.erase(std::unique(t.begin(), t.end() ), t.end() );
            }
        }
        return res;
    }
}