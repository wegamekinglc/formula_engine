#pragma once

#include <fel/types.hpp>

namespace FEngine {

    class Series {
        public:
            using const_iterator = Map_<String_, double>::const_iterator;
            friend bool operator==(const Series& lhs, const Series& rhs);
            Series() = default;
            Series(const Vector_<String_>& keys, const Vector_<double>& values) {
                for (size_t i = 0; i < keys.size(); ++i)
                    maps_[keys[i]] = values[i];
                keys_ = keys;
                values_ = values;
            }

            explicit Series(const Map_<String_, double>& values) {
                maps_ = values;
                for(const auto& it: values) {
                    keys_.push_back(it.first);
                    values_.push_back(it.second);
                }
            }

            Series(const String_& key, double val) {
                maps_[key] = val;
                keys_.push_back(key);
                values_.push_back(val);
            }

            double& operator[](const String_& key) { return maps_[key];}
            double at(const String_& key) const { return maps_.at(key);}
            size_t size() const { return maps_.size();}
            const_iterator find(const String_& key) const { return maps_.find(key);}
            const_iterator begin() const { return maps_.begin();}
            const_iterator end() const { return maps_.end();}
            const Vector_<String_>& keys() const { return keys_;}
            const Vector_<double>& values() const { return values_;}


        private:
            Map_<String_, double> maps_;
            Vector_<String_> keys_;
            Vector_<double> values_;
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