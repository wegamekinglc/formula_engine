#include <fel/containers.hpp>

namespace FEngine {
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

    Series operator-(const Series& rhs) {
        map<string, double> res;
        for(Series::const_iterator it = rhs.begin(); it != rhs.end(); ++it) 
            res[it->first] = -it->second;
        return Series(res);
    }
}