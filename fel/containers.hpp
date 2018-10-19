#pragma once

#include <fel/types.hpp>

namespace FEngine {

    class Series {
        public:
            using const_iterator = map<string, double>::const_iterator;
            Series(const vector<string>& keys, const vector<double>& vals) {
                for (size_t i = 0; i < keys.size(); ++i)
                    maps_[keys[i]] = vals[i];
                keys_ = keys;
                vals_ = vals;
            }

            Series(const map<string, double>& vals) {
                maps_ = vals;
                for (map<string, double>::const_iterator it=maps_.begin();
                        it != maps_.end(); ++it) {
                    keys_.push_back(it->first);
                    vals_.push_back(it->second);
                }
            }

            Series(string key, double val) {
                maps_[key] = val;
                keys_.push_back(key);
                vals_.push_back(val);
            }

            double& operator[](const string& key) { return maps_[key];}
            double at(const string& key) const { return maps_.at(key);}
            size_t size() const { return maps_.size();}
            const_iterator find(const string& key) const { return maps_.find(key);}
            const_iterator begin() const { return maps_.begin();}
            const_iterator end() const { return maps_.end();}
            const vector<string>& keys() const { return keys_;}
            const vector<double>& vals() const { return vals_;}

        private:
            map<string, double> maps_;
            vector<string> keys_;
            vector<double> vals_;
    };

    Series operator+(const Series& lhs, const Series& rhs);

    Series operator-(const Series& lhs, const Series& rhs);

    Series operator*(const Series& lhs, const Series& rhs);

    Series operator/(const Series& lhs, const Series& rhs);

    Series operator-(const Series& rhs);

    Series rank(const Series& rhs);
}