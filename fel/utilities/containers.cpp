#include<algorithm>
#include<fel/utilities/containers.hpp>


namespace FEngine {

    namespace {
        vector<double> rankSort(const vector<double>& rhs) {
            size_t  size = rhs.size();
            vector<std::pair<double, size_t> > v_sort(size);

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

        for(const auto& it: lhs) {
            string key = it.first;
            double val = it.second;
            if(rhs.find(key) != rhs.end())
                val += rhs.at(key);
            res[key] = val;
        }

        for(const auto& it: rhs) {
            string key = it.first;
            if(lhs.find(key) == lhs.end())
                res[key] = it.second;
        }
        
        return Series(res);
    }

    Series operator-(const Series& lhs, const Series& rhs) {
        map<string, double> res;

        for(const auto& it: lhs) {
            string key = it.first;
            double val = it.second;
            if(rhs.find(key) != rhs.end())
                val -= rhs.at(key);
            res[key] = val;
        }

        for(const auto& it: rhs) {
            string key = it.first;
            if(lhs.find(key) == lhs.end())
                res[key] = -it.second;
        }
        
        return Series(res);
    }

    Series operator*(const Series& lhs, const Series& rhs) {
        map<string, double> res;

        for(const auto& it: lhs) {
            string key = it.first;
            double val = it.second;
            if(rhs.find(key) != rhs.end())
                val *= rhs.at(key);
            res[key] = val;
        }

        for(const auto& it: rhs) {
            string key = it.first;
            if(lhs.find(key) == lhs.end())
                res[key] = it.second;
        }
    
        return Series(res);
    }

    Series operator/(const Series& lhs, const Series& rhs) {
        map<string, double> res;

        for(const auto& it: lhs) {
            string key = it.first;
            double val = it.second;
            if(rhs.find(key) != rhs.end())
                val /= rhs.at(key);
            res[key] = val;
        }

        for(const auto& it: rhs) {
            string key = it.first;
            if(lhs.find(key) == lhs.end())
                res[key] = 1. / it.second;
        }
    
        return Series(res);
    }

    Series operator/(const Series& lhs, double rhs) {
        map<string, double> res;

        for(const auto& it: lhs) {
            string key = it.first;
            double val = it.second;
            res[key] = val / rhs;
        }
    
        return Series(res);
    }

    double dot(const Series& lhs, const Series& rhs) {
        double res = 0.;
        for(const auto& it: lhs) {
            string key = it.first;
            double val = it.second;
            if(rhs.find(key) != rhs.end())
                res += val * rhs.at(key);
        }
        return res;
    }

    double sum(const Series& rhs) {
        double res = 0.;

        for(const auto& it: rhs) {
            double val = it.second;
            res += val;
        }
        return res;
    }

    Series operator-(const Series& rhs) {
        map<string, double> res;
        for(const auto& it: rhs)
            res[it.first] = -it.second;
        return Series(res);
    }

    bool operator==(const Series& lhs, const Series& rhs) {
        return lhs.maps_ == rhs.maps_;
    }

    Series abs(const Series& rhs) {
        map<string, double> res;

        for(const auto& it: rhs) {
            string key = it.first;
            double val = it.second;
            res[key] = val >= 0 ? val : -val;
        }
        return Series(res);
    }

    Series rank(const Series& rhs) {
        return Series(rhs.keys(), rankSort(rhs.values()));
    }
}