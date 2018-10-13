#pragma once

#include <fel/types.hpp>

namespace FEngine {
    using DataPack = map<string, map<string, map<DateTime, double>>>;

    class Series {
        public:
            Series(const vector<string>& keys, const vector<double>& vals) {
                for (size_t i = 0; i < keys.size(); ++i)
                    vals_[keys[i]] = vals[i];
            }

            Series(string key, double val) {
                vals_[key] = val;
            }

        private:
            map<string, double> vals_;
    };
}