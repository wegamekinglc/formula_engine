#pragma once

#include <fel/types.hpp>

namespace FEngine {

    class Series {
        public:
            using const_iterator = map<string, double>::const_iterator;
            friend bool operator==(const Series& lhs, const Series& rhs);
            Series() = default;
            Series(const vector<string>& keys, const vector<double>& values) {
                for (size_t i = 0; i < keys.size(); ++i)
                    maps_[keys[i]] = values[i];
                keys_ = keys;
                values_ = values;
            }

            explicit Series(const map<string, double>& values) {
                maps_ = values;
                for(const auto& it: values) {
                    keys_.push_back(it.first);
                    values_.push_back(it.second);
                }
            }

            Series(const string& key, double val) {
                maps_[key] = val;
                keys_.push_back(key);
                values_.push_back(val);
            }

            double& operator[](const string& key) { return maps_[key];}
            double at(const string& key) const { return maps_.at(key);}
            size_t size() const { return maps_.size();}
            const_iterator find(const string& key) const { return maps_.find(key);}
            const_iterator begin() const { return maps_.begin();}
            const_iterator end() const { return maps_.end();}
            const vector<string>& keys() const { return keys_;}
            const vector<double>& values() const { return values_;}


        private:
            map<string, double> maps_;
            vector<string> keys_;
            vector<double> values_;
    };

    bool operator==(const Series& lhs, const Series& rhs);

    Series operator+(const Series& lhs, const Series& rhs);

    Series operator-(const Series& lhs, const Series& rhs);

    Series operator*(const Series& lhs, const Series& rhs);

    Series operator/(const Series& lhs, const Series& rhs);
    Series operator/(const Series& lhs, double rhs);

    Series operator-(const Series& rhs);
    
    double dot(const Series& lhs, const Series& rhs);
    double sum(const Series& rhs);

    Series abs(const Series& rhs);
    Series rank(const Series& rhs);
}