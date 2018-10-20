#include<algorithm>
#include<fel/containers.hpp>


namespace FEngine {

    namespace {
        vector<double> rankSort(const vector<double>& rhs) {
            size_t  size = rhs.size();
            vector<std::pair<float, size_t> > v_sort(size);

            for (size_t i = 0U; i < size; ++i) {
                v_sort[i] = std::make_pair(rhs[i], i);
            }

            std::sort(v_sort.begin(), v_sort.end());

            std::pair<double, size_t> rank;
            vector<double> result(size);

            for (size_t i = 0U; i < size; ++i) {
                if (v_sort[i].first != rank.first) {
                    rank = std::make_pair(v_sort[i].first, i);
                }
                result[v_sort[i].second] = static_cast<double>(rank.second);
            }
            return result;
        }
    }

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

    bool operator==(const Series& lhs, const Series& rhs) {
        return lhs.maps_ == rhs.maps_;
    }

    Series rank(const Series& rhs) {
        return Series(rhs.keys(), rankSort(rhs.vals()));
    }
}