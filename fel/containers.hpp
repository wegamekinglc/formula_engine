#pragma once

#include <fel/types.hpp>

namespace FEngine {
    using DataPack = map<string, map<string, map<DateTime, double>>>;

    class Series {
        public:
            using const_iterator = map<string, double>::const_iterator;
            Series(const vector<string>& keys, const vector<double>& vals) {
                for (size_t i = 0; i < keys.size(); ++i)
                    vals_[keys[i]] = vals[i];
            }

            Series(const map<string, double>& vals) {
                vals_ = vals;
            }

            Series(string key, double val) {
                vals_[key] = val;
            }

            double& operator[](const string& key) { return vals_[key];}
            double at(const string& key) const { return vals_.at(key);}
            size_t size() const { return vals_.size();}
            const_iterator find(const string& key) const { return vals_.find(key);}
            const_iterator begin() const { return vals_.begin();}
            const_iterator end() const { return vals_.end();}

        private:
            map<string, double> vals_;
    };

    Series operator+(const Series& lhs, const Series& rhs) {
        map<string, double> res;

        for(Series::const_iterator it = lhs.begin(); it != lhs.end(); ++it) {
            string key = it->first;
            double val = it->second;
            if(rhs.find(key) != rhs.end())
                val += rhs.at(key);
            res[key] = val;
        }

        for(Series::const_iterator it = rhs.begin(); it != rhs.end(); ++it) {
            string key = it->first;
            if(lhs.find(key) == lhs.end())
                res[key] = it->second;
        }
        
        return Series(res);
    }

    Series operator-(const Series& lhs, const Series& rhs) {
        map<string, double> res;

        for(Series::const_iterator it = lhs.begin(); it != lhs.end(); ++it) {
            string key = it->first;
            double val = it->second;
            if(rhs.find(key) != rhs.end())
                val -= rhs.at(key);
            res[key] = val;
        }

        for(Series::const_iterator it = rhs.begin(); it != rhs.end(); ++it) {
            string key = it->first;
            if(lhs.find(key) == lhs.end())
                res[key] = -it->second;
        }
        
        return Series(res);
    }

    Series operator*(const Series& lhs, const Series& rhs) {
        map<string, double> res;

        for(Series::const_iterator it = lhs.begin(); it != lhs.end(); ++it) {
            string key = it->first;
            double val = it->second;
            if(rhs.find(key) != rhs.end())
                val *= rhs.at(key);
            res[key] = val;
        }

        for(Series::const_iterator it = rhs.begin(); it != rhs.end(); ++it) {
            string key = it->first;
            if(lhs.find(key) == lhs.end())
                res[key] = it->second;
        }
    
        return Series(res);
    }

    Series operator/(const Series& lhs, const Series& rhs) {
        map<string, double> res;

        for(Series::const_iterator it = lhs.begin(); it != lhs.end(); ++it) {
            string key = it->first;
            double val = it->second;
            if(rhs.find(key) != rhs.end())
                val /= rhs.at(key);
            res[key] = val;
        }

        for(Series::const_iterator it = rhs.begin(); it != rhs.end(); ++it) {
            string key = it->first;
            if(lhs.find(key) == lhs.end())
                res[key] = 1. / it->second;
        }
    
        return Series(res);
    }
}